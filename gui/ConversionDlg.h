#if !defined(AFX_CONVERSIONDLG_H__5EB09866_7349_49E9_9D91_47DC5FAE15DB__INCLUDED_)
#define AFX_CONVERSIONDLG_H__5EB09866_7349_49E9_9D91_47DC5FAE15DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConversionDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConversionDlg 

class CConversionDlg : public CDialog
{
// Konstruktion
public:
	static CConversionDlg* Instance();
// Dialogfelddaten
	//{{AFX_DATA(CConversionDlg)
	enum { IDD = IDD_CONVERSION };
	CButton	m_buttonCancel;
	CProgressCtrl	m_progressWAV;
	CProgressCtrl	m_progressMP3;
	CString	m_csWAVCurrentTrack;
	CString	m_csWAVCurrentSector;
	CString	m_csWAVEndSector;
	CString	m_csWAVStartSector;
	CString	m_csWAVPerCent;
	CString	m_csWAVCount;
	CString	m_csMP3PerCent;
	CString	m_csMP3CurrentTrack;
	CString	m_csMP3Count;
	CString	m_csMP3Size;
	CString	m_csWAVCurrentSize;
	CString	m_csWAVSize;
	BOOL	m_bShutdown;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CConversionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	LRESULT OnUpdateDlg( WPARAM wParam, LPARAM lParam );
	LRESULT OnEncFinish( WPARAM wParam, LPARAM lParam );
	LRESULT OnWAVFinish( WPARAM wParam, LPARAM lParam );
	LRESULT OnEncAborted( WPARAM wParam, LPARAM lParam );
	LRESULT OnWAVAborted( WPARAM wParam, LPARAM lParam );

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CConversionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCancel();
	afx_msg void OnCheckShutdown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CConversionDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	static CConversionDlg* m_instance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CONVERSIONDLG_H__5EB09866_7349_49E9_9D91_47DC5FAE15DB__INCLUDED_
