// Track.cpp: Implementierung der Klasse Track.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Track.h"
#include "DriveInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Track::Track()
 : iNumber( 0 ), csTitle( _T("") ), csLength( _T("") ), csStart( _T("") )
{

}

Track::~Track()
{

}
