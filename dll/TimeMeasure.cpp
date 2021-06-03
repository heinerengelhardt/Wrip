// TimeMeasure.cpp: Implementierung der Klasse TimeMeasure.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeMeasure.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

TimeMeasure::TimeMeasure() : m_timeStart( NULL ), m_timeStop( NULL )
{

}

TimeMeasure::~TimeMeasure()
{

}

TimeMeasure* TimeMeasure::m_instance = NULL;

TimeMeasure* TimeMeasure::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new TimeMeasure;
	}

	return m_instance;
}

void TimeMeasure::Start()
{
	m_timeStart = CTime::GetCurrentTime();
}

void TimeMeasure::Stop()
{
	m_timeStop = CTime::GetCurrentTime();
}

CString TimeMeasure::GetElapsedTime()
{
	CTimeSpan timeSpan = m_timeStop - m_timeStart;

	int iHours = timeSpan.GetHours();
	int iMinutes = timeSpan.GetMinutes();
	int iSeconds = timeSpan.GetSeconds();

	if( iSeconds > 3 ) {
		iSeconds -= 3;
	}
	
	CString csTime = _T("");
	csTime.Format( _T("%dh %dm %ds"), iHours, iMinutes, iSeconds );

	return csTime;
}
