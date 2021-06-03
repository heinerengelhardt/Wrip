// OutputInfo.cpp: Implementierung der Klasse OutputInfo.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutputInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

OutputInfo::OutputInfo() : m_iSelectedTrackCount( 0 )
{
	
}

OutputInfo::~OutputInfo()
{

}

OutputInfo* OutputInfo::m_instance = NULL;

OutputInfo* OutputInfo::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new OutputInfo();
	}

	return m_instance;
}

void OutputInfo::AddWAVFilePath(CString csPath)
{
	csPath.Replace( _T(".wav"), _T("") );
	csPath.Replace( _T(".mp3"), _T("") );
	csPath += _T(".wav");
	m_vcsWAVPaths.push_back( csPath );
}

void OutputInfo::AddMP3FilePath(CString csPath)
{
	csPath.Replace( _T(".wav"), _T("") );
	csPath.Replace( _T(".mp3"), _T("") );
	csPath += _T(".mp3");
	m_vcsMP3Paths.push_back( csPath );
}

void OutputInfo::AddOGGFilePath(CString csPath)
{
	csPath.Replace( _T(".wav"), _T("") );
	csPath.Replace( _T(".ogg"), _T("") );
	csPath += _T(".ogg");
	m_vcsOGGPaths.push_back( csPath );
}

void OutputInfo::AddWAVFileName(CString csName)
{
	csName.Replace( _T(".wav"), _T("") );
	csName.Replace( _T(".mp3"), _T("") );
	csName += _T(".wav");
	m_vcsWAVNames.push_back( csName );
}

void OutputInfo::AddMP3FileName(CString csName)
{
	csName.Replace( _T(".wav"), _T("") );
	csName.Replace( _T(".mp3"), _T("") );
	csName += _T(".mp3");
	m_vcsMP3Names.push_back( csName );
}

void OutputInfo::AddOGGFileName(CString csName)
{
	csName.Replace( _T(".wav"), _T("") );
	csName.Replace( _T(".ogg"), _T("") );
	csName += _T(".ogg");
	m_vcsOGGNames.push_back( csName );
}

void OutputInfo::ClearWAVFileStuff()
{
	m_vcsWAVPaths.clear();
	m_vcsWAVNames.clear();
	m_vcsPlaylistEntry.clear();
	while( !m_viQueue.empty() ) {
		m_viQueue.pop();
	}
	m_iSelectedTrackCount = 0;
}

void OutputInfo::ClearMP3FileStuff()
{
	m_vcsMP3Paths.clear();
	m_vcsMP3Names.clear();
	m_vcsPlaylistEntry.clear();
	while( !m_viQueue.empty() ) {
		m_viQueue.pop();
	}
	m_iSelectedTrackCount = 0;
}

void OutputInfo::ClearOGGFileStuff()
{
	m_vcsOGGPaths.clear();
	m_vcsOGGNames.clear();
	m_vcsPlaylistEntry.clear();
	while( !m_viQueue.empty() ) {
		m_viQueue.pop();
	}
	m_iSelectedTrackCount = 0;
}

std::vector<CString>& OutputInfo::GetWAVFilePaths()
{
	return m_vcsWAVPaths;
}

std::vector<CString>& OutputInfo::GetMP3FilePaths()
{
	return m_vcsMP3Paths;
}

std::vector<CString>& OutputInfo::GetOGGFilePaths()
{
	return m_vcsOGGPaths;
}

std::vector<CString>& OutputInfo::GetWAVFileNames()
{
	return m_vcsWAVNames;
}

std::vector<CString>& OutputInfo::GetMP3FileNames()
{
	return m_vcsMP3Names;
}

std::vector<CString>& OutputInfo::GetOGGFileNames()
{
	return m_vcsOGGNames;
}

void OutputInfo::PushQueue( int iTrackNr )
{
	m_viQueue.push( iTrackNr );
}

int OutputInfo::PopQueue()
{
	int iRet = m_viQueue.front();
	m_viQueue.pop();

	return iRet;
}

void OutputInfo::WaitUntilData()
{
	while( m_viQueue.empty() ) {
		Sleep( 1000 );
	}
}

void OutputInfo::SetSelectedTrackCount( int iCount )
{
	m_iSelectedTrackCount = iCount;
}

int OutputInfo::GetSelectedTrackCount()
{
	return m_iSelectedTrackCount;
}

void OutputInfo::SetOutputFolder( CString csFolder )
{
	m_csOutputFolder = csFolder;
}

CString OutputInfo::GetOutputFolder()
{
	return m_csOutputFolder;
}

void OutputInfo::AddPlaylistEntry( CString cs )
{
	m_vcsPlaylistEntry.push_back( cs );
}

std::vector<CString>& OutputInfo::GetPlaylistEntries()
{
	return m_vcsPlaylistEntry;
}
