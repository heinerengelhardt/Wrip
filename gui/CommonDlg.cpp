// CommonDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "CommonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCommonDlg 

extern int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

CCommonDlg::CCommonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommonDlg)
	m_csDestination = _T("");
	m_uiPort = 0;
	m_csProxy = _T("");
	m_bProxy = FALSE;
	//}}AFX_DATA_INIT
}

CCommonDlg* CCommonDlg::m_instance = NULL;

void CCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommonDlg)
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_buttonBrowse);
	DDX_Control(pDX, IDC_COMBO_FOLDER, m_comboFolder);
	DDX_Control(pDX, IDC_COMBO_FILE, m_comboFile);
	DDX_Control(pDX, IDC_COMBO_CDDB, m_comboCDDB);
	DDX_Text(pDX, IDC_EDIT_DESTINATION, m_csDestination);
	DDV_MaxChars(pDX, m_csDestination, 10000);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	DDV_MinMaxUInt(pDX, m_uiPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PROXY, m_csProxy);
	DDV_MaxChars(pDX, m_csProxy, 1000);
	DDX_Check(pDX, IDC_CHECK_PROXY, m_bProxy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommonDlg, CDialog)
	//{{AFX_MSG_MAP(CCommonDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_CHECK_PROXY, OnCheckProxy)
	ON_EN_KILLFOCUS(IDC_EDIT_DESTINATION, OnKillfocusEditDestination)
	ON_CBN_KILLFOCUS(IDC_COMBO_FOLDER, OnKillfocusComboFolder)
	ON_CBN_KILLFOCUS(IDC_COMBO_FILE, OnKillfocusComboFile)
	ON_EN_KILLFOCUS(IDC_EDIT_PROXY, OnKillfocusEditProxy)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, OnKillfocusEditPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCommonDlg 

CCommonDlg* CCommonDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CCommonDlg();
	}

	return m_instance;
}

void CCommonDlg::OnButtonBrowse() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	/* Works only if we're Windows 95 capable */
	if( TRUE /*afxData.bWin4*/ ) {
		LPMALLOC pMalloc = NULL;
		/* Gets the Shell's default allocator */
		if( ::SHGetMalloc( &pMalloc ) == NOERROR ) {
			BROWSEINFO bi = {0};
			char pszBuffer[MAX_PATH] = {0};
			LPITEMIDLIST pidl = NULL;
			// Get help on BROWSEINFO struct - it's got all the bit settings.
			bi.hwndOwner = GetSafeHwnd();
			bi.pidlRoot = NULL;
			bi.pszDisplayName = pszBuffer;
			bi.lpszTitle = _T("Select a Directory");
			bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
			bi.lpfn = NULL;
			bi.lParam = 0;
			// This next call issues the dialog box.
			if( ( pidl = ::SHBrowseForFolder( &bi ) ) != NULL ) {
				if( ::SHGetPathFromIDList( pidl, pszBuffer ) ) { 
					// At this point pszBuffer contains the selected path */.
					m_csDestination.Format( _T("%s"), pszBuffer );
				}
				// Free the PIDL allocated by SHBrowseForFolder.
				pMalloc->Free( pidl );
			}
			// Release the shell's allocator.
			pMalloc->Release();
		}
	}

	UpdateData( FALSE );	
}

BOOL CCommonDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// CG: Der folgende Block wurde von der Komponente "QuickInfo" hinzugefügt.
	{
		// Erstellen Sie das QuickInfo-Steuerelement .
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// ZU ERLEDIGEN: Verwenden Sie eines der folgenden Formulare, um Steuerelemente hinzuzufügen:

		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_BROWSE ), _T("Browse Folder") );
	}
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	m_comboCDDB.AddString( _T("cddb.cddb.com") );
	m_comboCDDB.AddString( _T("freedb.freedb.org") );
	m_comboCDDB.AddString( _T("freedb.freedb.de") );
	m_comboCDDB.AddString( _T("at.freedb.org") );
	m_comboCDDB.AddString( _T("au.freedb.org") );
	m_comboCDDB.AddString( _T("bg.freedb.org") );
	m_comboCDDB.AddString( _T("ca.freedb.org") );
	m_comboCDDB.AddString( _T("ca2.freedb.org") );
	m_comboCDDB.AddString( _T("de.freedb.org") );
	m_comboCDDB.SetCurSel( 1 );

	m_comboFolder.AddString( _T("") );
	m_comboFolder.AddString( _T("<artist>") );
	m_comboFolder.AddString( _T("<album>") );
	m_comboFolder.AddString( _T("<artist> - <album>") );
	m_comboFolder.AddString( _T("<artist> [<album>]") );
	m_comboFolder.SetCurSel( 3 );

	m_comboFile.AddString( _T("Track <nr>") );
	m_comboFile.AddString( _T("<nr> - <title>") );
	m_comboFile.AddString( _T("<nr> - <artist> - <title>") );
	m_comboFile.AddString( _T("<nr> - <album> - <artist> - <title>") );
	m_comboFile.AddString( _T("<artist> - <nr> - <title>") );
	m_comboFile.AddString( _T("<album> - <artist> - <title>") );
	m_comboFile.SetCurSel( 4 );

	CHAR szCurDir[MAX_PATH] = {0};
	GetCurrentDirectory( MAX_PATH, szCurDir );
	m_csDestination = szCurDir;
	m_csDestination.TrimLeft();
	m_csDestination.TrimRight();

	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CCommonDlg::OnCheckProxy() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateData( TRUE );
}

void CCommonDlg::OnKillfocusEditDestination() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData( TRUE );
	UpdateData( FALSE );
}

void CCommonDlg::OnKillfocusComboFolder() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );
	UpdateData( FALSE );
}

void CCommonDlg::OnKillfocusComboFile() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );
	UpdateData( FALSE );
}

BOOL CCommonDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: Der folgende Block wurde von der Komponente "QuickInfo" hinzugefügt.
	{
		// Diese Nachricht von QuickInfo verarbeiten lassen.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: Dies wurde von der Komponente "QuickInfo" hinzugefügt.
}

void CCommonDlg::OnKillfocusEditProxy() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );
	UpdateData( FALSE );	
}

void CCommonDlg::OnKillfocusEditPort() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	UpdateData( TRUE );
	UpdateData( FALSE );	
}
