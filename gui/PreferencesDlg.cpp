// PreferencesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "PreferencesDlg.h"
#include "CommonDlg.h"
#include "WavDlg.h"
#include "Mp3Dlg.h"
#include "EncoderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPreferencesDlg 


CPreferencesDlg::CPreferencesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreferencesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreferencesDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

CPreferencesDlg* CPreferencesDlg::m_instance = NULL;

void CPreferencesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreferencesDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreferencesDlg, CDialog)
	//{{AFX_MSG_MAP(CPreferencesDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPreferencesDlg 

CPreferencesDlg* CPreferencesDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CPreferencesDlg();
	}

	return m_instance;
}

BOOL CPreferencesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	InitTabs();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CPreferencesDlg::InitTabs()
{
	m_tab.InsertItem( 0, _T("Common") );
	m_tab.InsertItem( 1, _T("Rip") );
	m_tab.InsertItem( 2, _T("Encode") );

	CCommonDlg::Instance()->Create( IDD_COMMON, this );
	CWavDlg::Instance()->Create( IDD_WAV, this );
	CEncoderDlg::Instance()->Create( IDD_ENCODER, this );

	m_tabPage.push_back( CCommonDlg::Instance() );
	m_tabPage.push_back( CWavDlg::Instance() );
	m_tabPage.push_back( CEncoderDlg::Instance() );

	m_tabPage[0]->ShowWindow( SW_SHOW );
	m_tab.SetCurSel( 0 );
}

void CPreferencesDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	int select = m_tab.GetCurSel();

	switch( select ) {
		case 0: {
			m_tabPage[0]->ShowWindow( SW_SHOW );
			m_tabPage[1]->ShowWindow( SW_HIDE );
			m_tabPage[2]->ShowWindow( SW_HIDE );
			break;
		}

		case 1: {
			m_tabPage[0]->ShowWindow( SW_HIDE );
			m_tabPage[1]->ShowWindow( SW_SHOW );
			m_tabPage[2]->ShowWindow( SW_HIDE );
			break;
		}

		case 2: {
			m_tabPage[0]->ShowWindow( SW_HIDE );
			m_tabPage[1]->ShowWindow( SW_HIDE );
			m_tabPage[2]->ShowWindow( SW_SHOW );
			break;
		}

		default: {
			break;
		}
	}
	
	*pResult = 0;
}
