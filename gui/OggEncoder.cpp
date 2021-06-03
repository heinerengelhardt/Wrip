// OggEncoder.cpp: Implementierung der Klasse OggEncoder.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OggEncoder.h"
#include "TrackDlg.h"
#include "TrackInfo.h"
#include "WripDlg.h"
#include "ID3Tag.h"
#include "lame/BladeMP3EncDLL.h"
#include "OutputInfo.h"
#include "ConversionDlg.h"
#include "WavDlg.h"
#include "Mp3Dlg.h"
#include "OggDlg.h"
#include "Playlist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

OggEncoder::OggEncoder()
{

}

OggEncoder::~OggEncoder()
{

}

BOOL OggEncoder::m_bRun = TRUE;

UINT OggEncoder::StartEncode(LPVOID lParam)
{
	m_bRun = TRUE;

	OutputInfo::Instance()->WaitUntilData();

	int iSum = OutputInfo::Instance()->GetSelectedTrackCount();
	int iCount = iSum;

	try {
		CString csOGGFile = _T("");
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

			csOGGFile = OutputInfo::Instance()->GetOGGFileNames()[iTrack];
			OutputInfo::Instance()->AddPlaylistEntry( csOGGFile );

			if( CWavDlg::Instance()->m_bDeleteAfterEncode ) {
				CFile::Remove( OutputInfo::Instance()->GetWAVFilePaths()[iTrack] );
			}

			iCount--;
		}

		int iPlaylist = COggDlg::Instance()->m_comboPlaylist.GetCurSel();
		if( iPlaylist == 1 ) {
			Playlist::Instance()->CreateM3U();
		}
	}
	catch(...) {
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );

		return (UINT) 0;
	}

	PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_FINISH, 0, 0 );

	return (UINT) 0;
}

void OggEncoder::StopEncode()
{
	m_bRun = FALSE;
}

int OggEncoder::EncodeWAV(int iTrack, int iCur, int iSum)
{
	const int   READ = 1024;
	signed char readbuffer[READ * 4 + 44] = {0};

	ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
	ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
	ogg_packet       op; /* one raw packet of data for decode */

	vorbis_info      vi; /* struct that stores all the static vorbis bitstream settings */
	vorbis_comment   vc; /* struct that stores all the user comments */

	vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
	vorbis_block     vb; /* local working space for packet->PCM decode */

	int eos          = 0;
	int ret          = 0;
	int i            = 0;
	int founddata    = 0;
	DWORD dwFileSize = 0;

	CHAR szfin[MAX_PATH]  = {0};
	CHAR szfout[MAX_PATH] = {0};

	strcpy( szfin , OutputInfo::Instance()->GetWAVFilePaths()[iTrack].GetBuffer( 0 ) );
	strcpy( szfout , OutputInfo::Instance()->GetOGGFilePaths()[iTrack].GetBuffer( 0 ) );

	FILE* fin  = fopen( szfin,  "r" );
	FILE* fout = fopen( szfout, "wb" );

	if( fin == NULL ) {
		CString csError = _T("");
		csError.Format( _T("Error opening %s"), szfin );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return (UINT) -1;
	}

	if( fout == NULL ) {
		CString csError = _T("");
		csError.Format( _T("Error opening %s"), szfout );
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), csError, _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return (UINT) -1;
	}

	_setmode( _fileno( fin ), _O_BINARY );
	_setmode( _fileno( fout ), _O_BINARY );

	fseek( fin, 0, SEEK_END );
	dwFileSize = ftell( fin );
	fseek( fin, 0, SEEK_SET );

	for( i=0, founddata=0; i<30 && ! feof(fin) && ! ferror(fin); i++ ) {
		fread( readbuffer, 1, 2, fin );

		if( !strncmp( (char*)readbuffer, "da", 2) ) {
			founddata = 1;
			fread( readbuffer, 1, 6, fin );
			break;
		}
	}

	vorbis_info_init( &vi );

	{
		CFileStatus wavFileStat;
		CFile::GetStatus( OutputInfo::Instance()->GetWAVFilePaths()[iTrack], wavFileStat );

		CFileStatus oggFileStat;
		CFile::GetStatus( OutputInfo::Instance()->GetOGGFilePaths()[iTrack], oggFileStat );

		CConversionDlg::Instance()->m_progressMP3.SetRange32( 0, 100 );

		CConversionDlg::Instance()->m_csMP3CurrentTrack = OutputInfo::Instance()->GetOGGFileNames()[iTrack];
		CConversionDlg::Instance()->m_csMP3Count.Format( _T("( %d / %d )"), iCur, iSum );
		CConversionDlg::Instance()->m_csWAVSize.Format( _T("%.1f"), static_cast<float>( wavFileStat.m_size ) / 1000000.0f );
		CConversionDlg::Instance()->m_csMP3Size.Format( _T("%.1f"), static_cast<float>( oggFileStat.m_size ) / 1000000.0f );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
	}


	if( COggDlg::Instance()->m_bVBR ) {
		/*********************************************************************
		Encoding using a VBR quality mode.  The usable range is -.1
		(lowest quality, smallest file) to 1. (highest quality, largest file).
		Example quality mode .4: 44kHz stereo coupled, roughly 128kbps VBR
		*********************************************************************/

		CString csFrequency  = _T("");
		CString csVBRQuality = _T("");

		COggDlg::Instance()->m_comboFrequency.GetWindowText( csFrequency );
		COggDlg::Instance()->m_comboVBRQuality.GetWindowText( csVBRQuality );

		int   iChannels   = COggDlg::Instance()->m_comboChannels.GetCurSel();
		long  lFrequency  = TR::FromString<long>( csFrequency );
		float fVBRQuality = TR::FromString<float>( csVBRQuality );

		fVBRQuality /= 10.0f;
		iChannels   += 1;
  
		ret = vorbis_encode_init_vbr( &vi, iChannels, lFrequency, fVBRQuality );
	}
	else {
		/*********************************************************************
		Encoding using an average bitrate mode (ABR).
		example: 44kHz stereo coupled, average 128kbps VBR 
		*********************************************************************/

		CString csFrequency  = _T("");
		CString csMaxBitrate = _T("");
		CString csNomBitrate = _T("");
		CString csMinBitrate = _T("");

		COggDlg::Instance()->m_comboFrequency.GetWindowText( csFrequency );
		COggDlg::Instance()->m_comboMaxBitrate.GetWindowText( csMaxBitrate );
		COggDlg::Instance()->m_comboNomBitrate.GetWindowText( csNomBitrate );
		COggDlg::Instance()->m_comboMinBitrate.GetWindowText( csMinBitrate );

		int   iChannels  = COggDlg::Instance()->m_comboChannels.GetCurSel();
		long lFrequency  = TR::FromString<long>( csFrequency );
		long lMaxBitrate = TR::FromString<long>( csMaxBitrate );
		long lNomBitrate = TR::FromString<long>( csNomBitrate );
		long lMinBitrate = TR::FromString<long>( csMinBitrate );

		iChannels   += 1;
		lMaxBitrate *= 1000;
		lNomBitrate *= 1000;
		lMinBitrate *= 1000;
 
		ret = vorbis_encode_init( &vi, iChannels, lFrequency, lMaxBitrate, lNomBitrate, lMinBitrate );
	}


