#if !defined(AFX_INFORMATIONDLG_H__EE334437_5FF0_47FF_8932_715ED6004D3C__INCLUDED_)
#define AFX_INFORMATIONDLG_H__EE334437_5FF0_47FF_8932_715ED6004D3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InformationDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInformationDlg 

class CInformationDlg : public CDialog
{
// Konstruktion
public:
	static CInformationDlg* Instance();

// Dialogfelddaten
	//{{AFX_DATA(CInformationDlg)
	enum { IDD = IDD_INFORMATION };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CInformationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CInformationDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CInformationDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	static CInformationDlg* m_instance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_INFORMATIONDLG_H__EE334437_5FF0_47FF_8932_715ED6004D3C__INCLUDED_
