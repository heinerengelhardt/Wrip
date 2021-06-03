#if !defined(AFX_OGGDLG_H__F0F7D6EA_CA41_4E30_B438_75AE6233EED3__INCLUDED_)
#define AFX_OGGDLG_H__F0F7D6EA_CA41_4E30_B438_75AE6233EED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OggDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COggDlg 

class COggDlg : public CDialog
{
// Konstruktion
public:
	static COggDlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(COggDlg)
	enum { IDD = IDD_OGG };
	CComboBox	m_comboVBRQuality;
	CComboBox	m_comboPlaylist;
	CComboBox	m_comboFrequency;
	CComboBox	m_comboChannels;
	CComboBox	m_comboNomBitrate;
	CComboBox	m_comboMinBitrate;
	CComboBox	m_comboMaxBitrate;
	BOOL	m_bVBR;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COggDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	COggDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COggDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckVbr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitCombos();
	static COggDlg* m_instance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OGGDLG_H__F0F7D6EA_CA41_4E30_B438_75AE6233EED3__INCLUDED_
