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


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CSplashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSplashDlg)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_SPLASHDLG_H__4BE185AB_DDF5_4D76_B463_2FE492DBE61B__INCLUDED_
