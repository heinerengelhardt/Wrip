#if !defined(AFX_MP3DLG_H__1379B4C0_22A5_463D_AD51_B6DD7515620C__INCLUDED_)
#define AFX_MP3DLG_H__1379B4C0_22A5_463D_AD51_B6DD7515620C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mp3Dlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMp3Dlg 

class CMp3Dlg : public CDialog
{
// Konstruktion
public:
	static CMp3Dlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(CMp3Dlg)
	enum { IDD = IDD_MP3 };
	CComboBox	m_comboVBRQuality;
	CComboBox	m_comboQuality;
	CComboBox	m_comboMode;
	CComboBox	m_comboMaxBitrate;
	CComboBox	m_comboFrequency;
	CComboBox	m_comboBitrate;
	CComboBox	m_comboPlaylist;
	CComboBox	m_comboVersion;
	CComboBox	m_comboID3;
	BOOL	m_bVBR;
	BOOL	m_bCrc;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CMp3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CMp3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboVersion();
	afx_msg void OnCheckVbr();
	afx_msg void OnCheckCrc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitCombos();
	static CMp3Dlg* m_instance;
	CMp3Dlg(CWnd* pParent = NULL);   // Standardkonstruktor
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_MP3DLG_H__1379B4C0_22A5_463D_AD51_B6DD7515620C__INCLUDED_
