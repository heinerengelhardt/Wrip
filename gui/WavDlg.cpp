// WavDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "WavDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CWavDlg 


CWavDlg::CWavDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWavDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavDlg)
	m_bJitter = FALSE;
	m_iBlockCompare = 0;
	m_iReadOverlap = 0;
	m_iReadSectors = 0;
	m_bDeleteAfterEncode = FALSE;
	//}}AFX_DATA_INIT
}

CWavDlg* CWavDlg::m_instance = NULL;

void CWavDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavDlg)
	DDX_Control(pDX, IDC_BUTTON_RESET, m_buttonReset);
	DDX_Check(pDX, IDC_CHECK_JITTER, m_bJitter);
	DDX_Text(pDX, IDC_EDIT_BLOCKCOMPARE, m_iBlockCompare);
	DDX_Text(pDX, IDC_EDIT_READOVERLAP, m_iReadOverlap);
	DDX_Text(pDX, IDC_EDIT_READSECTORS, m_iReadSectors);
	DDX_Check(pDX, IDC_CHECK_DELETEAFTERENCODE, m_bDeleteAfterEncode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWavDlg, CDialog)
	//{{AFX_MSG_MAP(CWavDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_READSECTORS, OnKillfocusEditReadsectors)
	ON_EN_KILLFOCUS(IDC_EDIT_BLOCKCOMPARE, OnKillfocusEditBlockcompare)
	ON_EN_KILLFOCUS(IDC_EDIT_READOVERLAP, OnKillfocusEditReadoverlap)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_CHECK_DELETEAFTERENCODE, OnCheckDeleteafterencode)
	ON_BN_CLICKED(IDC_CHECK_JITTER, OnCheckJitter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CWavDlg 

CWavDlg* CWavDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CWavDlg();
	}

	return m_instance;
}

BOOL CWavDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	m_iReadOverlap  = 7;
	m_iBlockCompare = 1;
	m_iReadSectors  = 26;

	m_bDeleteAfterEncode = TRUE;

	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CWavDlg::OnKillfocusEditReadsectors() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );

	if( (m_iReadSectors < 26) || (m_iReadSectors > 400) ) {
		CString csTmp = _T("");
		csTmp.Format( _T("Please specify a value between 26 und 400") );
		MessageBox( csTmp, _T("Read sectors"), MB_OK | MB_ICONEXCLAMATION );
		m_iReadSectors = 26;
	}

	UpdateData( FALSE );
}

void CWavDlg::OnKillfocusEditBlockcompare() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );

	if( m_iBlockCompare > (m_iReadOverlap / 2) || (m_iBlockCompare < 1) ) {
		CString csTmp = _T("");
		csTmp.Format( _T("Please spcify a value between 1 and %d"), (m_iReadOverlap / 2) );
		MessageBox( csTmp, _T("Block compare"), MB_OK | MB_ICONEXCLAMATION );
		m_iBlockCompare = 1;
	}

	UpdateData( FALSE );
}

void CWavDlg::OnKillfocusEditReadoverlap() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );

	if( (m_iReadOverlap > m_iReadSectors) || (m_iReadOverlap < 1) ) {
		CString csTmp = _T("");
		csTmp.Format( _T("Please specify a value between 0 and %d"), m_iReadSectors );
		MessageBox( csTmp, _T("Read overlap"), MB_OK | MB_ICONEXCLAMATION );
		m_iReadOverlap  = 7;
	}

	UpdateData( FALSE );
}

void CWavDlg::OnButtonReset() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	m_iReadOverlap  = 7;
	m_iBlockCompare = 1;
	m_iReadSectors  = 26;

	UpdateData( FALSE );	
}

void CWavDlg::OnCheckDeleteafterencode() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData( TRUE );
	UpdateData( FALSE );
}

void CWavDlg::OnCheckJitter() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData( TRUE );
	UpdateData( FALSE );
}
