#if !defined(AFX_WAVDLG_H__A22E0C78_7C0B_466A_9CC9_771AC44980B5__INCLUDED_)
#define AFX_WAVDLG_H__A22E0C78_7C0B_466A_9CC9_771AC44980B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WavDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CWavDlg 

class CWavDlg : public CDialog
{
// Konstruktion
public:
	static CWavDlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(CWavDlg)
	enum { IDD = IDD_WAV };
	CButton	m_buttonReset;
	BOOL	m_bJitter;
	int		m_iBlockCompare;
	int		m_iReadOverlap;
	int		m_iReadSectors;
	BOOL	m_bDeleteAfterEncode;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CWavDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CWavDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditReadsectors();
	afx_msg void OnKillfocusEditBlockcompare();
	afx_msg void OnKillfocusEditReadoverlap();
	afx_msg void OnButtonReset();
	afx_msg void OnCheckDeleteafterencode();
	afx_msg void OnCheckJitter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWavDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	static CWavDlg* m_instance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_WAVDLG_H__A22E0C78_7C0B_466A_9CC9_771AC44980B5__INCLUDED_
