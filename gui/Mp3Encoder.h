// Mp3Encoder.h: Schnittstelle für die Klasse Mp3Encoder.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3ENCODER_H__6B2ED95A_8DA2_431D_B052_2D618068F54E__INCLUDED_)
#define AFX_MP3ENCODER_H__6B2ED95A_8DA2_431D_B052_2D618068F54E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "Wrip.h"
#include "Encoder.h"
#include <string>
#include <iostream>
#include <sstream>

class Mp3Encoder : public Encoder
{
public:
	static void StopEncode();
	static UINT StartEncode( LPVOID lParam );
	Mp3Encoder();
	virtual ~Mp3Encoder();

private:
	static int EncodeWAV( int iTrack, int iCur, int iSum );
	static BOOL m_bRun;
};

#endif // !defined(AFX_MP3ENCODER_H__6B2ED95A_8DA2_431D_B052_2D618068F54E__INCLUDED_)
