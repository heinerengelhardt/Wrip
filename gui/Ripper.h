// Ripper.h: Schnittstelle für die Klasse Ripper.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIPPER_H__FFE0C850_722C_4289_8D17_7AE8406560A3__INCLUDED_)
#define AFX_RIPPER_H__FFE0C850_722C_4289_8D17_7AE8406560A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "akrip/akrip32.h"
#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>
#include "Resource.h"

class Ripper 
{
public:
	static void StopRip();
	static UINT StartRip( LPVOID lpParam );
	Ripper();
	virtual ~Ripper();

private:
	static BOOL m_bRun;
	static void SetOutputPath( int iTrack );
	static void WriteWavHeader( FILE* fp, DWORD len );
	static void RipAudio( HCDROM hCD, DWORD dwStart, DWORD dwLen, int iTrack, int iCur, int iSum );
	static void MSB2DWORD( DWORD* d, BYTE* b );
	static LPTRACKBUF NewTrackBuf( DWORD numFrames );
};

#endif // !defined(AFX_RIPPER_H__FFE0C850_722C_4289_8D17_7AE8406560A3__INCLUDED_)
