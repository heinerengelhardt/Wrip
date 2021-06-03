#if !defined(AFX_PREFERENCESDLG_H__E4C4CD9A_FD06_4D38_928A_51110F998425__INCLUDED_)
#define AFX_PREFERENCESDLG_H__E4C4CD9A_FD06_4D38_928A_51110F998425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreferencesDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreferencesDlg 

#include <vector>

class CPreferencesDlg : public CDialog
{
// Konstruktion
private:
	void InitTabs();
	static CPreferencesDlg* m_instance;
	CPreferencesDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	std::vector<CDialog*> m_tabPage;

public:
	static CPreferencesDlg* Instance();
// Dialogfelddaten
	//{{AFX_DATA(CPreferencesDlg)
	enum { IDD = IDD_PREFERENCES };
	CTabCtrl	m_tab;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPreferencesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPreferencesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PREFERENCESDLG_H__E4C4CD9A_FD06_4D38_928A_51110F998425__INCLUDED_
