// WripDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "WripDlg.h"
#include "TrackDlg.h"
#include "InformationDlg.h"
#include "PreferencesDlg.h"
#include "ConversionDlg.h"
#include "DriveInfo.h"
#include "Drive.h"
#include "TrackInfo.h"
#include "Track.h"
#include <vector>
#include <process.h>
#include "Ripper.h"
#include "Encoder.h"
#include "Mp3Encoder.h"
#include "OggEncoder.h"
#include "FreeDBQuery.h"
#include "Mp3Dlg.h"
#include "WavDlg.h"
#include "OggDlg.h"
#include "ID3Tag.h"
#include "CommonDlg.h"
#include <dos.h>
#include <direct.h>
#include <dbt.h>
#include "TimeMeasure.h"
#include "Playlist.h"
#include "OutputInfo.h"
#include "EncoderDlg.h"
#include "IniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_csAbout;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_csAbout = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT_ABOUT, m_csAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWripDlg Dialogfeld

CWripDlg::CWripDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWripDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWripDlg)
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_wtEncodeThread = NULL;
}

CWripDlg* CWripDlg::m_instance = NULL;

CWripDlg* CWripDlg::Instance() {
	if( m_instance == NULL ) {
		m_instance = new CWripDlg();
	}

	return m_instance;
}

void CWripDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWripDlg)
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_buttonRefresh);
	DDX_Control(pDX, IDC_BUTTON_INFO, m_buttonInfo);
	DDX_Control(pDX, IDC_COMBO_DRIVES, m_comboDrives);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_buttonStop);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_buttonPrev);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_buttonPlay);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_buttonNext);
	DDX_Control(pDX, IDC_BUTTON_EJECT, m_buttonEject);
	DDX_Control(pDX, IDC_BUTTON_TOWAV, m_buttonToWav);
	DDX_Control(pDX, IDC_BUTTON_CDDB, m_buttonCddb);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_buttonExit);
	DDX_Control(pDX, IDC_BUTTON_TOMP3, m_buttonToMp3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWripDlg, CDialog)
	//{{AFX_MSG_MAP(CWripDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_TOMP3, OnButtonTomp3)
	ON_BN_CLICKED(IDC_BUTTON_TOWAV, OnButtonTowav)
	ON_BN_CLICKED(IDC_BUTTON_CDDB, OnButtonCddb)
	ON_BN_CLICKED(IDC_BUTTON_EJECT, OnButtonEject)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_DRIVES, OnSelchangeComboDrives)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_COMMAND(ID_MENU_PLAY, OnMenuPlay)
	ON_COMMAND(ID_MENU_STOP, OnMenuStop)
	ON_COMMAND(ID_MENU_TOMP3, OnMenuTomp3)
	ON_COMMAND(ID_MENU_TOWAV, OnMenuTowav)
	ON_WM_SETFOCUS()
	ON_WM_DEVICECHANGE()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_UPDATE, OnUpdateDlg )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWripDlg Nachrichten-Handler

BOOL CWripDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	{
		// Erstellen Sie das QuickInfo-Steuerelement .
		m_tooltip.Create( this );
		m_tooltip.Activate( TRUE );

		// ZU ERLEDIGEN: Verwenden Sie eines der folgenden Formulare, um Steuerelemente hinzuzufügen:
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_PLAY ), _T("Play") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_STOP ), _T("Stop") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_EJECT ), _T("Eject") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_NEXT ), _T("Next") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_PREV ), _T("Previos") );

		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_TOWAV ), _T("Rip Tracks") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_TOMP3 ), _T("Encode Tracks") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_CDDB ), _T("CDDB Query") );
		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_REFRESH ), _T("Refresh Track List") );
	}

	m_statusBar.Create( WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP,
		                CRect(0,0,0,0),
						this,
						-1 );

	SetStatusText( _T("Ready") );

	m_splashDlg = new CSplashDlg();
	m_splashDlg->Create( IDD_SPLASH, NULL );
	m_splashDlg->ShowWindow( SW_SHOW );
	m_splashDlg->m_progress.SetRange( 0, 40 );
	InitCombo();
	m_splashDlg->m_progress.SetPos( 10 );
	InitTabs();
	m_splashDlg->m_progress.SetPos( 20 );
	InitButtons();
	m_splashDlg->m_progress.SetPos( 30 );
	IniFile::LoadSettings();
	m_splashDlg->m_progress.SetPos( 40 );
	m_splashDlg->ShowWindow( SW_HIDE );
	delete m_splashDlg;

	UpdateData( FALSE );
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CWripDlg::InitCombo()
{
	CString csTmp = _T("");
	std::vector<Drive> vDrives = DriveInfo::Instance()->GetDrives();
	for( int i=0; i<vDrives.size(); i++ ) {
		csTmp.Format( _T("%s   %s"), vDrives[i].csLetter, vDrives[i].csDescription );
		m_comboDrives.AddString( csTmp );
	}
	m_comboDrives.SetCurSel( 0 );
}


