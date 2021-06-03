// FreeDBQuery.h: Schnittstelle für die Klasse FreeDBQuery.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FREEDBQUERY_H__D7E9B5E9_4E33_4EE5_9DAB_A71CB6578ACF__INCLUDED_)
#define AFX_FREEDBQUERY_H__D7E9B5E9_4E33_4EE5_9DAB_A71CB6578ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "akrip/akrip32.h"

class FreeDBQuery  
{
public:
	static UINT StartQuery( LPVOID lpParam );
	FreeDBQuery();
	virtual ~FreeDBQuery();

private:
	static void ReadCDDBDataFromFile();
};

#endif // !defined(AFX_FREEDBQUERY_H__D7E9B5E9_4E33_4EE5_9DAB_A71CB6578ACF__INCLUDED_)
