// Ripper.cpp: Implementierung der Klasse Ripper.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ripper.h"
#include "WavDlg.h"
#include "WripDlg.h"
#include "Wrip.h"
#include "TrackDlg.h"
#include "TrackInfo.h"
#include "DriveInfo.h"
#include "CommonDlg.h"
#include <winbase.h>
#include "OutputInfo.h"
#include "ConversionDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Ripper::Ripper()
{

}

Ripper::~Ripper()
{

}

BOOL Ripper::m_bRun = TRUE;

UINT Ripper::StartRip( LPVOID lpParam )
{
	TOC toc;
	ZeroMemory( &toc, sizeof(TOC) );
	DWORD dwStart = 0;
	DWORD dwLen = 0;
	int iCur = 0;
	int iSum = 0;
	m_bRun = TRUE;

	OutputInfo::Instance()->ClearWAVFileStuff();
	OutputInfo::Instance()->ClearMP3FileStuff();
	OutputInfo::Instance()->ClearOGGFileStuff();

	for( int j=0; j<TrackInfo::Instance()->GetNumberOfTracks(); j++ ) {
		SetOutputPath( j );
		if( CTrackDlg::Instance()->m_list.GetCheck( j ) ) {
			iSum++;
		}
	}

	OutputInfo::Instance()->SetSelectedTrackCount( iSum );

	try {
		for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
			if( CTrackDlg::Instance()->m_list.GetCheck( i ) ) {
				iCur++;

				if( CWavDlg::Instance()->m_bJitter ) {
					ModifyCDParms( DriveInfo::Instance()->GetCurrentDrive().hCD, CDP_OVERLAP, CWavDlg::Instance()->m_iReadOverlap );
					ModifyCDParms( DriveInfo::Instance()->GetCurrentDrive().hCD, CDP_JITTER, CWavDlg::Instance()->m_iBlockCompare );
					ModifyCDParms( DriveInfo::Instance()->GetCurrentDrive().hCD, CDP_READMODE, CWavDlg::Instance()->m_iReadSectors );
				}

				ModifyCDParms( DriveInfo::Instance()->GetCurrentDrive().hCD, CDP_MSF, FALSE );

				if( ReadTOC( DriveInfo::Instance()->GetCurrentDrive().hCD, &toc ) != SS_COMP ) {
					MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Error while reading the TOC"), _T("Rip Error"), MB_OK | MB_ICONERROR );
					PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_ABORTED, 0, 0 );
					AfxEndThread( 1, TRUE );
					return (UINT) 1;
				}

				MSB2DWORD( &dwStart, toc.tracks[i].addr );
				MSB2DWORD( &dwLen, toc.tracks[i+1].addr );
				dwLen -= dwStart;

				RipAudio( DriveInfo::Instance()->GetCurrentDrive().hCD, dwStart, dwLen, i, iCur, iSum );
				OutputInfo::Instance()->PushQueue( i );
			}
		}
	}
	catch(...) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("An unknown exception occured.\nPlease report this to <engelhardt@dvoid.org>.\n\nThank you!"), _T("Rip Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );

		return (UINT) 0;
	}

	PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_FINISH, 0, 0 );

	return (UINT) 0;
}