void CWripDlg::InitButtons()
{
	m_buttonExit.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_EXIT ) );
	m_buttonToMp3.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_TOMP3 ) );
	m_buttonToWav.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_TOWAV ) );
	m_buttonCddb.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_CDDB ) );
	m_buttonEject.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_EJECT ) );
	m_buttonNext.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_NEXT ) );
	m_buttonPlay.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_PLAY ) );
	m_buttonPrev.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_PREV ) );
	m_buttonStop.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_STOP ) );
	m_buttonInfo.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_INFO ) );
	m_buttonRefresh.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_REFRESH ) );
}

void CWripDlg::InitTabs()
{
	m_tab.InsertItem( 0, _T("Tracks") );
	m_tab.InsertItem( 1, _T("Preferences") );
	m_tab.InsertItem( 2, _T("Conversion") );
	m_tab.InsertItem( 3, _T("Information") );

	CTrackDlg::Instance()->Create( IDD_TRACKS, this );
	CPreferencesDlg::Instance()->Create( IDD_PREFERENCES, this );
	CConversionDlg::Instance()->Create( IDD_CONVERSION, this );
	CInformationDlg::Instance()->Create( IDD_INFORMATION, this );

	m_tabPage.push_back( CTrackDlg::Instance() );
	m_tabPage.push_back( CPreferencesDlg::Instance() );
	m_tabPage.push_back( CConversionDlg::Instance() );
	m_tabPage.push_back( CInformationDlg::Instance() );

	m_tabPage[0]->ShowWindow( SW_SHOW );
	m_tab.SetCurSel( 0 );
}

void CWripDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CWripDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CWripDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWripDlg::OnButtonExit() 
{
	if( MessageBox( _T("Really Exit Wrip?"), _T("Exit"), MB_YESNO | MB_ICONEXCLAMATION ) == IDNO ) {
		return;
	}

	CDialog::OnCancel();

	CleanUp();
}

