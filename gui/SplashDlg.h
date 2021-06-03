#if !defined(AFX_SPLASHDLG_H__4BE185AB_DDF5_4D76_B463_2FE492DBE61B__INCLUDED_)
#define AFX_SPLASHDLG_H__4BE185AB_DDF5_4D76_B463_2FE492DBE61B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashDlg.h : Header-Datei
//

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSplashDlg 

class CSplashDlg : public CDialog
{
// Konstruktion
public:
	CSplashDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSplashDlg)
	enum { IDD = IDD_SPLASH };
	CProgressCtrl	m_progress;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSplashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSplashDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPLASHDLG_H__4BE185AB_DDF5_4D76_B463_2FE492DBE61B__INCLUDED_
