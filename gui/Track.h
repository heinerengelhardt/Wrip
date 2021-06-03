// Track.h: Schnittstelle für die Klasse Track.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACK_H__289EE184_C179_4D63_A380_5294E172E53A__INCLUDED_)
#define AFX_TRACK_H__289EE184_C179_4D63_A380_5294E172E53A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "akrip/akrip32.h"
#include <mmsystem.h>
#include <resapi.h>
#include <direct.h>
#include <winbase.h>

class Track  
{
public:
	CString csTitle;
	CString csLength;
	CString csStart;
	int iNumber;
	Track();
	virtual ~Track();
};

#endif // !defined(AFX_TRACK_H__289EE184_C179_4D63_A380_5294E172E53A__INCLUDED_)
