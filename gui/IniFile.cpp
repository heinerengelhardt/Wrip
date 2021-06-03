// IniFile.cpp: Implementierung der Klasse IniFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include "Resource.h"

#include "WripDlg.h"
#include "TrackDlg.h"
#include "PreferencesDlg.h"
#include "Mp3Dlg.h"
#include "WavDlg.h"
#include "OggDlg.h"
#include "CommonDlg.h"
#include "EncoderDlg.h"

#include "TrackInfo.h"
#include "FreeDBQuery.h"
#include "OutputInfo.h"
#include "DriveInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

IniFile::IniFile()
{

}

IniFile::~IniFile()
{

}

CString IniFile::GetCurrentFolder()
{
    TCHAR szPathName[_MAX_PATH];
    ::GetModuleFileName(NULL, szPathName, _MAX_PATH);
    LPTSTR pszFileName = _tcsrchr(szPathName, '\\') + 1;
    *pszFileName = '\0';

	CString csPathName = _T("");
	csPathName.Format( _T("%s"), szPathName );

	return csPathName;
}

void IniFile::SaveSettings()
{
	CString csPathName = GetCurrentFolder();
	CString csIniFile = csPathName + _T("Wrip.ini");

    CFile file;
    if( !file.Open( csIniFile, CFile::modeCreate | CFile::modeReadWrite ) ) {
		AfxMessageBox( _T("Could not create INI file") );
		return;
	}
	file.Close();

	CString csTmp = _T("");

	csTmp.Format( _T("%d"), CWripDlg::Instance()->m_comboDrives.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Drive"), csTmp, csIniFile );

	// COMMON
	csTmp = CCommonDlg::Instance()->m_csDestination;
	WritePrivateProfileString( _T("Wrip"), _T("Destination"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CCommonDlg::Instance()->m_comboFolder.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Folder"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CCommonDlg::Instance()->m_comboFile.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("File"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CCommonDlg::Instance()->m_comboCDDB.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("CDDB"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CCommonDlg::Instance()->m_bProxy );
	WritePrivateProfileString( _T("Wrip"), _T("UseProxy"), csTmp, csIniFile );

	csTmp = CCommonDlg::Instance()->m_csProxy;
	WritePrivateProfileString( _T("Wrip"), _T("Proxy"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CCommonDlg::Instance()->m_uiPort );
	WritePrivateProfileString( _T("Wrip"), _T("Port"), csTmp, csIniFile );

	// RIP
	csTmp.Format( _T("%d"), CWavDlg::Instance()->m_bJitter );
	WritePrivateProfileString( _T("Wrip"), _T("UseJitter"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CWavDlg::Instance()->m_bDeleteAfterEncode );
	WritePrivateProfileString( _T("Wrip"), _T("DeleteWavAfterEncode"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CWavDlg::Instance()->m_iReadSectors );
	WritePrivateProfileString( _T("Wrip"), _T("Sectors"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CWavDlg::Instance()->m_iBlockCompare );
	WritePrivateProfileString( _T("Wrip"), _T("Compare"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CWavDlg::Instance()->m_iReadOverlap );
	WritePrivateProfileString( _T("Wrip"), _T("Overlap"), csTmp, csIniFile );

	// ENCODE
	// MP3
	csTmp.Format( _T("%d"), CEncoderDlg::Instance()->m_comboEncoder.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Encoder"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CEncoderDlg::Instance()->m_comboThreadPriority.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("ThreadPriority"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboVersion.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Version"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboBitrate.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Bitrate"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboFrequency.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Frequency"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboQuality.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Quality"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboMode.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Mode"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboID3.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("ID3"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboPlaylist.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("Playlist"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboVBRQuality.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("VBRQuality"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_comboMaxBitrate.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("MaxBitrate"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_bVBR );
	WritePrivateProfileString( _T("Wrip"), _T("UseVBR"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), CMp3Dlg::Instance()->m_bCrc );
	WritePrivateProfileString( _T("Wrip"), _T("UseCRC"), csTmp, csIniFile );

	// OGG
	csTmp.Format( _T("%d"), COggDlg::Instance()->m_bVBR );
	WritePrivateProfileString( _T("Wrip"), _T("UseOggVBR"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboMaxBitrate.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("MaxOggBitrate"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboNomBitrate.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("NomOggBitrate"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboMinBitrate.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("MinOggBitrate"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboChannels.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("OggChannels"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboFrequency.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("OggFrequency"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboPlaylist.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("OggPlaylist"), csTmp, csIniFile );

	csTmp.Format( _T("%d"), COggDlg::Instance()->m_comboVBRQuality.GetCurSel() );
	WritePrivateProfileString( _T("Wrip"), _T("VBROggQuality"), csTmp, csIniFile );
}

void IniFile::LoadSettings()
{
	CString csPathName = GetCurrentFolder();
	CString csIniFile = csPathName + _T("Wrip.ini");

    CFile file;
    if( !file.Open( csIniFile, CFile::modeRead ) ) {
		return;
    }
	file.Close();

	CHAR szTmp[MAX_PATH] = {0};

	int iDrive = GetPrivateProfileInt( _T("Wrip"), _T("Drive"), 0, csIniFile );
	CWripDlg::Instance()->m_comboDrives.SetCurSel( iDrive );
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 31 );
	TrackInfo::Instance()->Stop();
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 32 );
	DriveInfo::Instance()->SetCurrentDrive( CWripDlg::Instance()->m_comboDrives.GetCurSel() );
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 33 );
	TrackInfo::Instance()->CheckForTracks();
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 34 );
	TrackInfo::Instance()->CheckForTracks();
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 35 );
	CTrackDlg::Instance()->InitTracks();
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 36 );
	FreeDBQuery::StartQuery( NULL );
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 37 );
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 38 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	CWripDlg::Instance()->m_splashDlg->m_progress.SetPos( 39 );
	CTrackDlg::Instance()->m_comboGenre.SetCurSel( -1 );
	CTrackDlg::Instance()->UpdateData( FALSE );

	// COMMON
	GetPrivateProfileString( _T("Wrip"), _T("Destination"), _T(""), szTmp, MAX_PATH, csIniFile );
	CCommonDlg::Instance()->m_csDestination.Format( _T("%s"), szTmp );

	int iFolder = GetPrivateProfileInt( _T("Wrip"), _T("Folder"), 0, csIniFile );
	CCommonDlg::Instance()->m_comboFolder.SetCurSel( iFolder );

	int iFile = GetPrivateProfileInt( _T("Wrip"), _T("File"), 0, csIniFile );
	CCommonDlg::Instance()->m_comboFile.SetCurSel( iFile );

	int iCDDB = GetPrivateProfileInt( _T("Wrip"), _T("CDDB"), 0, csIniFile );
	CCommonDlg::Instance()->m_comboCDDB.SetCurSel( iCDDB );

	BOOL bUseProxy = GetPrivateProfileInt( _T("Wrip"), _T("UseProxy"), 0, csIniFile );
	CCommonDlg::Instance()->m_bProxy = bUseProxy;

	GetPrivateProfileString( _T("Wrip"), _T("Proxy"), _T(""), szTmp, MAX_PATH, csIniFile );
	CCommonDlg::Instance()->m_csProxy.Format( _T("%s"), szTmp );

	int iPort = GetPrivateProfileInt( _T("Wrip"), _T("Port"), 0, csIniFile );
	CCommonDlg::Instance()->m_uiPort = iPort;

	// RIP
	BOOL bUseJitter = GetPrivateProfileInt( _T("Wrip"), _T("UseJitter"), 0, csIniFile );
	CWavDlg::Instance()->m_bJitter = bUseJitter;

	BOOL bDeleteWavAfterEncode = GetPrivateProfileInt( _T("Wrip"), _T("DeleteWavAfterEncode"), 0, csIniFile );
	CWavDlg::Instance()->m_bDeleteAfterEncode = bDeleteWavAfterEncode;

	int iSectors = GetPrivateProfileInt( _T("Wrip"), _T("Sectors"), 0, csIniFile );
	CWavDlg::Instance()->m_iReadSectors = iSectors;

	int iCompare = GetPrivateProfileInt( _T("Wrip"), _T("Compare"), 0, csIniFile );
	CWavDlg::Instance()->m_iBlockCompare = iCompare;

	int iOverlap = GetPrivateProfileInt( _T("Wrip"), _T("Overlap"), 0, csIniFile );
	CWavDlg::Instance()->m_iReadOverlap = iOverlap;

	// ENCODE
	// MP3
	int iEncoder = GetPrivateProfileInt( _T("Wrip"), _T("Encoder"), 0, csIniFile );
	CEncoderDlg::Instance()->m_comboEncoder.SetCurSel( iEncoder );
	CEncoderDlg::Instance()->SetDlgPage( iEncoder );

	int iThreadPriority = GetPrivateProfileInt( _T("Wrip"), _T("ThreadPriority"), 0, csIniFile );
	CEncoderDlg::Instance()->m_comboThreadPriority.SetCurSel( iThreadPriority );

	int iVersion = GetPrivateProfileInt( _T("Wrip"), _T("Version"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboVersion.SetCurSel( iVersion );
	CMp3Dlg::Instance()->m_comboBitrate.ResetContent();
	CMp3Dlg::Instance()->m_comboFrequency.ResetContent();
	if( iVersion == 0 ) {
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("32000") );
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("44100") );
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("48000") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("32") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("40") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("48") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("56") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("64") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("80") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("96") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("112") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("128") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("160") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("192") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("224") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("256") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("320") );
	}
	else {
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("16000") );
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("22050") );
		CMp3Dlg::Instance()->m_comboFrequency.AddString( _T("24000") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("8") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("16") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("24") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("32") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("40") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("48") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("56") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("64") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("80") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("96") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("112") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("128") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("144") );
		CMp3Dlg::Instance()->m_comboBitrate.AddString( _T("160") );
	}

	int iBitrate = GetPrivateProfileInt( _T("Wrip"), _T("Bitrate"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboBitrate.SetCurSel( iBitrate );

	int iFrequency = GetPrivateProfileInt( _T("Wrip"), _T("Frequency"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboFrequency.SetCurSel( iFrequency );

	int iQuality = GetPrivateProfileInt( _T("Wrip"), _T("Quality"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboQuality.SetCurSel( iQuality );

	int iMode = GetPrivateProfileInt( _T("Wrip"), _T("Mode"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboMode.SetCurSel( iMode );

	int iID3 = GetPrivateProfileInt( _T("Wrip"), _T("ID3"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboID3.SetCurSel( iID3 );

	int iPlaylist = GetPrivateProfileInt( _T("Wrip"), _T("Playlist"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboPlaylist.SetCurSel( iPlaylist );

	int iVBRQuality = GetPrivateProfileInt( _T("Wrip"), _T("VBRQuality"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboVBRQuality.SetCurSel( iVBRQuality );

	int iMaxBitrate = GetPrivateProfileInt( _T("Wrip"), _T("MaxBitrate"), 0, csIniFile );
	CMp3Dlg::Instance()->m_comboMaxBitrate.SetCurSel( iMaxBitrate );

	BOOL bUseVBR = GetPrivateProfileInt( _T("Wrip"), _T("UseVBR"), 0, csIniFile );
	CMp3Dlg::Instance()->m_bVBR = bUseVBR;

	BOOL bUseCRC = GetPrivateProfileInt( _T("Wrip"), _T("UseCRC"), 0, csIniFile );
	CMp3Dlg::Instance()->m_bCrc = bUseCRC;

	// OGG
	int iMaxOggBitrate = GetPrivateProfileInt( _T("Wrip"), _T("MaxOggBitrate"), 0, csIniFile );
	COggDlg::Instance()->m_comboMaxBitrate.SetCurSel( iMaxOggBitrate );

	int iNomOggBitrate = GetPrivateProfileInt( _T("Wrip"), _T("NomOggBitrate"), 0, csIniFile );
	COggDlg::Instance()->m_comboNomBitrate.SetCurSel( iNomOggBitrate );

	int iMinOggBitrate = GetPrivateProfileInt( _T("Wrip"), _T("MinOggBitrate"), 0, csIniFile );
	COggDlg::Instance()->m_comboMinBitrate.SetCurSel( iMinOggBitrate );

	int iOggChannels = GetPrivateProfileInt( _T("Wrip"), _T("OggChannels"), 0, csIniFile );
	COggDlg::Instance()->m_comboChannels.SetCurSel( iOggChannels );

	int iOggFrequency = GetPrivateProfileInt( _T("Wrip"), _T("OggFrequency"), 0, csIniFile );
	COggDlg::Instance()->m_comboFrequency.SetCurSel( iOggFrequency );

	int iOggPlaylist = GetPrivateProfileInt( _T("Wrip"), _T("OggPlaylist"), 0, csIniFile );
	COggDlg::Instance()->m_comboPlaylist.SetCurSel( iOggPlaylist );

	int iVBROggQuality = GetPrivateProfileInt( _T("Wrip"), _T("VBROggQuality"), 0, csIniFile );
	COggDlg::Instance()->m_comboVBRQuality.SetCurSel( iVBROggQuality );

	BOOL bUseOggVBR = GetPrivateProfileInt( _T("Wrip"), _T("UseOggVBR"), 0, csIniFile );
	COggDlg::Instance()->m_bVBR = bUseOggVBR;
	if( bUseOggVBR ) {
		COggDlg::Instance()->m_comboMaxBitrate.EnableWindow( FALSE );
		COggDlg::Instance()->m_comboNomBitrate.EnableWindow( FALSE );
		COggDlg::Instance()->m_comboMinBitrate.EnableWindow( FALSE );
		COggDlg::Instance()->m_comboVBRQuality.EnableWindow( TRUE );
	}
	else {
		COggDlg::Instance()->m_comboMaxBitrate.EnableWindow( TRUE );
		COggDlg::Instance()->m_comboNomBitrate.EnableWindow( TRUE );
		COggDlg::Instance()->m_comboMinBitrate.EnableWindow( TRUE );
		COggDlg::Instance()->m_comboVBRQuality.EnableWindow( FALSE );
	}

	// UPDATE DIALOGS
	CCommonDlg::Instance()->UpdateData( FALSE );
	CWavDlg::Instance()->UpdateData( FALSE );
	CMp3Dlg::Instance()->UpdateData( FALSE );
	COggDlg::Instance()->UpdateData( FALSE );
}
