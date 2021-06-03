// DriveInfo.h: Schnittstelle für die Klasse DriveInfo.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVEINFO_H__6C7986F7_A8E2_4F88_A537_01C7C6754255__INCLUDED_)
#define AFX_DRIVEINFO_H__6C7986F7_A8E2_4F88_A537_01C7C6754255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>
#include "akrip/akrip32.h"
#include "Drive.h"

#include <vector>

using std::vector;

class DriveInfo  
{
public:
	void SetCurrentDrive( int iDrive );
	Drive GetCurrentDrive();
	std::vector<Drive> GetDrives();
	int GetNumberOfDrives();
	static DriveInfo* Instance();
	DriveInfo();
	virtual ~DriveInfo();

private:
	int m_iNumberOfDrives;
	std::vector<Drive> m_vDrives;
	static DriveInfo* m_instance;
	void CheckForDrives();
	Drive m_drvCurrentDrive;
};

#endif // !defined(AFX_DRIVEINFO_H__6C7986F7_A8E2_4F88_A537_01C7C6754255__INCLUDED_)
