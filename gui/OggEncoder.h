// OggEncoder.h: Schnittstelle für die Klasse OggEncoder.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGGENCODER_H__804ADBEF_8F36_4324_AE9A_088474B24F2D__INCLUDED_)
#define AFX_OGGENCODER_H__804ADBEF_8F36_4324_AE9A_088474B24F2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "Wrip.h"
#include "Encoder.h"
#include <string>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include "oggvorbis/vorbisenc.h"

class OggEncoder : public Encoder
{
public:
	static int EncodeWAV( int iTrack, int iCur, int iSum );
	static void StopEncode();
	static UINT StartEncode( LPVOID lParam );
	OggEncoder();
	virtual ~OggEncoder();

private:
	static BOOL m_bRun;
};

#endif // !defined(AFX_OGGENCODER_H__804ADBEF_8F36_4324_AE9A_088474B24F2D__INCLUDED_)
