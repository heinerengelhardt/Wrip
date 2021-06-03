// Playlist.h: Schnittstelle für die Klasse Playlist.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYLIST_H__4887FE8C_9423_4E61_9C5B_ABA0F93203A7__INCLUDED_)
#define AFX_PLAYLIST_H__4887FE8C_9423_4E61_9C5B_ABA0F93203A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Playlist  
{
public:
	static Playlist* Instance();
	void CreateB4S();
	void CreateM3U();
	Playlist();
	virtual ~Playlist();

private:
	static Playlist* m_instance;
};

#endif // !defined(AFX_PLAYLIST_H__4887FE8C_9423_4E61_9C5B_ABA0F93203A7__INCLUDED_)