void Ripper::RipAudio( HCDROM hCD, DWORD dwStart, DWORD dwLen, int iTrack, int iCur, int iSum )
{
	DWORD dwStatus = 0;
	FILE *fp = NULL;
	DWORD num2rip = 26;
	int retries = 0;
	LPTRACKBUF t = {0};
	int c = 0;
	DWORD numWritten = 0;
	DWORD dwLEN = dwLen;
	CString csError = _T("");

	t = NewTrackBuf( 26 );

	if( !t ) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Trackbuffer could not be loaded"), _T("Rip Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return;
	}

	CString csOutputPath = OutputInfo::Instance()->GetWAVFilePaths()[iTrack];
	fp = fopen( csOutputPath.GetBuffer( 0 ), _T("w+b") );
	csOutputPath.ReleaseBuffer();

	WriteWavHeader( fp, 0 );

	CConversionDlg::Instance()->m_csWAVStartSector.Format( _T("%ld"), dwStart );
	CConversionDlg::Instance()->m_csWAVEndSector.Format( _T("%ld"), dwStart + dwLen );
	CConversionDlg::Instance()->m_csWAVCurrentTrack = OutputInfo::Instance()->GetWAVFileNames()[iTrack];
	CConversionDlg::Instance()->m_csWAVCount.Format( _T("( %d / %d )"), iCur, iSum );
	CConversionDlg::Instance()->m_progressWAV.SetRange32( 0, dwLen );
	CConversionDlg::Instance()->m_csWAVCurrentSector.Format( _T("%ld"), dwStart );
	CConversionDlg::Instance()->m_csWAVPerCent.Format( _T("0 %%") );
	PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

	while( dwLen ) {

		if( !m_bRun ) {
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
		}

		if( dwLen < num2rip ) {
			num2rip = dwLen;
		}

		retries = 3;
		dwStatus = SS_ERR;
		while( retries-- && (dwStatus != SS_COMP) )	{
			t->numFrames   = num2rip;
			t->startOffset = 0;
			t->len         = 0;
			t->startFrame  = dwStart;

			dwStatus       = ReadCDAudioLBA( hCD, t );
		}
		
		if( dwStatus == SS_COMP ) {
			fwrite( t->buf + t->startOffset, 1, t->len, fp );
			numWritten += t->len;
		}
		else {
			csError.Format( _T("Error at %d (%d:%d)"), dwStart, GetAspiLibError(), GetAspiLibAspiError() );
			MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Rip Error"), MB_OK | MB_ICONERROR );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_WAV_ABORTED, 0, 0 );
			AfxEndThread( 1, TRUE );
		}

		dwStart += num2rip;
		dwLen   -= num2rip;

		CConversionDlg::Instance()->m_csWAVCurrentSector.Format( _T("%ld"), dwStart + (dwLEN - dwLen) );
		CConversionDlg::Instance()->m_progressWAV.SetPos( dwLEN - dwLen );
		CConversionDlg::Instance()->m_csWAVPerCent.Format( _T("%d %%"), (dwLEN - dwLen) / (dwLEN / 100) );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
	}

	WriteWavHeader( fp, numWritten );
  
	fclose( fp );
	GlobalFree( (HGLOBAL) t );
}

LPTRACKBUF Ripper::NewTrackBuf( DWORD numFrames )
{
	LPTRACKBUF t;
	int numAlloc = 0;

	numAlloc = (( (int) numFrames ) * 2352 ) + TRACKBUFEXTRA;

	t = (LPTRACKBUF) GlobalAlloc( GPTR, numAlloc );

	if( !t ) {
		return NULL;
	}

	t->startFrame = 0;
	t->numFrames = 0;
	t->maxLen = numFrames * 2352;
	t->len = 0;
	t->status = 0;
	t->startOffset = 0;

	return t;
}

void Ripper::MSB2DWORD( DWORD* d, BYTE* b )
{
	DWORD retVal = 0;

	retVal = (DWORD) b[0];
	retVal = (retVal<<8) + (DWORD) b[1];
	retVal = (retVal<<8) + (DWORD) b[2];
	retVal = (retVal<<8) + (DWORD) b[3];

	*d = retVal;
}

void Ripper::WriteWavHeader( FILE* fp, DWORD len )
{
	typedef struct _WAVHDR {
		BYTE  riff[4];
		DWORD len;
		BYTE  cWavFmt[8];
		DWORD dwHdrLen;
		WORD  wFormat;
		WORD  wNumChannels;
		DWORD dwSampleRate;
		DWORD dwBytesPerSec;
		WORD  wBlockAlign;
		WORD  wBitsPerSample;
		BYTE  cData[4];
		DWORD dwDataLen;
	} PACKED WAVHDR, *PWAVHDR, *LPWAVHDR;

	WAVHDR wav = {0};

	if( !fp ) {
		return;
	}

	memcpy( wav.riff, "RIFF", 4 );
	wav.len = len + 44 - 8;
	memcpy( wav.cWavFmt, "WAVEfmt ", 8 );
	wav.dwHdrLen = 16;
	wav.wFormat = 1;
	wav.wNumChannels = 2;
	wav.dwSampleRate = 44100;
	wav.dwBytesPerSec = 44100*2*2;
	wav.wBlockAlign = 4;
	wav.wBitsPerSample = 16;
	memcpy( wav.cData, "data", 4 );
	wav.dwDataLen = len;
	fseek( fp, 0, SEEK_SET );

	fwrite( &wav, 1, sizeof(wav), fp );
}

