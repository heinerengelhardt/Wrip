#if !defined(AFX_COMMONDLG_H__2B3C1A73_19BC_4066_9A78_57E8B0A180BC__INCLUDED_)
#define AFX_COMMONDLG_H__2B3C1A73_19BC_4066_9A78_57E8B0A180BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommonDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCommonDlg 

class CCommonDlg : public CDialog
{
// Konstruktion
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static CCommonDlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(CCommonDlg)
	enum { IDD = IDD_COMMON };
	CButton	m_buttonBrowse;
	CComboBox	m_comboFolder;
	CComboBox	m_comboFile;
	CComboBox	m_comboCDDB;
	CString	m_csDestination;
	UINT	m_uiPort;
	CString	m_csProxy;
	BOOL	m_bProxy;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CCommonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CToolTipCtrl m_tooltip;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CCommonDlg)
	afx_msg void OnButtonBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckProxy();
	afx_msg void OnKillfocusEditDestination();
	afx_msg void OnKillfocusComboFolder();
	afx_msg void OnKillfocusComboFile();
	afx_msg void OnKillfocusEditProxy();
	afx_msg void OnKillfocusEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CCommonDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	static CCommonDlg* m_instance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_COMMONDLG_H__2B3C1A73_19BC_4066_9A78_57E8B0A180BC__INCLUDED_
