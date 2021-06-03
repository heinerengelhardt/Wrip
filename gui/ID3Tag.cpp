// ID3Tag.cpp: Implementierung der Klasse ID3Tag.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ID3Tag.h"
#include "TrackInfo.h"
#include "OutputInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ID3Tag::ID3Tag( CString csFile )
{
	m_id3Tag.Link( csFile, ID3TT_ID3V2 );
}

ID3Tag::~ID3Tag()
{

}

void ID3Tag::AddAlbum( CString csAlbum )
{
	ID3_AddAlbum( &m_id3Tag, csAlbum, TRUE );
}

void ID3Tag::AddTitle( CString csTitle )
{
	ID3_AddTitle( &m_id3Tag, csTitle, TRUE );
}

void ID3Tag::AddGenre( CString csGenre )
{
	ID3_AddGenre( &m_id3Tag, csGenre, TRUE );
}

void ID3Tag::AddArtist( CString csArtist )
{
	ID3_AddArtist( &m_id3Tag, csArtist, TRUE );
}

void ID3Tag::AddTrack( int iTrack, int iTotalTracks )
{
	ID3_AddTrack( &m_id3Tag, iTrack, iTotalTracks );
}

void ID3Tag::UpdateID3Tag()
{
	ID3_AddComment( &m_id3Tag, _T("Encoded by Wrip (dvoid.org)"), TRUE );
	m_id3Tag.Update();
}

UINT ID3Tag::StartID3Tag( LPVOID lParam )
{
	int* piTrack = (int*) lParam;
	int iTrack   = *piTrack;

	ID3Tag id3( OutputInfo::Instance()->GetMP3FilePaths()[iTrack] );
	id3.AddAlbum( TrackInfo::Instance()->csAlbum );
	id3.AddArtist( TrackInfo::Instance()->csArtist );
	id3.AddGenre( TrackInfo::Instance()->csGenre );
	id3.AddTitle( TrackInfo::Instance()->GetTracks()[iTrack].csTitle );
	id3.AddTrack( iTrack + 1, TrackInfo::Instance()->GetNumberOfTracks() );
	id3.UpdateID3Tag();

	return (UINT) 0;
}
