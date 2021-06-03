// Mp3Dlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "WripDlg.h"
#include "Mp3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CMp3Dlg 


CMp3Dlg::CMp3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMp3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMp3Dlg)
	m_bVBR = FALSE;
	m_bCrc = FALSE;
	//}}AFX_DATA_INIT
}

CMp3Dlg* CMp3Dlg::m_instance = NULL;


void CMp3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMp3Dlg)
	DDX_Control(pDX, IDC_COMBO_VBRQUALITY, m_comboVBRQuality);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_comboQuality);
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Control(pDX, IDC_COMBO_MAXBITRATE, m_comboMaxBitrate);
	DDX_Control(pDX, IDC_COMBO_FREQUENCY, m_comboFrequency);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_comboBitrate);
	DDX_Control(pDX, IDC_COMBO_PLAYLIST, m_comboPlaylist);
	DDX_Control(pDX, IDC_COMBO_VERSION, m_comboVersion);
	DDX_Control(pDX, IDC_COMBO_ID3, m_comboID3);
	DDX_Check(pDX, IDC_CHECK_VBR, m_bVBR);
	DDX_Check(pDX, IDC_CHECK_CRC, m_bCrc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMp3Dlg, CDialog)
	//{{AFX_MSG_MAP(CMp3Dlg)
	ON_CBN_SELCHANGE(IDC_COMBO_VERSION, OnSelchangeComboVersion)
	ON_BN_CLICKED(IDC_CHECK_VBR, OnCheckVbr)
	ON_BN_CLICKED(IDC_CHECK_CRC, OnCheckCrc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CMp3Dlg 

CMp3Dlg* CMp3Dlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CMp3Dlg();
	}

	return m_instance;
}

BOOL CMp3Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	InitCombos();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CMp3Dlg::InitCombos()
{
	m_comboID3.AddString( _T("None") );
	m_comboID3.AddString( _T("ID3 v2") );
	m_comboID3.SetCurSel( 1 );

	m_comboVersion.AddString( _T("MPEG I") );
	m_comboVersion.AddString( _T("MPEG II") );
	m_comboVersion.SetCurSel( 0 );

	m_comboPlaylist.AddString( _T("None") );
	m_comboPlaylist.AddString( _T("m3u") );
	// m_comboPlaylist.AddString( _T("b4s") );
	m_comboPlaylist.SetCurSel( 0 );

	m_comboQuality.AddString( _T("Normal") );
	m_comboQuality.AddString( _T("Low") );
	m_comboQuality.AddString( _T("High") );
	m_comboQuality.AddString( _T("Voice") );
	m_comboQuality.AddString( _T("R3mix") );
	m_comboQuality.AddString( _T("Very high") );
	m_comboQuality.SetCurSel( 0 );

	m_comboMode.AddString( _T("Stereo") );
	m_comboMode.AddString( _T("Joint-Stereo") );
	m_comboMode.AddString( _T("Dual-Channel") );
	m_comboMode.AddString( _T("Mono") );
	m_comboMode.SetCurSel( 0 );

	m_comboFrequency.AddString( _T("32000") );
	m_comboFrequency.AddString( _T("44100") );
	m_comboFrequency.AddString( _T("48000") );
	m_comboFrequency.SetCurSel( 1 );

	m_comboBitrate.AddString( _T("32") );
	m_comboBitrate.AddString( _T("40") );
	m_comboBitrate.AddString( _T("48") );
	m_comboBitrate.AddString( _T("56") );
	m_comboBitrate.AddString( _T("64") );
	m_comboBitrate.AddString( _T("80") );
	m_comboBitrate.AddString( _T("96") );
	m_comboBitrate.AddString( _T("112") );
	m_comboBitrate.AddString( _T("128") );
	m_comboBitrate.AddString( _T("160") );
	m_comboBitrate.AddString( _T("192") );
	m_comboBitrate.AddString( _T("224") );
	m_comboBitrate.AddString( _T("256") );
	m_comboBitrate.AddString( _T("320") );
	m_comboBitrate.SetCurSel( 10 );

	m_comboMaxBitrate.AddString( _T("32") );
	m_comboMaxBitrate.AddString( _T("40") );
	m_comboMaxBitrate.AddString( _T("48") );
	m_comboMaxBitrate.AddString( _T("56") );
	m_comboMaxBitrate.AddString( _T("64") );
	m_comboMaxBitrate.AddString( _T("80") );
	m_comboMaxBitrate.AddString( _T("96") );
	m_comboMaxBitrate.AddString( _T("112") );
	m_comboMaxBitrate.AddString( _T("128") );
	m_comboMaxBitrate.AddString( _T("160") );
	m_comboMaxBitrate.AddString( _T("192") );
	m_comboMaxBitrate.AddString( _T("224") );
	m_comboMaxBitrate.AddString( _T("256") );
	m_comboMaxBitrate.AddString( _T("320") );
	m_comboMaxBitrate.SetCurSel( 13 );

	m_comboVBRQuality.AddString( _T("0") );
	m_comboVBRQuality.AddString( _T("1") );
	m_comboVBRQuality.AddString( _T("2") );
	m_comboVBRQuality.AddString( _T("3") );
	m_comboVBRQuality.AddString( _T("4") );
	m_comboVBRQuality.AddString( _T("5") );
	m_comboVBRQuality.AddString( _T("6") );
	m_comboVBRQuality.AddString( _T("7") );
	m_comboVBRQuality.AddString( _T("8") );
	m_comboVBRQuality.AddString( _T("9") );
	m_comboVBRQuality.SetCurSel( 5 );
}

