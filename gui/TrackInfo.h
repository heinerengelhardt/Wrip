// TrackInfo.h: Schnittstelle für die Klasse TrackInfo.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKINFO_H__54725195_CA36_4883_BB14_49BB85AEF234__INCLUDED_)
#define AFX_TRACKINFO_H__54725195_CA36_4883_BB14_49BB85AEF234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Track.h"
#include "akrip/akrip32.h"
#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>

class TrackInfo  
{
public:
	void Stop();
	void Play( int iTrack );
	CString GetCDLength();
	std::vector<Track>& GetTracks();
	static TrackInfo* Instance();
	int GetNumberOfTracks();
	TrackInfo();
	void CheckForTracks();
	virtual ~TrackInfo();
	CString csGenre;
	CString csAlbum;
	CString csArtist;

private:
	void CalcTrackData();
	void CalcCDLength();
	CString m_csCDLength;
	void CalcNumberOfTracks();
	void CloseDevice();
	void OpenDevice();
	void SetTimeFormat();
	int m_iNumberOfTracks;
	std::vector<Track> m_vTracks;
	static TrackInfo* m_instance;

	DWORD dwDeviceID;
	MCI_STATUS_PARMS mciStatusParms;
	MCI_OPEN_PARMS mciOpenParms;
	MCI_PLAY_PARMS mciPlayParms;
	MCI_SET_PARMS mciSetParms;
};

#endif // !defined(AFX_TRACKINFO_H__54725195_CA36_4883_BB14_49BB85AEF234__INCLUDED_)
