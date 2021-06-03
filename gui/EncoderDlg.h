#if !defined(AFX_ENCODERDLG_H__541ACEF7_AC8F_4549_BC0E_4D2CB4A0E3EC__INCLUDED_)
#define AFX_ENCODERDLG_H__541ACEF7_AC8F_4549_BC0E_4D2CB4A0E3EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncoderDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEncoderDlg 

#include <vector>

class CEncoderDlg : public CDialog
{
// Konstruktion
public:
	void SetDlgPage( int iPage );
	static CEncoderDlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(CEncoderDlg)
	enum { IDD = IDD_ENCODER };
	CComboBox	m_comboThreadPriority;
	CComboBox	m_comboEncoder;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CEncoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CEncoderDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CEncoderDlg)
	afx_msg void OnSelchangeComboThreadpriority();
	afx_msg void OnSelchangeComboEncoder();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitSubDialogs();
	static CEncoderDlg* m_instance;
	void InitCombos();
	std::vector<CDialog*> m_dlgPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ENCODERDLG_H__541ACEF7_AC8F_4549_BC0E_4D2CB4A0E3EC__INCLUDED_