void CWripDlg::OnButtonTomp3() 
{
	BOOL bAnyChecked = FALSE;

	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		if( CTrackDlg::Instance()->m_list.GetCheck( i ) ) {
			bAnyChecked = TRUE;
		}
	}

	if( !bAnyChecked ) {
		MessageBox( _T("Please select one or more tracks."), _T("To MP3"), MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	m_tab.SetCurSel( 2 );
	m_tabPage[0]->ShowWindow( SW_HIDE );
	m_tabPage[1]->ShowWindow( SW_HIDE );
	m_tabPage[2]->ShowWindow( SW_SHOW );
	m_tabPage[3]->ShowWindow( SW_HIDE );

	DisableControls();

	m_wtRipThread = AfxBeginThread( Ripper::StartRip, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );

	TimeMeasure::Instance()->Start();

	if( CEncoderDlg::Instance()->m_comboEncoder.GetCurSel() == 0 ) {
		StartMp3Encoding();
	}
	else {
		StartOggEncoding();
	}
}

void CWripDlg::OnButtonTowav() 
{
	BOOL bAnyChecked = FALSE;

	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		if( CTrackDlg::Instance()->m_list.GetCheck( i ) ) {
			bAnyChecked = TRUE;
		}
	}

	if( !bAnyChecked ) {
		MessageBox( _T("Please select one or more tracks."), _T("To WAV"), MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	m_tab.SetCurSel( 2 );
	m_tabPage[0]->ShowWindow( SW_HIDE );
	m_tabPage[1]->ShowWindow( SW_HIDE );
	m_tabPage[2]->ShowWindow( SW_SHOW );
	m_tabPage[3]->ShowWindow( SW_HIDE );

	DisableControls();

	TimeMeasure::Instance()->Start();

	m_wtRipThread = AfxBeginThread( Ripper::StartRip, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );
}

void CWripDlg::OnButtonCddb()
{
	AfxBeginThread( FreeDBQuery::StartQuery, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );
}

void CWripDlg::OnButtonEject()
{
	DriveInfo::Instance()->GetCurrentDrive().Eject();
}

void CWripDlg::OnButtonStop() 
{
	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	UpdateData( FALSE );
}

void CWripDlg::OnButtonPlay() 
{
	int iTrack = CTrackDlg::Instance()->m_list.GetSelectionMark();
	if( iTrack < 0 ) {
		iTrack = 0;
	}
	CTrackDlg::Instance()->m_list.SetSelectionMark( iTrack );
	CString csTrackName = CTrackDlg::Instance()->m_list.GetItemText( iTrack, 0 );
	TrackInfo::Instance()->Play( ++iTrack );
	CString csTrack = _T("");
	csTrack.Format( _T("Playing track %d (%s)"), iTrack, csTrackName );
	SetStatusText( csTrack );

	UpdateData( FALSE );
}

void CWripDlg::OnButtonPrev() 
{
	int iTrack = CTrackDlg::Instance()->m_list.GetSelectionMark();
	if( iTrack <= 0 ) {
		return;
	}
	CTrackDlg::Instance()->m_list.SetSelectionMark( --iTrack );
	CString csTrackName = CTrackDlg::Instance()->m_list.GetItemText( iTrack, 0 );
	TrackInfo::Instance()->Play( ++iTrack );
	CString csTrack = _T("");
	csTrack.Format( _T("Playing track %d (%s)"), iTrack, csTrackName );
	SetStatusText( csTrack );

	UpdateData( FALSE );
}

void CWripDlg::OnButtonNext() 
{
	int iTrack = CTrackDlg::Instance()->m_list.GetSelectionMark();
	if( iTrack < 0 || (iTrack+1) >= TrackInfo::Instance()->GetNumberOfTracks() ) {
		return;
	}
	CTrackDlg::Instance()->m_list.SetSelectionMark( ++iTrack );
	CString csTrackName = CTrackDlg::Instance()->m_list.GetItemText( iTrack, 0 );
	TrackInfo::Instance()->Play( ++iTrack );
	CString csTrack = _T("");
	csTrack.Format( _T("Playing track %d (%s)"), iTrack, csTrackName );
	SetStatusText( csTrack );

	UpdateData( FALSE );
}

void CWripDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int select = m_tab.GetCurSel();

	switch( select ) {
		case 0: {
			m_tabPage[0]->ShowWindow( SW_SHOW );
			m_tabPage[1]->ShowWindow( SW_HIDE );
			m_tabPage[2]->ShowWindow( SW_HIDE );
			m_tabPage[3]->ShowWindow( SW_HIDE );
			break;
		}

		case 1: {
			m_tabPage[0]->ShowWindow( SW_HIDE );
			m_tabPage[1]->ShowWindow( SW_SHOW );
			m_tabPage[2]->ShowWindow( SW_HIDE );
			m_tabPage[3]->ShowWindow( SW_HIDE );
			break;
		}

		case 2: {
			m_tabPage[0]->ShowWindow( SW_HIDE );
			m_tabPage[1]->ShowWindow( SW_HIDE );
			m_tabPage[2]->ShowWindow( SW_SHOW );
			m_tabPage[3]->ShowWindow( SW_HIDE );
			break;
		}

		case 3: {
			m_tabPage[0]->ShowWindow( SW_HIDE );
			m_tabPage[1]->ShowWindow( SW_HIDE );
			m_tabPage[2]->ShowWindow( SW_HIDE );
			m_tabPage[3]->ShowWindow( SW_SHOW );
			break;
		}

		default: {
			break;
		}
	}

	*pResult = 0;
}

void CWripDlg::OnButtonInfo() 
{
	OSVERSIONINFO ver = {0};
	CString csText = _T("");
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx( &ver );
	CString csType( _T("Windows 9x") );	
	if( ver.dwPlatformId == VER_PLATFORM_WIN32s ) {
		csType = _T("Win32s");
	}
	if( ver.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
		csType = _T("Windows NT");
	}
	csText.Format( _T("Operating System:\n%s version %d.%d (%d %s)"),
					csType,
					ver.dwMajorVersion,
					ver.dwMinorVersion,
					LOWORD( ver.dwBuildNumber ),
					ver.szCSDVersion );

	CString strFreeMemory = _T("");
	CString strFmt = _T("");
	MEMORYSTATUS MemStat = {0};
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus( &MemStat );
	strFmt.LoadString( CG_IDS_PHYSICAL_MEM );
	strFreeMemory.Format( strFmt, MemStat.dwTotalPhys / 1024L );
	csText += _T("\n\nSystem Memory:\n");
	csText += strFreeMemory;

	CString strFreeDiskSpace = _T("");
	struct _diskfree_t diskfree;
	int nDrive = _getdrive();
	if( _getdiskfree(nDrive, &diskfree) == 0 ) {
		strFmt.LoadString( CG_IDS_DISK_SPACE );
		strFreeDiskSpace.Format( strFmt,
			(DWORD)diskfree.avail_clusters *
			(DWORD)diskfree.sectors_per_cluster *
			(DWORD)diskfree.bytes_per_sector / (DWORD) 1024L,
			nDrive-1 + _T('A') );
	}
	else {
		strFreeDiskSpace.LoadString( CG_IDS_DISK_SPACE_UNAVAIL );
	}
	csText += _T("\n\nDisk Space:\n");
	csText += strFreeDiskSpace;

	CHAR szCurrentFolder[MAX_PATH] = {0};
	GetCurrentDirectory( MAX_PATH, szCurrentFolder );
	CString csTmp = _T("");
	csTmp.Format( _T("%s"), szCurrentFolder );
	csText += _T("\n\nWorking Directory:\n");
	csText += csTmp;
	csTmp = _T("");

	std::vector<Drive> vDrives = DriveInfo::Instance()->GetDrives();
	for( int i=0; i<vDrives.size(); i++ ) {
		csTmp.Format( _T("\n\nDrive %s\n%s"), vDrives[i].csLetter, vDrives[i].csDescription );
		csText += csTmp;
	}
	csTmp = _T("");

	MessageBox( csText, _T("System Information"), MB_ICONINFORMATION );
}

void CWripDlg::SetStatusText( const CString& cs )
{
	m_statusBar.SetText( cs, 0, 0 );
}

void CWripDlg::OnClose() 
{
	CDialog::OnCancel();

	CleanUp();
}

void CWripDlg::OnSelchangeComboDrives() 
{
	TrackInfo::Instance()->Stop();
	DriveInfo::Instance()->SetCurrentDrive( m_comboDrives.GetCurSel() );
	TrackInfo::Instance()->CheckForTracks();
	TrackInfo::Instance()->CheckForTracks();
	CTrackDlg::Instance()->InitTracks();

	AfxBeginThread( FreeDBQuery::StartQuery, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );

	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	CTrackDlg::Instance()->m_comboGenre.SetCurSel( -1 );
	CTrackDlg::Instance()->m_csAlbum  = _T("");
	CTrackDlg::Instance()->m_csArtist = _T("");
	CTrackDlg::Instance()->UpdateData( FALSE );
}

void CWripDlg::OnButtonRefresh() 
{
	TrackInfo::Instance()->Stop();
	DriveInfo::Instance()->GetCurrentDrive().CloseDrive();
	TrackInfo::Instance()->CheckForTracks();
	TrackInfo::Instance()->CheckForTracks();
	CTrackDlg::Instance()->InitTracks();

	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	CTrackDlg::Instance()->m_comboGenre.SetCurSel( -1 );
	CTrackDlg::Instance()->m_csAlbum = _T("");
	CTrackDlg::Instance()->m_csArtist = _T("");
	CTrackDlg::Instance()->UpdateData( FALSE );
}


LRESULT CWripDlg::OnUpdateDlg(WPARAM wParam, LPARAM lParam)
{
	UpdateData( FALSE );
	return 0;
}

void CWripDlg::RefreshTrackList()
{
	TrackInfo::Instance()->Stop();
	DriveInfo::Instance()->GetCurrentDrive().CloseDrive();
	TrackInfo::Instance()->CheckForTracks();
	CTrackDlg::Instance()->InitTracks();

	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	CTrackDlg::Instance()->m_comboGenre.SetCurSel( -1 );
	CTrackDlg::Instance()->m_csAlbum = _T("");
	CTrackDlg::Instance()->m_csArtist = _T("");
	CTrackDlg::Instance()->UpdateData( FALSE );
}

void CWripDlg::EnableControls()
{
	m_buttonCddb.EnableWindow( TRUE );
	m_buttonEject.EnableWindow( TRUE );
	m_buttonNext.EnableWindow( TRUE );
	m_buttonPlay.EnableWindow( TRUE );
	m_buttonPrev.EnableWindow( TRUE );
	m_buttonRefresh.EnableWindow( TRUE );
	m_buttonStop.EnableWindow( TRUE );
	m_buttonToMp3.EnableWindow( TRUE );
	m_buttonToWav.EnableWindow( TRUE );
	m_comboDrives.EnableWindow( TRUE );

	CConversionDlg::Instance()->m_buttonCancel.EnableWindow( FALSE );

	CTrackDlg::Instance()->m_buttonSelectAll.EnableWindow( TRUE );
	CTrackDlg::Instance()->m_comboGenre.EnableWindow( TRUE );
	CTrackDlg::Instance()->GetDlgItem( IDC_EDIT_ARTIST )->EnableWindow( TRUE );
	CTrackDlg::Instance()->GetDlgItem( IDC_EDIT_ALBUM )->EnableWindow( TRUE );
	CTrackDlg::Instance()->m_list.EnableWindow( TRUE );

	CCommonDlg::Instance()->m_comboCDDB.EnableWindow( TRUE );
	CCommonDlg::Instance()->m_comboFile.EnableWindow( TRUE );
	CCommonDlg::Instance()->m_comboFolder.EnableWindow( TRUE );
	CCommonDlg::Instance()->GetDlgItem( IDC_CHECK_PROXY )->EnableWindow( TRUE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_DESTINATION )->EnableWindow( TRUE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_PROXY )->EnableWindow( TRUE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_PORT )->EnableWindow( TRUE );
	CCommonDlg::Instance()->m_buttonBrowse.EnableWindow( TRUE );

	CWavDlg::Instance()->GetDlgItem( IDC_CHECK_DELETEAFTERENCODE )->EnableWindow( TRUE );
	CWavDlg::Instance()->GetDlgItem( IDC_CHECK_JITTER )->EnableWindow( TRUE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_READSECTORS )->EnableWindow( TRUE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_BLOCKCOMPARE )->EnableWindow( TRUE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_READOVERLAP )->EnableWindow( TRUE );
	CWavDlg::Instance()->m_buttonReset.EnableWindow( TRUE );

	CEncoderDlg::Instance()->m_comboEncoder.EnableWindow( TRUE );

	CMp3Dlg::Instance()->GetDlgItem( IDC_CHECK_VBR )->EnableWindow( TRUE );
	CMp3Dlg::Instance()->GetDlgItem( IDC_CHECK_CRC )->EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboBitrate.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboFrequency.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboID3.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboMaxBitrate.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboMode.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboPlaylist.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboQuality.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboVBRQuality.EnableWindow( TRUE );
	CMp3Dlg::Instance()->m_comboVersion.EnableWindow( TRUE );

	COggDlg::Instance()->m_comboChannels.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboFrequency.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboMaxBitrate.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboMinBitrate.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboNomBitrate.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboPlaylist.EnableWindow( TRUE );
	COggDlg::Instance()->m_comboVBRQuality.EnableWindow( TRUE );
	COggDlg::Instance()->GetDlgItem( IDC_CHECK_VBR )->EnableWindow( TRUE );
}

void CWripDlg::DisableControls()
{
	m_buttonCddb.EnableWindow( FALSE );
	m_buttonEject.EnableWindow( FALSE );
	m_buttonNext.EnableWindow( FALSE );
	m_buttonPlay.EnableWindow( FALSE );
	m_buttonPrev.EnableWindow( FALSE );
	m_buttonRefresh.EnableWindow( FALSE );
	m_buttonStop.EnableWindow( FALSE );
	m_buttonToMp3.EnableWindow( FALSE );
	m_buttonToWav.EnableWindow( FALSE );
	m_comboDrives.EnableWindow( FALSE );

	CConversionDlg::Instance()->m_buttonCancel.EnableWindow( TRUE );

	CTrackDlg::Instance()->m_buttonSelectAll.EnableWindow( FALSE );
	CTrackDlg::Instance()->m_comboGenre.EnableWindow( FALSE );
	CTrackDlg::Instance()->GetDlgItem( IDC_EDIT_ARTIST )->EnableWindow( FALSE );
	CTrackDlg::Instance()->GetDlgItem( IDC_EDIT_ALBUM )->EnableWindow( FALSE );
	CTrackDlg::Instance()->m_list.EnableWindow( FALSE );

	CCommonDlg::Instance()->m_comboCDDB.EnableWindow( FALSE );
	CCommonDlg::Instance()->m_comboFile.EnableWindow( FALSE );
	CCommonDlg::Instance()->m_comboFolder.EnableWindow( FALSE );
	CCommonDlg::Instance()->GetDlgItem( IDC_CHECK_PROXY )->EnableWindow( FALSE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_DESTINATION )->EnableWindow( FALSE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_PROXY )->EnableWindow( FALSE );
	CCommonDlg::Instance()->GetDlgItem( IDC_EDIT_PORT )->EnableWindow( FALSE );
	CCommonDlg::Instance()->m_buttonBrowse.EnableWindow( FALSE );

	CWavDlg::Instance()->GetDlgItem( IDC_CHECK_DELETEAFTERENCODE )->EnableWindow( FALSE );
	CWavDlg::Instance()->GetDlgItem( IDC_CHECK_JITTER )->EnableWindow( FALSE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_READSECTORS )->EnableWindow( FALSE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_BLOCKCOMPARE )->EnableWindow( FALSE );
	CWavDlg::Instance()->GetDlgItem( IDC_EDIT_READOVERLAP )->EnableWindow( FALSE );
	CWavDlg::Instance()->m_buttonReset.EnableWindow( FALSE );

	CEncoderDlg::Instance()->m_comboEncoder.EnableWindow( FALSE );

	CMp3Dlg::Instance()->GetDlgItem( IDC_CHECK_VBR )->EnableWindow( FALSE );
	CMp3Dlg::Instance()->GetDlgItem( IDC_CHECK_CRC )->EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboBitrate.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboFrequency.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboID3.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboMaxBitrate.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboMode.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboPlaylist.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboQuality.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboVBRQuality.EnableWindow( FALSE );
	CMp3Dlg::Instance()->m_comboVersion.EnableWindow( FALSE );

	COggDlg::Instance()->m_comboChannels.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboFrequency.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboMaxBitrate.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboMinBitrate.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboNomBitrate.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboPlaylist.EnableWindow( FALSE );
	COggDlg::Instance()->m_comboVBRQuality.EnableWindow( FALSE );
	COggDlg::Instance()->GetDlgItem( IDC_CHECK_VBR )->EnableWindow( FALSE );
}

BOOL CWripDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent( pMsg );

	return CDialog::PreTranslateMessage( pMsg );
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_csAbout  = _T("");
	m_csAbout += _T("Wrip version 1.1\r\n");
	m_csAbout += _T("Copyright © 2001 - 2003 by\r\n");
	m_csAbout += _T("Heiner Engelhardt\r\n");
	m_csAbout += _T("engelhardt@dvoid.org\r\n");
	m_csAbout += _T("www.dvoid.org");

	UpdateData( FALSE );

	return TRUE;

}

