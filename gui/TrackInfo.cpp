// TrackInfo.cpp: Implementierung der Klasse TrackInfo.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackInfo.h"
#include "DriveInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

TrackInfo::TrackInfo()
 : m_iNumberOfTracks( 0 ),
   csGenre( _T("") ),
   csAlbum( _T("") ),
   csArtist( _T("") )
{
	CheckForTracks();
}

TrackInfo::~TrackInfo()
{

}

TrackInfo* TrackInfo::m_instance = NULL;

int TrackInfo::GetNumberOfTracks()
{
	return m_iNumberOfTracks;
}

TrackInfo* TrackInfo::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new TrackInfo();
	}

	return m_instance;
}

std::vector<Track>& TrackInfo::GetTracks()
{
	return m_vTracks;
}

void TrackInfo::CheckForTracks()
{
	m_vTracks.clear();
	m_iNumberOfTracks = 0;

	CloseDevice();
	OpenDevice();
	SetTimeFormat();
	CalcNumberOfTracks();
	CalcTrackData();
	CalcCDLength();
	CloseDevice();
}

void TrackInfo::SetTimeFormat()
{
    mciSetParms.dwTimeFormat = MCI_FORMAT_MSF;

	if ( DWORD dwReturn = mciSendCommand( dwDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD)(LPVOID)& mciSetParms ) ) {
        mciSendCommand(dwDeviceID, MCI_CLOSE, 0, NULL);
        return;
    }
}

void TrackInfo::OpenDevice()
{
	CString csAlias = _T("");

	DWORD dwAliasCount = GetCurrentTime();

	mciOpenParms.wDeviceID = 0;
	mciOpenParms.lpstrDeviceType  = (LPSTR) MCI_DEVTYPE_CD_AUDIO;/*(LPSTR)"cdaudio";*/
	mciOpenParms.lpstrElementName = DriveInfo::Instance()->GetCurrentDrive().csLetter;
	mciOpenParms.lpstrAlias       = (LPCSTR) csAlias;
	DWORD dwFlags = MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ALIAS | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;
	DWORD dwReturn = mciSendCommand( 0, MCI_OPEN, dwFlags, (DWORD)(LPSTR)& mciOpenParms);
	if( dwReturn ) {
		return;
	}

	dwDeviceID = mciOpenParms.wDeviceID;
}

void TrackInfo::CloseDevice()
{
	DWORD dwReturn = mciSendCommand( dwDeviceID, MCI_CLOSE, 0, NULL );
	if( dwReturn ) {
		return;
	}
}

void TrackInfo::CalcNumberOfTracks()
{
    mciStatusParms.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;
    
	if (DWORD dwReturn = mciSendCommand(dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &mciStatusParms)) {
        mciSendCommand(dwDeviceID, MCI_CLOSE, 0, NULL);
        return;
    }
    
	m_iNumberOfTracks = mciStatusParms.dwReturn;
}

void TrackInfo::CalcCDLength()
{
    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
    if ( DWORD dwReturn = mciSendCommand(dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &mciStatusParms)) {
		mciSendCommand(dwDeviceID, MCI_CLOSE, 0, NULL);
        return;
    }

	m_csCDLength.Format( _T("%02d:%02d"), 
					     MCI_MSF_MINUTE( mciStatusParms.dwReturn ), 
						 MCI_MSF_SECOND( mciStatusParms.dwReturn ) );
}

CString TrackInfo::GetCDLength()
{
	return m_csCDLength;
}

void TrackInfo::CalcTrackData()
{
    DWORD dwReturn = 0;
	for( int i=0; i<m_iNumberOfTracks; i++ ) {
        mciStatusParms.dwItem = MCI_STATUS_POSITION;
        mciStatusParms.dwTrack = i+1;
        if( dwReturn = mciSendCommand(dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &mciStatusParms)) {
            mciSendCommand(dwDeviceID, MCI_CLOSE, 0, NULL);
            return;
        }

		Track t;
		t.csStart.Format( _T("%02d:%02d"),
						  MCI_MSF_MINUTE( mciStatusParms.dwReturn ), 
						  MCI_MSF_SECOND( mciStatusParms.dwReturn ) );
		m_vTracks.push_back( t );
    }

    for( int j=0; j<m_iNumberOfTracks; j++ ) {
        mciStatusParms.dwItem = MCI_STATUS_LENGTH;
        mciStatusParms.dwTrack = j+1;
        if (dwReturn = mciSendCommand(dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &mciStatusParms)) {
            mciSendCommand(dwDeviceID, MCI_CLOSE, 0, NULL);
            return;
        }

		m_vTracks[j].csLength.Format( _T("%02d:%02d"),
									  MCI_MSF_MINUTE( mciStatusParms.dwReturn ), 
									  MCI_MSF_SECOND( mciStatusParms.dwReturn ) );
		m_vTracks[j].iNumber = j+1;
		m_vTracks[j].csTitle.Format( _T("Track %.2d"), j+1 );
    }
}

void TrackInfo::Play( int iTrack )
{
	OpenDevice();

	mciSetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	DWORD dwFlags = MCI_SET_TIME_FORMAT;

	DWORD dwReturn = mciSendCommand(dwDeviceID,MCI_SET,dwFlags,(DWORD)(LPSTR)&mciSetParms);
	if( dwReturn ) {
		return;
	}

    mciPlayParms.dwFrom = 0L;
    mciPlayParms.dwTo = 0L;
    mciPlayParms.dwFrom = MCI_MAKE_TMSF(iTrack, 0, 0, 0);
    mciPlayParms.dwTo = MCI_MAKE_TMSF(iTrack + 1, 0, 0, 0);
	dwFlags = MCI_FROM | MCI_TO;
    
	if( iTrack == GetNumberOfTracks() ) {
		dwFlags = MCI_FROM;
		dwReturn = mciSendCommand(dwDeviceID, MCI_PLAY, dwFlags, (DWORD)(LPVOID) &mciPlayParms);
		if( dwReturn ) {
			return;
		}
	}

	dwReturn = mciSendCommand(dwDeviceID, MCI_PLAY, dwFlags, (DWORD)(LPVOID) &mciPlayParms);
	if( dwReturn ) {
		return;
	}

	CloseDevice();
}

void TrackInfo::Stop()
{
	OpenDevice();
	
	mciSetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	DWORD dwFlags = MCI_SET_TIME_FORMAT;

	DWORD dwReturn = mciSendCommand(dwDeviceID,MCI_SET,dwFlags,(DWORD)(LPSTR)&mciSetParms);
	if( dwReturn ) {
		return;
	}

	dwReturn = mciSendCommand( dwDeviceID, MCI_STOP, dwFlags, NULL );
	if( dwReturn ) {
		return;
	}

	CloseDevice();
}
