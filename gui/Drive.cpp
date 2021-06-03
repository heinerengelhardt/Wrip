// Drive.cpp: Implementierung der Klasse Drive.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Drive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Drive::Drive()
 : csDescription( _T("") ), csLetter( _T("") ), iLUN( 0 ), iHA( 0 ), csID( _T("") ), iTGT( 0 )
{

}

Drive::~Drive()
{

}

void Drive::Eject()
{
	OpenDevice();

	static BOOL bClosed = TRUE;

	if( bClosed ) {
		DWORD dwFlags = MCI_SET_DOOR_OPEN;
		DWORD dwReturn = mciSendCommand(dwDeviceID,MCI_SET,dwFlags,(DWORD)(LPSTR)&mciSetParms);
		if( dwReturn ) {
			return;
		}

		bClosed = FALSE;
	}
	else {
		DWORD dwFlags = MCI_SET_DOOR_CLOSED;
		DWORD dwReturn = mciSendCommand(dwDeviceID,MCI_SET,dwFlags,(DWORD)(LPSTR)&mciSetParms);
		if(dwReturn) {
			return;
		}

		bClosed = TRUE;
	}

	CloseDevice();
}

void Drive::OpenDevice()
{
	CString csAlias = _T("");

	DWORD dwAliasCount = GetCurrentTime();

	mciOpenParms.wDeviceID = 0;
	mciOpenParms.lpstrDeviceType  = (LPSTR) MCI_DEVTYPE_CD_AUDIO;/*(LPSTR)"cdaudio";*/
	mciOpenParms.lpstrElementName = csLetter;
	mciOpenParms.lpstrAlias       = (LPCSTR) csAlias;
	DWORD dwFlags = MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ALIAS | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;
	DWORD dwReturn = mciSendCommand( 0, MCI_OPEN, dwFlags, (DWORD)(LPSTR)& mciOpenParms);
	if( dwReturn ) {
		return;
	}

	dwDeviceID = mciOpenParms.wDeviceID;
}

void Drive::CloseDevice()
{
	DWORD dwReturn = mciSendCommand( dwDeviceID, MCI_CLOSE, 0, NULL );
	if( dwReturn ) {
		return;
	}
}

void Drive::CloseDrive()
{
	OpenDevice();

	DWORD dwFlags = MCI_SET_DOOR_CLOSED;
	DWORD dwReturn = mciSendCommand(dwDeviceID,MCI_SET,dwFlags,(DWORD)(LPSTR)&mciSetParms);
	if(dwReturn) {
		return;
	}

	CloseDevice();
}

CString Drive::GetCDID()
{
	OpenDevice();

	CHAR szID[80] = {0};
	mciInfoParms.lpstrReturn = szID;
	mciInfoParms.dwRetSize = 80;
	mciSendCommand( dwDeviceID, MCI_INFO, MCI_INFO_MEDIA_IDENTITY | MCI_WAIT, (DWORD)(LPVOID)& mciInfoParms );

	long l_temp = atoi( szID );
	PCHAR buf = strupr( itoa( l_temp, szID, 16 ) );

	CloseDevice();

	return buf;
}