//	/*********************************************************************
//	Encode using a qulity mode, but select that quality mode by asking for
//	an approximate bitrate.  This is not ABR, it is true VBR, but selected
//	using the bitrate interface, and then turning bitrate management off:
//	*********************************************************************/
//
//	ret = ( vorbis_encode_setup_managed( &vi, 2, 44100, -1, 128000, -1 ) ||
//		    vorbis_encode_ctl( &vi, OV_ECTL_RATEMANAGE_AVG, NULL )       ||
//            vorbis_encode_setup_init( &vi ) );


	/* do not continue if setup failed; this can happen if we ask for a
	mode that libVorbis does not support (eg, too low a bitrate, etc,
    will return 'OV_EIMPL') */

	if( ret ) {
		MessageBox( CWripDlg::Instance()->GetSafeHwnd(), _T("Failed to setup the ogg vorbis encoder"), _T("Encode Error"), MB_OK | MB_ICONERROR );
		PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
		AfxEndThread( 1, TRUE );
		return 1;
	}

	/* add a comment */
	vorbis_comment_init( &vc );
	vorbis_comment_add_tag( &vc, "Wrip", "Encoded by Wrip 1.0" );

	/* set up the analysis state and auxiliary encoding storage */
	vorbis_analysis_init( &vd, &vi );
	vorbis_block_init( &vd, &vb );
  
	/* set up our packet->stream encoder */
	/* pick a random serial number; that way we can more likely build
	chained streams just by concatenation */
	srand( time( NULL ) );
	ogg_stream_init( &os, rand() );

	/* Vorbis streams begin with three headers; the initial header (with
	most of the codec setup parameters) which is mandated by the Ogg
    bitstream spec.  The second header holds any comment fields.  The
    third header holds the bitstream codebook.  We merely need to
    make the headers, then pass them to libvorbis one at a time;
    libvorbis handles the additional Ogg bitstream constraints */

	{
		ogg_packet header;
		ogg_packet header_comm;
		ogg_packet header_code;

		vorbis_analysis_headerout( &vd, &vc, &header, &header_comm, &header_code );
		ogg_stream_packetin( &os, &header ); /* automatically placed in its own page */
		ogg_stream_packetin( &os, &header_comm );
		ogg_stream_packetin( &os, &header_code );

		/* This ensures the actual
		 * audio data will start on a new page, as per spec
		 */
		while( !eos ) {
			int result = ogg_stream_flush( &os, &og );
			if( result == 0 ) {
				break;
			}
			fwrite( og.header, 1, og.header_len, fout );
			fwrite( og.body, 1, og.body_len, fout );
		}
	}

	/* main encode loop */
	while( m_bRun && !eos ) {
		long i = 0L;
		long bytes = fread( readbuffer, 1, READ * 4, fin ); /* stereo hardwired here */

		if( bytes == 0 ) {
			/* end of file.  this can be done implicitly in the mainline,
			but it's easier to see here in non-clever fashion.
			Tell the library we're at end of stream so that it can handle
			the last frame and mark end of stream in the output properly */
			vorbis_analysis_wrote( &vd, 0 );

		}
		else {
			/* data to encode */

			/* expose the buffer to submit data */
			float **buffer = vorbis_analysis_buffer( &vd, READ );
      
			/* uninterleave samples */
			for( i=0; i<bytes/4; i++ ) {
				buffer[0][i]=((readbuffer[i*4+1]<<8) | (0x00ff&(int)readbuffer[i*4]))/32768.f;
				buffer[1][i]=((readbuffer[i*4+3]<<8) | (0x00ff&(int)readbuffer[i*4+2]))/32768.f;
			}
    
			/* tell the library how much we actually submitted */
			vorbis_analysis_wrote( &vd, i );
		}

		/* vorbis does some data preanalysis, then divvies up blocks for
		more involved (potentially parallel) processing.  Get a single
	    block for encoding now */
		while( ( vorbis_analysis_blockout( &vd, &vb ) == 1 ) ) {

			if( !m_bRun ) {
				PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
				AfxEndThread( 1, TRUE );
			}

			/* analysis, assume we want to use bitrate management */
			vorbis_analysis( &vb, NULL );
			vorbis_bitrate_addblock( &vb );

			while( ( vorbis_bitrate_flushpacket( &vd, &op ) ) ) {

				if( !m_bRun ) {
					PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
					AfxEndThread( 1, TRUE );
				}
	
				/* weld the packet into the bitstream */
				ogg_stream_packetin( &os, &op );
	
				/* write out pages (if any) */
				while( !eos ) {

					if( !m_bRun ) {
						PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_ENC_ABORTED, 0, 0 );
						AfxEndThread( 1, TRUE );
					}

					int result = ogg_stream_pageout( &os, &og );
					if( result == 0 ) {
						break;
					}
					fwrite( og.header, 1, og.header_len, fout );
					fwrite( og.body, 1, og.body_len, fout );
	  
					/* this could be set above, but for illustrative purposes, I do
					it here (to show that vorbis does know where the stream ends) */
	  
					if( ogg_page_eos( &og ) ) {
						eos = 1;
					}
				}
			}
		}

		{
			CFileStatus oggFileStat;
			CFile::GetStatus( OutputInfo::Instance()->GetOGGFilePaths()[iTrack], oggFileStat );

			CConversionDlg::Instance()->m_csMP3Size.Format( _T("%.1f"), static_cast<float>( oggFileStat.m_size ) / 1000000.0f );
			CConversionDlg::Instance()->m_csWAVCurrentSize.Format( _T("%.1f"), static_cast<float>( ftell( fin ) ) / 1000000.0f );
			CConversionDlg::Instance()->m_csMP3PerCent.Format( _T("%.0f %%"), 100.0f * static_cast<float>( ftell( fin ) ) / static_cast<float>( dwFileSize ) );
			CConversionDlg::Instance()->m_progressMP3.SetPos( static_cast<int>( 100.0f * static_cast<float>( ftell( fin ) ) / static_cast<float>( dwFileSize ) ) );
			PostMessage( CConversionDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
		}
	}

	/* clean up and exit.  vorbis_info_clear() must be called last */
  
	ogg_stream_clear( &os );
	vorbis_block_clear( &vb );
	vorbis_dsp_clear( &vd );
	vorbis_comment_clear( &vc );
	vorbis_info_clear( &vi );

	fclose( fin );
	fclose( fout );
  
	/* ogg_page and ogg_packet structs always point to storage in
    libvorbis.  They're never freed or manipulated directly */
  
	return 0;
}
