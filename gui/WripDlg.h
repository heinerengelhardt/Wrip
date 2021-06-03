// WripDlg.h : Header-Datei
//

#if !defined(AFX_WRIPDLG_H__C6F697DF_5655_44C0_B0E4_C0AC623E2873__INCLUDED_)
#define AFX_WRIPDLG_H__C6F697DF_5655_44C0_B0E4_C0AC623E2873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWripDlg Dialogfeld

#include <vector>
#include "SplashDlg.h"

class CWripDlg : public CDialog
{
// Konstruktion
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DisableControls();
	void EnableControls();
	CWinThread* m_wtEncodeThread;
	CWinThread* m_wtRipThread;
	void RefreshTrackList();
	LRESULT OnUpdateDlg( WPARAM wParam, LPARAM lParam );
	void SetStatusText( const CString& cs );
	static CWripDlg* Instance();
	CSplashDlg* m_splashDlg;

	void InitTabs();
	void InitCombo();
	void InitButtons();

// Dialogfelddaten
	//{{AFX_DATA(CWripDlg)
	enum { IDD = IDD_WRIP_DIALOG };
	CButton	m_buttonRefresh;
	CButton	m_buttonInfo;
	CComboBox	m_comboDrives;
	CTabCtrl	m_tab;
	CButton	m_buttonStop;
	CButton	m_buttonPrev;
	CButton	m_buttonPlay;
	CButton	m_buttonNext;
	CButton	m_buttonEject;
	CButton	m_buttonToWav;
	CButton	m_buttonCddb;
	CButton	m_buttonExit;
	CButton	m_buttonToMp3;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CWripDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void StartOggEncoding();
	void StartMp3Encoding();
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CWripDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonTomp3();
	afx_msg void OnButtonTowav();
	afx_msg void OnButtonCddb();
	afx_msg void OnButtonEject();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonNext();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonInfo();
	afx_msg void OnClose();
	afx_msg void OnSelchangeComboDrives();
	afx_msg void OnButtonRefresh();
	afx_msg void OnMenuPlay();
	afx_msg void OnMenuStop();
	afx_msg void OnMenuTomp3();
	afx_msg void OnMenuTowav();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CleanUp();
	CStatusBarCtrl m_statusBar;
	char FirstDriveFromMask (ULONG unitmask);
	CWripDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	static CWripDlg* m_instance;
	std::vector<CDialog*> m_tabPage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_WRIPDLG_H__C6F697DF_5655_44C0_B0E4_C0AC623E2873__INCLUDED_)
