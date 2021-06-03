// Wrip.h : Haupt-Header-Datei für die Anwendung WRIP
//

#if !defined(AFX_WRIP_H__980994FF_EC20_449C_9649_911C0498C918__INCLUDED_)
#define AFX_WRIP_H__980994FF_EC20_449C_9649_911C0498C918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

#include "TR.H"
#include "Wrip_i.h"

#define WM_UPDATE		WM_USER + 23477
#define WM_REFRESH		WM_USER + 23478
#define WM_WAV_FINISH	WM_USER + 23479
#define WM_ENC_FINISH	WM_USER + 23480
#define WM_WAV_ABORTED	WM_USER + 23481
#define WM_ENC_ABORTED	WM_USER + 23482

/////////////////////////////////////////////////////////////////////////////
// CWripApp:
// Siehe Wrip.cpp für die Implementierung dieser Klasse
//

class CWripApp : public CWinApp
{
public:
	CWripApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWripApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CWripApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WRIP_H__980994FF_EC20_449C_9649_911C0498C918__INCLUDED_)
