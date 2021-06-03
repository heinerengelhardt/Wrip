// DriveInfo.cpp: Implementierung der Klasse DriveInfo.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DriveInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

DriveInfo::DriveInfo() : m_iNumberOfDrives( 0 )
{
	CheckForDrives();
}

DriveInfo::~DriveInfo()
{

}

DriveInfo* DriveInfo::m_instance = NULL;

DriveInfo* DriveInfo::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new DriveInfo();
	}

	return m_instance;
}

int DriveInfo::GetNumberOfDrives()
{
	return m_iNumberOfDrives;
}

void DriveInfo::CheckForDrives()
{
	CString csDriveLetter = _T("");
	for( char c='A'; c<='Z'; c++ ) {
		csDriveLetter.Format( _T("%c:"), c );
		if( GetDriveType( csDriveLetter ) == DRIVE_CDROM ) {
			m_iNumberOfDrives++;
			Drive d;
			d.csLetter = csDriveLetter;
			m_vDrives.push_back( d );
		}
	}

    CDLIST cd;
    memset( &cd, 0, sizeof(cd) );

	GETCDHAND cdh;
	memset( &cdh, 0, sizeof(cdh) );

    cd.max = MAXCDLIST;
    GetCDList( &cd );

	if( cd.num == 0 ) {
		return;
	}

	CString csDriveDescription = _T("");
	for(int i=0; i<cd.num; i++) {
		csDriveDescription.Format( _T("%s%s%s     (%d:%d:%d)"),
								   cd.cd[i].info.vendor,
								   cd.cd[i].info.prodId,
								   cd.cd[i].info.rev,
								   cd.cd[i].ha,
								   cd.cd[i].lun,
								   cd.cd[i].tgt );

		m_vDrives[i].csDescription = csDriveDescription;
		m_vDrives[i].csID          = cd.cd[i].id;
		m_vDrives[i].iHA           = cd.cd[i].ha;
		m_vDrives[i].iLUN          = cd.cd[i].lun;
		m_vDrives[i].iTGT          = cd.cd[i].tgt;

		memset( &cdh, 0, sizeof(cdh) );

		cdh.size           = sizeof(GETCDHAND);
		cdh.ver            = 1;
		cdh.ha             = cd.cd[i].ha;
		cdh.tgt            = cd.cd[i].tgt;
		cdh.lun            = cd.cd[i].lun;
		cdh.readType       = CDR_ANY;

		m_vDrives[i].hCD   = GetCDHandle( &cdh );
	}

	SetCurrentDrive( 0 );
}

std::vector<Drive> DriveInfo::GetDrives()
{
	return m_vDrives;
}

Drive DriveInfo::GetCurrentDrive()
{
	return m_drvCurrentDrive;
}

void DriveInfo::SetCurrentDrive( int iDrive )
{
	if( iDrive < m_vDrives.size() ) {
		m_drvCurrentDrive = m_vDrives[iDrive];
		m_drvCurrentDrive.CloseDrive();
	}
}
