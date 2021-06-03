// Mp3Encoder.cpp: Implementierung der Klasse Mp3Encoder.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mp3Encoder.h"
#include "TrackDlg.h"
#include "TrackInfo.h"
#include "WripDlg.h"
#include "ID3Tag.h"
#include "lame/BladeMP3EncDLL.h"
#include "OutputInfo.h"
#include "ConversionDlg.h"
#include "WavDlg.h"
#include "Mp3Dlg.h"
#include "Playlist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Mp3Encoder::Mp3Encoder()
{

}

Mp3Encoder::~Mp3Encoder()
{

}

BOOL Mp3Encoder::m_bRun = TRUE;

UINT Mp3Encoder::StartEncode( LPVOID lParam )
{
	m_bRun = TRUE;

	OutputInfo::Instance()->WaitUntilData();

	int iSum = OutputInfo::Instance()->GetSelectedTrackCount();
	int iCount = iSum;

	try {
		CString csMP3File = _T("");
		while( iCount ) {

			if( !m_bRun ) {
				PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
				AfxEndThread( 1, TRUE );
			}

			CConversionDlg::Instance()->m_csMP3Size.Format( _T("0") );
			CConversionDlg::Instance()->m_csWAVCurrentSize.Format( _T("0") );
			CConversionDlg::Instance()->m_csMP3PerCent.Format( _T("waiting ...") );
			CConversionDlg::Instance()->m_progressMP3.SetPos( -1 );
			CConversionDlg::Instance()->m_csMP3CurrentTrack = _T("---");
			CConversionDlg::Instance()->m_csMP3Count.Format( _T("( - / - )") );
			CConversionDlg::Instance()->m_csWAVSize.Format( _T("0") );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

			OutputInfo::Instance()->WaitUntilData();
			int iTrack = OutputInfo::Instance()->PopQueue();

			EncodeWAV( iTrack, (iSum - iCount) + 1, iSum );

			csMP3File = OutputInfo::Instance()->GetMP3FileNames()[iTrack];
			OutputInfo::Instance()->AddPlaylistEntry( csMP3File );

			CString csID3 = _T("");
			CMp3Dlg::Instance()->m_comboID3.GetWindowText( csID3 );
			if( csID3 == _T("ID3 v2") ) {
				int* piTrack = &iTrack;
				AfxBeginThread( ID3Tag::StartID3Tag, piTrack, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );	
				ID3Tag::StartID3Tag( piTrack );
			}

			if( CWavDlg::Instance()->m_bDeleteAfterEncode ) {
				CFile::Remove( OutputInfo::Instance()->GetWAVFilePaths()[iTrack] );
			}

			iCount--;
		}

		int iPlaylist = CMp3Dlg::Instance()->m_comboPlaylist.GetCurSel();
		if( iPlaylist == 1 ) {
			Playlist::Instance()->CreateM3U();
		}
	}
	catch(...) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("An unknown exception occured.\nPlease report this to <engelhardt@dvoid.org>.\n\nThank you!"), _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );

		return (UINT) 0;
	}

	PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_FINISH, 0, 0 );

	return (UINT) 0;
}

void Mp3Encoder::StopEncode()
{
	m_bRun = FALSE;
}

