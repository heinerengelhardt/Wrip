// Drive.h: Schnittstelle für die Klasse Drive.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVE_H__01DD012A_0041_4531_97A9_461020ADB8DC__INCLUDED_)
#define AFX_DRIVE_H__01DD012A_0041_4531_97A9_461020ADB8DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "akrip/akrip32.h"
#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>

class Drive  
{
public:
	CString GetCDID();
	void CloseDrive();
	void Eject();
	CString csDescription;
	CString csLetter;
	CString csID;
	int iHA;
	int iLUN;
	int iTGT;
	HCDROM hCD;
	Drive();
	virtual ~Drive();

private:
	void OpenDevice();
	void CloseDevice();

	DWORD dwDeviceID;
	MCI_STATUS_PARMS mciStatusParms;
	MCI_OPEN_PARMS mciOpenParms;
	MCI_PLAY_PARMS mciPlayParms;
	MCI_INFO_PARMS mciInfoParms;
	MCI_SET_PARMS mciSetParms;
};

#endif // !defined(AFX_DRIVE_H__01DD012A_0041_4531_97A9_461020ADB8DC__INCLUDED_)