void Ripper::SetOutputPath( int iTrack )
{
	static const CString csNr     = _T("<nr>");
	static const CString csTitle  = _T("<title>");
	static const CString csArtist = _T("<artist>");
	static const CString csAlbum  = _T("<album>");
	static const CString csL      = _T("<");
	static const CString csR      = _T(">");
	static const CString csP      = _T(".");

	CString csPath   = _T("");
	csPath = CCommonDlg::Instance()->m_csDestination;
	if( csPath == _T("") ) {
		CHAR szCurDir[MAX_PATH] = {0};
		GetCurrentDirectory( MAX_PATH, szCurDir );
		csPath = szCurDir;
	}
	if( csPath[csPath.GetLength()-1] != '\\' ) {
		csPath += _T("\\");
	}
	csPath.TrimLeft();
	csPath.TrimRight();

	CString csFolder = _T("");
	CCommonDlg::Instance()->m_comboFolder.GetWindowText( csFolder );
	csFolder.Replace( csNr,     _T("") );
	csFolder.Replace( csTitle,  _T("") );
	csFolder.Replace( csArtist, TrackInfo::Instance()->csArtist );
	csFolder.Replace( csAlbum,  TrackInfo::Instance()->csAlbum );
	csFolder.Replace( csL,      _T("") );
	csFolder.Replace( csR,      _T("") );
	csFolder.Replace( csP,      _T("") );
	csFolder.TrimLeft();
	csFolder.TrimRight();
	
	CString csFile   = _T("");
	CCommonDlg::Instance()->m_comboFile.GetWindowText( csFile );
	CString csTmpNr = _T("");
	csTmpNr.Format( _T("%.2d"), TrackInfo::Instance()->GetTracks()[iTrack].iNumber );
	csFile.Replace( csNr,     csTmpNr );
	csFile.Replace( csTitle,  TrackInfo::Instance()->GetTracks()[iTrack].csTitle );
	csFile.Replace( csArtist, TrackInfo::Instance()->csArtist );
	csFile.Replace( csAlbum,  TrackInfo::Instance()->csAlbum );
	csFile.Replace( csL,      _T("") );
	csFile.Replace( csR,      _T("") );
	csFile.Replace( csP,      _T("") );
	csFile.TrimLeft();
	csFile.TrimRight();
	if( csFile == _T("") ) {
		csFile.Format( _T("%.2d - %s"),
					   TrackInfo::Instance()->GetTracks()[iTrack].iNumber,
					   TrackInfo::Instance()->GetTracks()[iTrack].csTitle );
	}
	OutputInfo::Instance()->AddWAVFileName( csFile );
	OutputInfo::Instance()->AddMP3FileName( csFile );
	OutputInfo::Instance()->AddOGGFileName( csFile );

	CString csOutputPath = _T("");
	csOutputPath += csPath;
	if( csFolder != _T("") ) {
		csOutputPath += csFolder;
	}

	CreateDirectory( csOutputPath, NULL );

	if( csFolder != _T("") ) {
		csOutputPath += _T("\\");
	}

	OutputInfo::Instance()->SetOutputFolder( csOutputPath );

	csOutputPath += csFile;
	OutputInfo::Instance()->AddWAVFilePath( csOutputPath );
	OutputInfo::Instance()->AddMP3FilePath( csOutputPath );
	OutputInfo::Instance()->AddOGGFilePath( csOutputPath );
}

void Ripper::StopRip()
{
	m_bRun = FALSE;
}
