// ID3Tag.h: Schnittstelle für die Klasse ID3Tag.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ID3TAG_H__0D37BF79_AFC1_49CB_A407_B1FDD9AD4486__INCLUDED_)
#define AFX_ID3TAG_H__0D37BF79_AFC1_49CB_A407_B1FDD9AD4486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "id3/misc_support.h"

class ID3Tag  
{
public:
	static UINT StartID3Tag( LPVOID lParam );
	void AddTrack( int iTrack, int iTotalTracks );
	void UpdateID3Tag();
	void AddArtist( CString csArtist );
	void AddGenre( CString csGenre );
	void AddTitle( CString csTitle );
	void AddAlbum( CString csAlbum );
	ID3Tag( CString csFile );
	virtual ~ID3Tag();

private:
	ID3_Tag m_id3Tag;
};

#endif // !defined(AFX_ID3TAG_H__0D37BF79_AFC1_49CB_A407_B1FDD9AD4486__INCLUDED_)