int Mp3Encoder::EncodeWAV( int iTrack, int iCur, int iSum )
{
	BEINITSTREAM		beInitStream     = NULL;
	BEENCODECHUNK		beEncodeChunk    = NULL;
	BEDEINITSTREAM		beDeinitStream   = NULL;
	BECLOSESTREAM		beCloseStream    = NULL;
	BEVERSION			beVersion        = NULL;
	BEWRITEVBRHEADER	beWriteVBRHeader = NULL;

	HINSTANCE	hDLL			=NULL;
	FILE*		pFileIn			=NULL;
	FILE*		pFileOut		=NULL;
	BE_CONFIG	beConfig		={0,};

	CHAR		strFileIn[255]	= {'0',};
	CHAR		strFileOut[255]	= {'0',};

	DWORD		dwSamples		=0;
	DWORD		dwMP3Buffer		=0;
	HBE_STREAM	hbeStream		=0;
	BE_ERR		err				=0;

	PBYTE		pMP3Buffer		=NULL;
	PSHORT		pWAVBuffer		=NULL;

	if( !m_bRun ) {
		return -1;
	}

	// Setup the file names
	strcpy( strFileIn , OutputInfo::Instance()->GetWAVFilePaths()[iTrack].GetBuffer( 0 ) );
	strcpy( strFileOut, OutputInfo::Instance()->GetMP3FilePaths()[iTrack].GetBuffer( 0 ) );

	hDLL = LoadLibrary("lame_enc.dll");

	if( hDLL == NULL ) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Error loading lame_enc.dll"), _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	// Get Interface functions from the DLL
	beInitStream	= (BEINITSTREAM) GetProcAddress(hDLL, TEXT_BEINITSTREAM);
	beEncodeChunk	= (BEENCODECHUNK) GetProcAddress(hDLL, TEXT_BEENCODECHUNK);
	beDeinitStream	= (BEDEINITSTREAM) GetProcAddress(hDLL, TEXT_BEDEINITSTREAM);
	beCloseStream	= (BECLOSESTREAM) GetProcAddress(hDLL, TEXT_BECLOSESTREAM);
	beVersion		= (BEVERSION) GetProcAddress(hDLL, TEXT_BEVERSION);
	beWriteVBRHeader= (BEWRITEVBRHEADER) GetProcAddress(hDLL,TEXT_BEWRITEVBRHEADER);

	// Check if all interfaces are present
	if(!beInitStream || !beEncodeChunk || !beDeinitStream || !beCloseStream || !beVersion || !beWriteVBRHeader)	{
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Unable to get LAME interfaces"), _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	// Try to open the WAV file, be sure to open it as a binary file!	
	pFileIn = fopen( strFileIn, "rb" );

	// Check file open result
	if( pFileIn == NULL ) {
		CString csError = _T("");
		csError.Format( _T("Error opening %s"), strFileIn );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	// Open MP3 file
	pFileOut= fopen( strFileOut, "wb+" );

	// Check file open result
	if( pFileOut == NULL ) {
		CString csError = _T("");
		csError.Format( _T("Error creating file %s"), strFileOut );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	{
		CFileStatus wavFileStat;
		CFile::GetStatus( OutputInfo::Instance()->GetWAVFilePaths()[iTrack], wavFileStat );

		CFileStatus mp3FileStat;
		CFile::GetStatus( OutputInfo::Instance()->GetMP3FilePaths()[iTrack], mp3FileStat );

		CConversionDlg::Instance()->m_progressMP3.SetRange32( 0, 100 );

		CConversionDlg::Instance()->m_csMP3CurrentTrack = OutputInfo::Instance()->GetMP3FileNames()[iTrack];
		CConversionDlg::Instance()->m_csMP3Count.Format( _T("( %d / %d )"), iCur, iSum );
		CConversionDlg::Instance()->m_csWAVSize.Format( _T("%.1f"), static_cast<float>( wavFileStat.m_size ) / 1000000.0f );
		CConversionDlg::Instance()->m_csMP3Size.Format( _T("%.1f"), static_cast<float>( mp3FileStat.m_size ) / 1000000.0f );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
	}

	memset( &beConfig, 0, sizeof(beConfig) );					// clear all fields

	// use the LAME config structure
	beConfig.dwConfig = BE_CONFIG_LAME;

	// LAME SETTINGS
	beConfig.format.LHV1.dwStructVersion	= 1;
	
	beConfig.format.LHV1.dwStructSize		= sizeof(beConfig);		
	
	CString csFrequency = _T("");
	CMp3Dlg::Instance()->m_comboFrequency.GetWindowText( csFrequency );
	beConfig.format.LHV1.dwSampleRate		= TR::FromString<int>( csFrequency );	// INPUT FREQUENCY
	
	beConfig.format.LHV1.dwReSampleRate		= 0;									// DON"T RESAMPLE
	
	int iMode = CMp3Dlg::Instance()->m_comboMode.GetCurSel();
	beConfig.format.LHV1.nMode				= iMode;								// OUTPUT IN STREO
	
	CString csBitrate = _T("");
	CMp3Dlg::Instance()->m_comboBitrate.GetWindowText( csBitrate );
	beConfig.format.LHV1.dwBitrate			= TR::FromString<int>( csBitrate );		// MINIMUM BIT RATE
	
	int iQuality = CMp3Dlg::Instance()->m_comboQuality.GetCurSel();
	beConfig.format.LHV1.nPreset			= iQuality;								// QUALITY PRESET SETTING
	
	int iVersion = CMp3Dlg::Instance()->m_comboVersion.GetCurSel();
	if( iVersion == 1 ) {
		beConfig.format.LHV1.dwMpegVersion	= MPEG1;								// MPEG VERSION (I or II)
	}
	else {
		beConfig.format.LHV1.dwMpegVersion	= MPEG2;								// MPEG VERSION (I or II)
	}
	
	beConfig.format.LHV1.dwPsyModel			= 0;									// USE DEFAULT PSYCHOACOUSTIC MODEL 
	
	beConfig.format.LHV1.dwEmphasis			= 0;									// NO EMPHASIS TURNED ON
	
	beConfig.format.LHV1.bOriginal			= TRUE;									// SET ORIGINAL FLAG

	if( CMp3Dlg::Instance()->m_bVBR ) {
		CString csMaxBitrate = _T("");
		CMp3Dlg::Instance()->m_comboMaxBitrate.GetWindowText( csMaxBitrate );
		beConfig.format.LHV1.dwMaxBitrate	 = TR::FromString<int>( csMaxBitrate );	// MAXIMUM BIT RATE
		
		beConfig.format.LHV1.bCRC			 = CMp3Dlg::Instance()->m_bCrc;			// INSERT CRC
		
		beConfig.format.LHV1.bCopyright		 = TRUE;								// SET COPYRIGHT FLAG	
		
		beConfig.format.LHV1.bPrivate		 = TRUE;								// SET PRIVATE FLAG
		
		beConfig.format.LHV1.bWriteVBRHeader = TRUE;								// YES, WRITE THE XING VBR HEADER
		
		beConfig.format.LHV1.bEnableVBR		 = TRUE;								// USE VBR
		
		int iVBRQuality = CMp3Dlg::Instance()->m_comboVBRQuality.GetCurSel() + 1;
		beConfig.format.LHV1.nVBRQuality		= iVBRQuality;						// SET VBR QUALITY
	}

	beConfig.format.LHV1.bNoRes				 = TRUE;								// No Bit resorvoir

	// Init the MP3 Stream
	err = beInitStream( &beConfig, &dwSamples, &dwMP3Buffer, &hbeStream );

	// Check result
	if( err != BE_ERR_SUCCESSFUL ) {
		CString csError = _T("");
		csError.Format( _T("Error opening encoding stream (%lu)"), err );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}


	// Allocate MP3 buffer
	pMP3Buffer = new BYTE[dwMP3Buffer];

	// Allocate WAV buffer
	pWAVBuffer = new SHORT[dwSamples];

	// Check if Buffer are allocated properly
	if( !pMP3Buffer || !pWAVBuffer ) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Out of memory"), _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	DWORD dwRead = 0;
	DWORD dwWrite = 0;
	DWORD dwDone = 0;
	DWORD dwFileSize = 0;

	// Seek to end of file
	fseek( pFileIn, 0, SEEK_END );

	// Get the file size
	dwFileSize = ftell( pFileIn );

	// Seek back to start of WAV file,
	// but skip the first 44 bytes, since that's the WAV header
	fseek( pFileIn, 44, SEEK_SET );


	// Convert All PCM samples
	while ( (dwRead = fread( pWAVBuffer, sizeof(SHORT), dwSamples, pFileIn)) >0 )	{
		if( !m_bRun ) {
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
		}

		// Encode samples
		err = beEncodeChunk( hbeStream, dwRead, pWAVBuffer, pMP3Buffer, &dwWrite );

		// Check result
		if( err != BE_ERR_SUCCESSFUL ) {
			beCloseStream( hbeStream );
			CString csError = _T("");
			csError.Format( _T("beEncodeChunk failed (%lu)"), err );
			MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
			return -1;
		}
		
		// write dwWrite bytes that are returned in tehe pMP3Buffer to disk
		if( fwrite( pMP3Buffer, 1, dwWrite, pFileOut ) != dwWrite ) {
			MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Output file write error"), _T("Encode Error"), MB_OK | MB_ICONERROR );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
			return -1;
		}

		dwDone += dwRead * sizeof(SHORT);

		{
			CFileStatus mp3FileStat;
			CFile::GetStatus( OutputInfo::Instance()->GetMP3FilePaths()[iTrack], mp3FileStat );

			CConversionDlg::Instance()->m_csMP3Size.Format( _T("%.1f"), static_cast<float>( mp3FileStat.m_size ) / 1000000.0f );
			CConversionDlg::Instance()->m_csWAVCurrentSize.Format( _T("%.1f"), static_cast<float>( dwDone ) / 1000000.0f );
			CConversionDlg::Instance()->m_csMP3PerCent.Format( _T("%.0f %%"), 100.0f * static_cast<float>( dwDone ) / static_cast<float>( dwFileSize ) );
			CConversionDlg::Instance()->m_progressMP3.SetPos( static_cast<int>( 100.0f * static_cast<float>( dwDone ) / static_cast<float>( dwFileSize ) ) );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
		}
	}

	// Deinit the stream
	err = beDeinitStream( hbeStream, pMP3Buffer, &dwWrite );

	// Check result
	if( err != BE_ERR_SUCCESSFUL ) {
		beCloseStream( hbeStream );
		CString csError = _T("");
		csError.Format( _T("beExitStream failed (%lu)"), err );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return -1;
	}

	// Are there any bytes returned from the DeInit call?
	// If so, write them to disk
	if( dwWrite ) {
		if( fwrite( pMP3Buffer, 1, dwWrite, pFileOut ) != dwWrite ) {
			MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Output file write error"), _T("Encode Error"), MB_OK | MB_ICONERROR );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
			return -1;
		}
	}

	// close the MP3 Stream
	beCloseStream( hbeStream );

	// Delete WAV buffer
	delete [] pWAVBuffer;

	// Delete MP3 Buffer
	delete [] pMP3Buffer;

	// Close input file
	fclose( pFileIn );

	// Close output file
	fclose( pFileOut );

	// Write the VBR Tag
	beWriteVBRHeader( strFileOut );

	// Were done, return OK result
	return 0;
}
