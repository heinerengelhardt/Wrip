// TimeMeasure.h: Schnittstelle für die Klasse TimeMeasure.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEMEASURE_H__ECD08CE8_EE7D_4594_B33B_58E94D63062B__INCLUDED_)
#define AFX_TIMEMEASURE_H__ECD08CE8_EE7D_4594_B33B_58E94D63062B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TimeMeasure  
{
public:
	CString GetElapsedTime();
	void Stop();
	void Start();
	static TimeMeasure* Instance();
	TimeMeasure();
	virtual ~TimeMeasure();

private:
	static TimeMeasure* m_instance;
	CTime m_timeStart;
	CTime m_timeStop;
};

#endif // !defined(AFX_TIMEMEASURE_H__ECD08CE8_EE7D_4594_B33B_58E94D63062B__INCLUDED_)