void CWripDlg::OnMenuPlay()
{
	int iTrack = CTrackDlg::Instance()->m_list.GetSelectionMark();
	if( iTrack < 0 ) {
		iTrack = 0;
	}
	CTrackDlg::Instance()->m_list.SetHotItem( iTrack );
	CString csTrackName = CTrackDlg::Instance()->m_list.GetItemText( iTrack, 0 );
	TrackInfo::Instance()->Play( ++iTrack );
	CString csTrack = _T("");
	csTrack.Format( _T("Playing track %d (%s)"), iTrack, csTrackName );
	SetStatusText( csTrack );

	UpdateData( FALSE );
}

void CWripDlg::OnMenuStop()
{
	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	UpdateData( FALSE );
}

void CWripDlg::OnMenuTomp3() 
{
	BOOL bAnyChecked = FALSE;

	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		if( CTrackDlg::Instance()->m_list.GetCheck( i ) ) {
			bAnyChecked = TRUE;
		}
	}

	if( !bAnyChecked ) {
		MessageBox( _T("Please select one or more tracks."), _T("To MP3"), MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	m_tab.SetCurSel( 2 );
	m_tabPage[0]->ShowWindow( SW_HIDE );
	m_tabPage[1]->ShowWindow( SW_HIDE );
	m_tabPage[2]->ShowWindow( SW_SHOW );
	m_tabPage[3]->ShowWindow( SW_HIDE );

	DisableControls();

	m_wtRipThread = AfxBeginThread( Ripper::StartRip, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );

	TimeMeasure::Instance()->Start();

	if( CEncoderDlg::Instance()->m_comboEncoder.GetCurSel() == 0 ) {
		StartMp3Encoding();
	}
	else {
		StartOggEncoding();
	}	
}

void CWripDlg::OnMenuTowav() 
{
	BOOL bAnyChecked = FALSE;

	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		if( CTrackDlg::Instance()->m_list.GetCheck( i ) ) {
			bAnyChecked = TRUE;
		}
	}

	if( !bAnyChecked ) {
		MessageBox( _T("Please select one or more tracks."), _T("To WAV"), MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	TrackInfo::Instance()->Stop();
	CTrackDlg::Instance()->m_list.SetHotItem( -1 );
	CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
	SetStatusText( _T("Ready") );

	m_tab.SetCurSel( 2 );
	m_tabPage[0]->ShowWindow( SW_HIDE );
	m_tabPage[1]->ShowWindow( SW_HIDE );
	m_tabPage[2]->ShowWindow( SW_SHOW );
	m_tabPage[3]->ShowWindow( SW_HIDE );

	DisableControls();

	TimeMeasure::Instance()->Start();

	m_wtRipThread = AfxBeginThread( Ripper::StartRip, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );	
}

void CWripDlg::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	
	CTrackDlg::Instance()->UpdateData( FALSE );
}

BOOL CWripDlg::OnDeviceChange( UINT nEventType, DWORD dwData )
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR) dwData;
    char szMsg[80] = {0};


    switch( nEventType ) {
		case DBT_DEVICEARRIVAL:
			// See if a CD-ROM or DVD was inserted into a drive.
			if( lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME ) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME) lpdb;

				if( lpdbv->dbcv_flags & DBTF_MEDIA ) { // ARRIVED
					CString csDriveLetter = _T("");
					csDriveLetter.Format( _T("%c:"), FirstDriveFromMask( lpdbv->dbcv_unitmask ) );
					CString csCurrentDriveLetter = DriveInfo::Instance()->GetCurrentDrive().csLetter;
					if( csCurrentDriveLetter == csDriveLetter ) {
						TrackInfo::Instance()->CheckForTracks();
						CTrackDlg::Instance()->InitTracks();
						AfxBeginThread( FreeDBQuery::StartQuery, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );
						CTrackDlg::Instance()->m_list.SetHotItem( -1 );
						CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
						CTrackDlg::Instance()->m_buttonSelectAll.EnableWindow( TRUE );
						m_buttonCddb.EnableWindow( TRUE );
						m_buttonNext.EnableWindow( TRUE );
						m_buttonPlay.EnableWindow( TRUE );
						m_buttonPrev.EnableWindow( TRUE );
						m_buttonStop.EnableWindow( TRUE );
						m_buttonToMp3.EnableWindow( TRUE );
						m_buttonToWav.EnableWindow( TRUE );
					}
				}
			}
			break;

		case DBT_DEVICEREMOVECOMPLETE:
			// See if a CD-ROM or DVD was removed from a drive.
			if( lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME ) {
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME) lpdb;

				if( lpdbv->dbcv_flags & DBTF_MEDIA ) { // REMOVED
					CString csDriveLetter = _T("");
					csDriveLetter.Format( _T("%c:"), FirstDriveFromMask( lpdbv->dbcv_unitmask ) );
					CString csCurrentDriveLetter = DriveInfo::Instance()->GetCurrentDrive().csLetter;
					if( csCurrentDriveLetter == csDriveLetter ) {
						TrackInfo::Instance()->CheckForTracks();
						CTrackDlg::Instance()->InitTracks();
						CTrackDlg::Instance()->m_list.SetHotItem( -1 );
						CTrackDlg::Instance()->m_list.SetSelectionMark( -1 );
						CTrackDlg::Instance()->m_comboGenre.SetCurSel( -1 );
						CTrackDlg::Instance()->m_csAlbum  = _T("");
						CTrackDlg::Instance()->m_csArtist = _T("");
						CTrackDlg::Instance()->m_buttonSelectAll.EnableWindow( FALSE );
						m_buttonCddb.EnableWindow( FALSE );
						m_buttonNext.EnableWindow( FALSE );
						m_buttonPlay.EnableWindow( FALSE );
						m_buttonPrev.EnableWindow( FALSE );
						m_buttonStop.EnableWindow( FALSE );
						m_buttonToMp3.EnableWindow( FALSE );
						m_buttonToWav.EnableWindow( FALSE );
						CTrackDlg::Instance()->UpdateData( FALSE );
					}
				}
			}
			break;
	}

	return CDialog::OnDeviceChange( nEventType, dwData );
}

