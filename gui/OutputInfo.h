// OutputInfo.h: Schnittstelle für die Klasse OutputInfo.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTINFO_H__4CBC5F28_BD0A_4CEC_AB1F_EFF97250903C__INCLUDED_)
#define AFX_OUTPUTINFO_H__4CBC5F28_BD0A_4CEC_AB1F_EFF97250903C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <queue>

class OutputInfo  
{
public:
	std::vector<CString>& GetPlaylistEntries();
	void AddPlaylistEntry( CString cs );
	CString GetOutputFolder();
	void SetOutputFolder( CString csFolder );
	int GetSelectedTrackCount();
	void SetSelectedTrackCount( int iCount );
	void WaitUntilData();
	int PopQueue();
	void PushQueue( int iTrackNr );
	std::vector<CString>& GetWAVFileNames();
	std::vector<CString>& GetMP3FileNames();
	std::vector<CString>& GetMP3FilePaths();
	std::vector<CString>& GetOGGFileNames();
	std::vector<CString>& GetOGGFilePaths();
	std::vector<CString>& GetWAVFilePaths();
	void ClearMP3FileStuff();
	void ClearOGGFileStuff();
	void ClearWAVFileStuff();
	void AddMP3FilePath( CString csPath );
	void AddOGGFilePath( CString csPath );
	void AddWAVFilePath( CString csPath );
	void AddMP3FileName( CString csName );
	void AddOGGFileName( CString csName );
	void AddWAVFileName( CString csName );
	static OutputInfo* Instance();
	OutputInfo();
	virtual ~OutputInfo();

private:
	CString m_csOutputFolder;
	static OutputInfo* m_instance;
	std::vector<CString> m_vcsWAVPaths;
	std::vector<CString> m_vcsMP3Paths;
	std::vector<CString> m_vcsOGGPaths;
	std::vector<CString> m_vcsWAVNames;
	std::vector<CString> m_vcsMP3Names;
	std::vector<CString> m_vcsOGGNames;
	std::vector<CString> m_vcsPlaylistEntry;
	std::queue<int>      m_viQueue;
	int m_iSelectedTrackCount;
};

#endif // !defined(AFX_OUTPUTINFO_H__4CBC5F28_BD0A_4CEC_AB1F_EFF97250903C__INCLUDED_)
