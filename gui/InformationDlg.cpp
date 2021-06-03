// InformationDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "InformationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CInformationDlg 


CInformationDlg::CInformationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInformationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInformationDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

CInformationDlg* CInformationDlg::m_instance = NULL;

void CInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInformationDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInformationDlg, CDialog)
	//{{AFX_MSG_MAP(CInformationDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CInformationDlg 

CInformationDlg* CInformationDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CInformationDlg();
	}

	return m_instance;
}
