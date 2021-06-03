// SplashDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "SplashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSplashDlg 


CSplashDlg::CSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplashDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CSplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplashDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplashDlg, CDialog)
	//{{AFX_MSG_MAP(CSplashDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSplashDlg 