char CWripDlg::FirstDriveFromMask( ULONG unitmask )
{
	char i = 0;

    for( i=0; i<26; ++i ) {
		if( unitmask & 0x1 ) {
			break;
		}
		unitmask = unitmask >> 1;
	}

	return ( i + 'A' );
}

void CWripDlg::CleanUp()
{
	IniFile::SaveSettings();
	Ripper::StopRip();
	Mp3Encoder::StopEncode();
	TrackInfo::Instance()->Stop();

	delete TimeMeasure::Instance();
	delete Playlist::Instance();
	delete CTrackDlg::Instance();
	delete CCommonDlg::Instance();
	delete CMp3Dlg::Instance();
	delete COggDlg::Instance();
	delete CWavDlg::Instance();
	delete CEncoderDlg::Instance();
	delete CPreferencesDlg::Instance();
	delete CInformationDlg::Instance();
	delete DriveInfo::Instance();
	delete TrackInfo::Instance();
	delete OutputInfo::Instance();
}

void CWripDlg::StartMp3Encoding()
{
	m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );

	CEncoderDlg::Instance()->m_comboThreadPriority.SetCurSel( 2 );

//	switch( CEncoderDlg::Instance()->m_comboThreadPriority.GetCurSel() ) {
//		case 6: {// THREAD_PRIORITY_TIME_CRITICAL
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL );
//			break;
//		}
//
//		case 5: {// THREAD_PRIORITY_HIGHEST	
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_HIGHEST, 0, 0, NULL );
//			break;
//		}
//
//		case 4: {// THREAD_PRIORITY_ABOVE_NORMAL
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL );
//			break;
//		}
//
//		case 3: {// THREAD_PRIORITY_NORMAL
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL );
//			break;
//		}
//
//		case 2: {// THREAD_PRIORITY_BELOW_NORMAL
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );
//			break;
//		}
//
//		case 1: {// THREAD_PRIORITY_LOWEST
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_LOWEST, 0, 0, NULL );
//			break;
//		}
//
//		case 0: {// THREAD_PRIORITY_IDLE
//			m_wtEncodeThread = AfxBeginThread( Mp3Encoder::StartEncode, NULL, THREAD_PRIORITY_IDLE, 0, 0, NULL );
//			break;
//		}
//	}
}

void CWripDlg::StartOggEncoding()
{
	m_wtEncodeThread = AfxBeginThread( OggEncoder::StartEncode, NULL, THREAD_PRIORITY_BELOW_NORMAL, 0, 0, NULL );
}
