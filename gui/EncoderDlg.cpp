// EncoderDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wrip.h"
#include "EncoderDlg.h"
#include "WripDlg.h"
#include "Mp3Dlg.h"
#include "OggDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CEncoderDlg 


CEncoderDlg::CEncoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncoderDlg)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

CEncoderDlg* CEncoderDlg::m_instance = NULL;

CEncoderDlg* CEncoderDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CEncoderDlg;
	}

	return m_instance;
}

void CEncoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncoderDlg)
	DDX_Control(pDX, IDC_COMBO_THREADPRIORITY, m_comboThreadPriority);
	DDX_Control(pDX, IDC_COMBO_ENCODER, m_comboEncoder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEncoderDlg, CDialog)
	//{{AFX_MSG_MAP(CEncoderDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_THREADPRIORITY, OnSelchangeComboThreadpriority)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODER, OnSelchangeComboEncoder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CEncoderDlg 

BOOL CEncoderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	InitCombos();
	InitSubDialogs();
	SetDlgPage( 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CEncoderDlg::OnSelchangeComboThreadpriority() 
{
	switch( m_comboThreadPriority.GetCurSel() ) {
		case 6: {// THREAD_PRIORITY_TIME_CRITICAL
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_TIME_CRITICAL );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_TIME_CRITICAL );
			}
			break;
		}

		case 5: {// THREAD_PRIORITY_HIGHEST	
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_HIGHEST );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_HIGHEST );
			}
			break;
		}

		case 4: {// THREAD_PRIORITY_ABOVE_NORMAL
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_ABOVE_NORMAL );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_ABOVE_NORMAL );
			}
			break;
		}

		case 3: {// THREAD_PRIORITY_NORMAL
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_NORMAL );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_NORMAL );
			}
			break;
		}

		case 2: {// THREAD_PRIORITY_BELOW_NORMAL
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_BELOW_NORMAL );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_BELOW_NORMAL );
			}
			break;
		}

		case 1: {// THREAD_PRIORITY_LOWEST
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_LOWEST );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_LOWEST );
			}
			break;
		}

		case 0: {// THREAD_PRIORITY_IDLE
			if( CWripDlg::Instance()->m_wtEncodeThread != NULL ) {
				CWripDlg::Instance()->m_wtEncodeThread->SetThreadPriority( THREAD_PRIORITY_IDLE );
			}
			if( CWripDlg::Instance()->m_wtRipThread != NULL ) {
				CWripDlg::Instance()->m_wtRipThread->SetThreadPriority( THREAD_PRIORITY_IDLE );
			}
			break;
		}
	}
}

void CEncoderDlg::OnSelchangeComboEncoder() 
{
	int iSel = m_comboEncoder.GetCurSel();

	switch( iSel ) {
		case 0: {
			m_dlgPage[0]->ShowWindow( SW_SHOW );
			m_dlgPage[1]->ShowWindow( SW_HIDE );
			break;
		}

		case 1: {
			m_dlgPage[0]->ShowWindow( SW_HIDE );
			m_dlgPage[1]->ShowWindow( SW_SHOW );
			break;
		}

		default: {
			break;
		}
	}
}

void CEncoderDlg::InitCombos()
{
	m_comboThreadPriority.AddString( _T("Idle") );
	m_comboThreadPriority.AddString( _T("Lowest") );
	m_comboThreadPriority.AddString( _T("Below Normal") );
	m_comboThreadPriority.AddString( _T("Normal") );
	m_comboThreadPriority.AddString( _T("Above Normal") );
	m_comboThreadPriority.AddString( _T("Highest") );
	m_comboThreadPriority.AddString( _T("Time Critical") );
	m_comboThreadPriority.SetCurSel( 2 );

	m_comboEncoder.AddString( _T("Lame MP3 Encoder") );
	m_comboEncoder.AddString( _T("Ogg Vorbis Encoder") );
	m_comboEncoder.SetCurSel( 0 );
}

void CEncoderDlg::InitSubDialogs()
{
	CMp3Dlg::Instance()->Create( IDD_MP3, this );
	COggDlg::Instance()->Create( IDD_OGG, this );
	
	m_dlgPage.push_back( CMp3Dlg::Instance() );
	m_dlgPage.push_back( COggDlg::Instance() );
}

void CEncoderDlg::SetDlgPage( int iPage )
{
	switch( iPage ) {
		case 0: {
			m_dlgPage[0]->ShowWindow( SW_SHOW );
			m_dlgPage[1]->ShowWindow( SW_HIDE );
			break;
		}

		case 1: {
			m_dlgPage[0]->ShowWindow( SW_HIDE );
			m_dlgPage[1]->ShowWindow( SW_SHOW );
			break;
		}

		default: {
			break;
		}
	}	
}
