// FreeDBQuery.cpp: Implementierung der Klasse FreeDBQuery.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wrip.h"
#include "FreeDBQuery.h"
#include "Resource.h"
#include "WripDlg.h"
#include "Track.h"
#include "Drive.h"
#include "TrackInfo.h"
#include "DriveInfo.h"
#include "CommonDlg.h"
#include "TrackDlg.h"

#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>
#include <vector>
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

FreeDBQuery::FreeDBQuery()
{

}

FreeDBQuery::~FreeDBQuery()
{

}

UINT FreeDBQuery::StartQuery( LPVOID lpParam )
{
	CWripDlg::Instance()->SetStatusText( _T("Retrieving CDDB data...") );
	PostMessage( CWripDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

	CDDBQUERYITEM qi[32] = {0};
	CDDBQUERY query;
	ZeroMemory( &query, sizeof(query) );
	DWORD pID[150] = {0};
	CHAR* buf;
	buf = (CHAR*) GlobalAlloc( GPTR, 32000 );
	CString csCDDBServer = _T("");

	GetCDDBDiskID( DriveInfo::Instance()->GetCurrentDrive().hCD, pID, 150 );

	ZeroMemory( qi, sizeof(qi) );
	query.num = 32;
	query.q   = qi;

	CDDBSetOption( CDDB_OPT_USECDPLAYERINI, "", TRUE );
	CCommonDlg::Instance()->m_comboCDDB.GetWindowText( csCDDBServer );
	CDDBSetOption( CDDB_OPT_SERVER, csCDDBServer.GetBuffer( 0 ), 0 );
	CDDBSetOption( CDDB_OPT_CGI, "/~cddb/cddb.cgi", 0 );
	if( CCommonDlg::Instance()->m_bProxy ) {
		CDDBSetOption( CDDB_OPT_PROXY, CCommonDlg::Instance()->m_csProxy.GetBuffer( 0 ), 0 ); // Server
		CDDBSetOption( CDDB_OPT_PROXYPORT, "", CCommonDlg::Instance()->m_uiPort );  // Port
	}
	CDDBSetOption( CDDB_OPT_USER, "wrip-user@dvoid.org", 0 );
	CDDBSetOption( CDDB_OPT_AGENT, "Wrip 1.0", 0 );
	CDDBQuery( DriveInfo::Instance()->GetCurrentDrive().hCD, &query );

	CString csCateg = qi[0].categ;
	if( csCateg == _T("cdplayerini") ) {
		ReadCDDBDataFromFile();
		return (UINT) 0;
	}

	if( query.num > 0 ) {
		TrackInfo::Instance()->csAlbum  = qi[0].title;
		TrackInfo::Instance()->csArtist = qi[0].artist;
		TrackInfo::Instance()->csGenre  = qi[0].categ;
	}
	else {
		ReadCDDBDataFromFile();
		return (UINT) 0;
	}

	query.num = 0;
	CDDBGetDiskInfo( &qi[query.num], buf, 32000 );

	CString csCDDBData = (CString) buf;
	csCDDBData.TrimLeft();
	csCDDBData.TrimRight();
	csCDDBData.Delete( 0, csCDDBData.Find( _T("TTITLE"), 0 ) );
	csCDDBData.Delete( csCDDBData.Find( _T("EXTD="), 0 ), csCDDBData.GetLength() - csCDDBData.Find( _T("EXTD="), 0 ) );
	std::vector<CString> vcsSpecialChars;
	vcsSpecialChars.push_back( _T("\\") );
	vcsSpecialChars.push_back( _T("/") );
	vcsSpecialChars.push_back( _T(":") );
	vcsSpecialChars.push_back( _T("*") );
	vcsSpecialChars.push_back( _T("\?") );
	vcsSpecialChars.push_back( _T("\"") );
	vcsSpecialChars.push_back( _T("<") );
	vcsSpecialChars.push_back( _T(">") );
	vcsSpecialChars.push_back( _T("|") );
	vcsSpecialChars.push_back( _T("\0") );
	vcsSpecialChars.push_back( _T(".") );
	vcsSpecialChars.push_back( _T("\t") );
	vcsSpecialChars.push_back( _T("\n") );
	vcsSpecialChars.push_back( _T("\r") );
	for( int i=0; i<vcsSpecialChars.size(); i++ ) {
		csCDDBData.Replace( vcsSpecialChars[i], _T(" ") );
	}
	csCDDBData.TrimLeft();
	csCDDBData.TrimRight();
	
	CString csFirst = _T("");
	CString csNext  = _T("");
	CString csTitle = _T("");
	int iFirst = 0;
	int iNext  = 0;
	for( int j=0; j<TrackInfo::Instance()->GetNumberOfTracks(); j++ ) {
		csFirst.Format( _T("TTITLE%d="), j );
		csNext.Format( _T("TTITLE%d="), j+1 );
		iFirst = csCDDBData.Find( csFirst );
		iNext  = csCDDBData.Find( csNext );
		if( iNext == -1 ) {
			iNext = csCDDBData.GetLength();
		}
		csTitle = csCDDBData.Mid( iFirst, iNext - iFirst );
		csTitle.TrimLeft();
		csTitle.TrimRight();
		csTitle.Replace( csFirst, _T("") );
		TrackInfo::Instance()->GetTracks()[j].csTitle = csTitle;
	}

	PostMessage( CTrackDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

	CWripDlg::Instance()->SetStatusText( _T("Ready") );
	PostMessage( CWripDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

	return (UINT) 0;
}

void FreeDBQuery::ReadCDDBDataFromFile()
{
	CString csIniFile = _T("cdplayer.ini");
	CString csCDID = DriveInfo::Instance()->GetCurrentDrive().GetCDID();
	CHAR szArtist[100] = {0};
	CHAR szAlbum[100]  = {0};
	CHAR szGenre[100]  = {0};

	if( !GetPrivateProfileString( csCDID, _T("artist"), _T(""), szArtist, 100, csIniFile ) ) {
		CWripDlg::Instance()->SetStatusText( _T("No CDDB entries found.") );
		PostMessage( CWripDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
		return;
	}
	GetPrivateProfileString( csCDID, _T("title"), _T(""), szAlbum, 100, csIniFile );
	GetPrivateProfileString( csCDID, _T("genre"), _T(""), szGenre, 100, csIniFile );
	
	TrackInfo::Instance()->csAlbum  = (CString) szAlbum;
	TrackInfo::Instance()->csArtist = (CString) szArtist;
	TrackInfo::Instance()->csGenre  = (CString) szGenre;

	std::vector<CString> vcsSpecialChars;
	vcsSpecialChars.push_back( _T("\\") );
	vcsSpecialChars.push_back( _T("/") );
	vcsSpecialChars.push_back( _T(":") );
	vcsSpecialChars.push_back( _T("*") );
	vcsSpecialChars.push_back( _T("\?") );
	vcsSpecialChars.push_back( _T("\"") );
	vcsSpecialChars.push_back( _T("<") );
	vcsSpecialChars.push_back( _T(">") );
	vcsSpecialChars.push_back( _T("|") );
	vcsSpecialChars.push_back( _T("\0") );
	vcsSpecialChars.push_back( _T(".") );

	CHAR szTitle[200] = {0};
	CString csNr = _T("");
	CString csTitle = _T("");
	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		csNr.Format( _T("%d"), i );
		GetPrivateProfileString( csCDID, csNr, _T(""), szTitle, 200, csIniFile );
		csTitle = (CString) szTitle;
		for( int j=0; j<vcsSpecialChars.size(); j++ ) {
			csTitle.Replace( vcsSpecialChars[j], _T(" ") );
		}
		csTitle.TrimLeft();
		csTitle.TrimRight();
		TrackInfo::Instance()->GetTracks()[i].csTitle = csTitle;
	}

	PostMessage( CTrackDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );

	CWripDlg::Instance()->SetStatusText( _T("Ready") );
	PostMessage( CWripDlg::Instance()->GetSafeHwnd(), WM_UPDATE, 0, 0 );
}