void CMp3Dlg::OnSelchangeComboVersion() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	CString csVersion = _T("");
	m_comboVersion.GetWindowText( csVersion );

	m_comboBitrate.ResetContent();
	m_comboFrequency.ResetContent();

	if( csVersion == _T("MPEG I") ) {
		m_comboFrequency.AddString( _T("32000") );
		m_comboFrequency.AddString( _T("44100") );
		m_comboFrequency.AddString( _T("48000") );

		m_comboBitrate.AddString( _T("32") );
		m_comboBitrate.AddString( _T("40") );
		m_comboBitrate.AddString( _T("48") );
		m_comboBitrate.AddString( _T("56") );
		m_comboBitrate.AddString( _T("64") );
		m_comboBitrate.AddString( _T("80") );
		m_comboBitrate.AddString( _T("96") );
		m_comboBitrate.AddString( _T("112") );
		m_comboBitrate.AddString( _T("128") );
		m_comboBitrate.AddString( _T("160") );
		m_comboBitrate.AddString( _T("192") );
		m_comboBitrate.AddString( _T("224") );
		m_comboBitrate.AddString( _T("256") );
		m_comboBitrate.AddString( _T("320") );
	}
	else {
		m_comboFrequency.AddString( _T("16000") );
		m_comboFrequency.AddString( _T("22050") );
		m_comboFrequency.AddString( _T("24000") );

		m_comboBitrate.AddString( _T("8") );
		m_comboBitrate.AddString( _T("16") );
		m_comboBitrate.AddString( _T("24") );
		m_comboBitrate.AddString( _T("32") );
		m_comboBitrate.AddString( _T("40") );
		m_comboBitrate.AddString( _T("48") );
		m_comboBitrate.AddString( _T("56") );
		m_comboBitrate.AddString( _T("64") );
		m_comboBitrate.AddString( _T("80") );
		m_comboBitrate.AddString( _T("96") );
		m_comboBitrate.AddString( _T("112") );
		m_comboBitrate.AddString( _T("128") );
		m_comboBitrate.AddString( _T("144") );
		m_comboBitrate.AddString( _T("160") );
	}

	m_comboFrequency.SetCurSel( 1 );
	m_comboBitrate.SetCurSel( 10 );
}

void CMp3Dlg::OnCheckVbr() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData( TRUE );
	UpdateData( FALSE );
}

void CMp3Dlg::OnCheckCrc() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData( TRUE );
	UpdateData( FALSE );
}
