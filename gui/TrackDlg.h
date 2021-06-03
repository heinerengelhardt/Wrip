#if !defined(AFX_TRACKDLG_H__D5EA21D4_F207_4DA8_BDBF_AD40B8A76173__INCLUDED_)
#define AFX_TRACKDLG_H__D5EA21D4_F207_4DA8_BDBF_AD40B8A76173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrackDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTrackDlg 

class CTrackDlg : public CDialog
{
// Konstruktion
private:
	CImageList m_imageList;
	void InitGenre();
	void InitList();
	static CTrackDlg* m_instance;
	CTrackDlg(CWnd* pParent = NULL);   // Standardkonstruktor

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnUpdateDlg( WPARAM wParam, LPARAM lParam );
	static CTrackDlg* Instance();
	void InitTracks();

// Dialogfelddaten
	//{{AFX_DATA(CTrackDlg)
	enum { IDD = IDD_TRACKS };
	CButton	m_buttonSelectAll;
	CComboBox	m_comboGenre;
	CListCtrl	m_list;
	CString	m_csAlbum;
	CString	m_csArtist;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CTrackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CToolTipCtrl m_tooltip;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CTrackDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSelectall();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditArtist();
	afx_msg void OnKillfocusEditAlbum();
	afx_msg void OnKillfocusComboGenre();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_TRACKDLG_H__D5EA21D4_F207_4DA8_BDBF_AD40B8A76173__INCLUDED_
