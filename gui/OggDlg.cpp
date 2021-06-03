// OggDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "wrip.h"
#include "OggDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COggDlg 


COggDlg::COggDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COggDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COggDlg)
	m_bVBR = FALSE;
	//}}AFX_DATA_INIT
}

COggDlg* COggDlg::m_instance = NULL;

void COggDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COggDlg)
	DDX_Control(pDX, IDC_COMBO_VBRQUALITY, m_comboVBRQuality);
	DDX_Control(pDX, IDC_COMBO_PLAYLIST, m_comboPlaylist);
	DDX_Control(pDX, IDC_COMBO_FREQUENCY, m_comboFrequency);
	DDX_Control(pDX, IDC_COMBO_CHANNELS, m_comboChannels);
	DDX_Control(pDX, IDC_COMBO_NOMBITRATE, m_comboNomBitrate);
	DDX_Control(pDX, IDC_COMBO_MINBITRATE, m_comboMinBitrate);
	DDX_Control(pDX, IDC_COMBO_MAXBITRATE, m_comboMaxBitrate);
	DDX_Check(pDX, IDC_CHECK_VBR, m_bVBR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COggDlg, CDialog)
	//{{AFX_MSG_MAP(COggDlg)
	ON_BN_CLICKED(IDC_CHECK_VBR, OnCheckVbr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COggDlg 

BOOL COggDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	InitCombos();

	if( m_bVBR ) {
		m_comboMaxBitrate.EnableWindow( FALSE );
		m_comboNomBitrate.EnableWindow( FALSE );
		m_comboMinBitrate.EnableWindow( FALSE );
		m_comboVBRQuality.EnableWindow( TRUE );
	}
	else {
		m_comboMaxBitrate.EnableWindow( TRUE );
		m_comboNomBitrate.EnableWindow( TRUE );
		m_comboMinBitrate.EnableWindow( TRUE );
		m_comboVBRQuality.EnableWindow( FALSE );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

COggDlg* COggDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new COggDlg;
	}

	return m_instance;
}

void COggDlg::InitCombos()
{
	m_comboChannels.AddString( _T("Mono") );
	m_comboChannels.AddString( _T("Stereo") );
	m_comboChannels.SetCurSel( 1 );

	m_comboFrequency.AddString( _T("32000") );
	m_comboFrequency.AddString( _T("44100") );
	m_comboFrequency.AddString( _T("48000") );
	m_comboFrequency.SetCurSel( 1 );

	m_comboPlaylist.AddString( _T("None") );
	m_comboPlaylist.AddString( _T("m3u") );
	// m_comboPlaylist.AddString( _T("b4s") );
	m_comboPlaylist.SetCurSel( 0 );

	m_comboVBRQuality.AddString( _T("1") );
	m_comboVBRQuality.AddString( _T("2") );
	m_comboVBRQuality.AddString( _T("3") );
	m_comboVBRQuality.AddString( _T("4") );
	m_comboVBRQuality.AddString( _T("5") );
	m_comboVBRQuality.AddString( _T("6") );
	m_comboVBRQuality.AddString( _T("7") );
	m_comboVBRQuality.AddString( _T("8") );
	m_comboVBRQuality.AddString( _T("9") );
	m_comboVBRQuality.AddString( _T("10") );
	m_comboVBRQuality.SetCurSel( 3 );

	m_comboMinBitrate.AddString( _T("48") );
	m_comboMinBitrate.AddString( _T("64") );
	m_comboMinBitrate.AddString( _T("80") );
	m_comboMinBitrate.AddString( _T("96") );
	m_comboMinBitrate.AddString( _T("128") );
	m_comboMinBitrate.AddString( _T("160") );
	m_comboMinBitrate.AddString( _T("196") );
	m_comboMinBitrate.AddString( _T("256") );
	m_comboMinBitrate.AddString( _T("350") );
	m_comboMinBitrate.SetCurSel( 4 );

	m_comboNomBitrate.AddString( _T("32") );
	m_comboNomBitrate.AddString( _T("40") );
	m_comboNomBitrate.AddString( _T("48") );
	m_comboNomBitrate.AddString( _T("64") );
	m_comboNomBitrate.AddString( _T("80") );
	m_comboNomBitrate.AddString( _T("96") );
	m_comboNomBitrate.AddString( _T("128") );
	m_comboNomBitrate.AddString( _T("160") );
	m_comboNomBitrate.AddString( _T("196") );
	m_comboNomBitrate.AddString( _T("256") );
	m_comboNomBitrate.AddString( _T("350") );
	m_comboNomBitrate.SetCurSel( 6 );

	m_comboMaxBitrate.AddString( _T("32") );
	m_comboMaxBitrate.AddString( _T("40") );
	m_comboMaxBitrate.AddString( _T("48") );
	m_comboMaxBitrate.AddString( _T("64") );
	m_comboMaxBitrate.AddString( _T("80") );
	m_comboMaxBitrate.AddString( _T("96") );
	m_comboMaxBitrate.AddString( _T("128") );
	m_comboMaxBitrate.AddString( _T("160") );
	m_comboMaxBitrate.AddString( _T("196") );
	m_comboMaxBitrate.AddString( _T("256") );
	m_comboMaxBitrate.AddString( _T("350") );
	m_comboMaxBitrate.SetCurSel( 6 );
}

void COggDlg::OnCheckVbr() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );

	if( m_bVBR ) {
		m_comboMaxBitrate.EnableWindow( FALSE );
		m_comboNomBitrate.EnableWindow( FALSE );
		m_comboMinBitrate.EnableWindow( FALSE );
		m_comboVBRQuality.EnableWindow( TRUE );
	}
	else {
		m_comboMaxBitrate.EnableWindow( TRUE );
		m_comboNomBitrate.EnableWindow( TRUE );
		m_comboMinBitrate.EnableWindow( TRUE );
		m_comboVBRQuality.EnableWindow( FALSE );
	}

	UpdateData( FALSE );
}
