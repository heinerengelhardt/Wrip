// TrackDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "TrackDlg.h"
#include "WripDlg.h"
#include "TrackInfo.h"
#include "Track.h"
#include <vector>
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTrackDlg 


CTrackDlg::CTrackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackDlg)
	m_csAlbum = _T("");
	m_csArtist = _T("");
	//}}AFX_DATA_INIT
}

CTrackDlg* CTrackDlg::m_instance = NULL;

void CTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackDlg)
	DDX_Control(pDX, IDC_BUTTON_SELECTALL, m_buttonSelectAll);
	DDX_Control(pDX, IDC_COMBO_GENRE, m_comboGenre);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_EDIT_ALBUM, m_csAlbum);
	DDV_MaxChars(pDX, m_csAlbum, 1000);
	DDX_Text(pDX, IDC_EDIT_ARTIST, m_csArtist);
	DDV_MaxChars(pDX, m_csArtist, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrackDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackDlg)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
	ON_BN_CLICKED(IDC_BUTTON_SELECTALL, OnButtonSelectall)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_EN_KILLFOCUS(IDC_EDIT_ARTIST, OnKillfocusEditArtist)
	ON_EN_KILLFOCUS(IDC_EDIT_ALBUM, OnKillfocusEditAlbum)
	ON_CBN_KILLFOCUS(IDC_COMBO_GENRE, OnKillfocusComboGenre)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_UPDATE, OnUpdateDlg )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CTrackDlg 

CTrackDlg* CTrackDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CTrackDlg();
	}

	return m_instance;
}

BOOL CTrackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	{
		// Erstellen Sie das QuickInfo-Steuerelement .
		m_tooltip.Create( this );
		m_tooltip.Activate( TRUE );

		// ZU ERLEDIGEN: Verwenden Sie eines der folgenden Formulare, um Steuerelemente hinzuzufügen:

		m_tooltip.AddTool( GetDlgItem( IDC_BUTTON_SELECTALL ), _T("Select/Unselect all Tracks") );
	}
	
	m_buttonSelectAll.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_ARROW_DOWN ) );

	InitList();
	InitGenre();
	InitTracks();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CTrackDlg::InitList()
{
	LVCOLUMN lvc;
	ZeroMemory( &lvc, sizeof(LVCOLUMN) );

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = _T("Titel");
	lvc.cx = 210;
	lvc.fmt = LVCFMT_LEFT;
	m_list.InsertColumn( 0, &lvc );

	lvc.iSubItem = 1;
	lvc.pszText = _T("Nr");
	lvc.cx = 25;
	lvc.fmt = LVCFMT_RIGHT;
	m_list.InsertColumn( 1, &lvc );

	lvc.iSubItem = 2;
	lvc.pszText = _T("Length");
	lvc.cx = 60;
	lvc.fmt = LVCFMT_RIGHT;
	m_list.InsertColumn( 2, &lvc );

	lvc.iSubItem = 3;
	lvc.pszText = _T("Start");
	lvc.cx = 60;
	lvc.fmt = LVCFMT_RIGHT;
	m_list.InsertColumn( 3 ,&lvc );

	m_imageList.Create( IDB_ICONS, 16, 0, 0xFFFFFF );

	// m_list.SetImageList( &m_imageList, LVSIL_SMALL );

	m_list.SetExtendedStyle( LVS_EX_HEADERDRAGDROP |
		                     LVS_EX_FULLROWSELECT  |
							 LVS_EX_CHECKBOXES     |
							 LVS_EX_GRIDLINES );
}

void CTrackDlg::InitTracks()
{
	m_list.DeleteAllItems();

	if( TrackInfo::Instance()->GetNumberOfTracks() <= 0 ) {
		CWripDlg::Instance()->m_buttonCddb.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonNext.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonPlay.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonPrev.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonStop.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonToMp3.EnableWindow( FALSE );
		CWripDlg::Instance()->m_buttonToWav.EnableWindow( FALSE );
		m_buttonSelectAll.EnableWindow( FALSE );
		m_comboGenre.EnableWindow( FALSE );
		m_list.EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_ARTIST )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_ALBUM )->EnableWindow( FALSE );
		return;
	}
	else {
		CWripDlg::Instance()->m_buttonCddb.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonNext.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonPlay.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonPrev.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonStop.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonToMp3.EnableWindow( TRUE );
		CWripDlg::Instance()->m_buttonToWav.EnableWindow( TRUE );
		m_buttonSelectAll.EnableWindow( TRUE );
		m_comboGenre.EnableWindow( TRUE );
		m_list.EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_ARTIST )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_ALBUM )->EnableWindow( TRUE );
	}

	LVITEM lvi;
	ZeroMemory( &lvi, sizeof(LVITEM) );

	for( int i=0; i<TrackInfo::Instance()->GetNumberOfTracks(); i++ ) {
		m_list.InsertItem( &lvi );
	}

	m_csAlbum  = TrackInfo::Instance()->csAlbum;
	m_csArtist = TrackInfo::Instance()->csArtist;
	if( m_comboGenre.SelectString( -1, TrackInfo::Instance()->csGenre ) == CB_ERR ) {
		m_comboGenre.SelectString( -1, _T("Other") );
	}

	CString csNr = _T("");
	for( int j=0; j<TrackInfo::Instance()->GetNumberOfTracks(); j++ ) {
		csNr.Format( _T("%.2d"), TrackInfo::Instance()->GetTracks()[j].iNumber );
		m_list.SetItemText( j, 0, TrackInfo::Instance()->GetTracks()[j].csTitle );
		m_list.SetItemText( j, 1, csNr );
		m_list.SetItemText( j, 2, TrackInfo::Instance()->GetTracks()[j].csLength );
		m_list.SetItemText( j, 3, TrackInfo::Instance()->GetTracks()[j].csStart );
	}
}

void CTrackDlg::OnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	*pResult = 0;
}

void CTrackDlg::InitGenre()
{
	const char* const genre_names[] = {
		"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge",
	    "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop", "R&B",
		"Rap", "Reggae", "Rock", "Techno", "Industrial", "Alternative", "Ska",
		"Death Metal", "Pranks", "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop",
		"Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental",
		"Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "Alt. Rock",
		"Bass", "Soul", "Punk", "Space", "Meditative", "Instrumental Pop",
		"Instrumental Rock", "Ethnic", "Gothic", "Darkwave", "Techno-Industrial",
		"Electronic", "Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy",
		"Cult", "Gangsta Rap", "Top 40", "Christian Rap", "Pop/Funk", "Jungle",
		"Native American", "Cabaret", "New Wave", "Psychedelic", "Rave",
		"Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz",
		"Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk",
		"Folk/Rock", "National Folk", "Swing", "Fast-Fusion", "Bebob", "Latin",
		"Revival", "Celtic", "Bluegrass", "Avantgarde", "Gothic Rock",
		"Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock",
		"Big Band", "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech",
		"Chanson", "Opera", "Chamber Music", "Sonata", "Symphony", "Booty Bass",
		"Primus", "Porn Groove", "Satire", "Slow Jam", "Club", "Tango", "Samba",
		"Folklore", "Ballad", "Power Ballad", "Rhythmic Soul", "Freestyle", "Duet",
		"Punk Rock", "Drum Solo", "A Cappella", "Euro-House", "Dance Hall",
		"Goa", "Drum & Bass", "Club-House", "Hardcore", "Terror", "Indie",
		"BritPop", "Negerpunk", "Polsk Punk", "Beat", "Christian Gangsta Rap",
		"Heavy Metal", "Black Metal", "Crossover", "Contemporary Christian",
		"Christian Rock", "Merengue", "Salsa", "Thrash Metal", "Anime", "JPop",
		"Synthpop"
	};

	int iGenreCount = ((int)(sizeof genre_names / sizeof (const char* const)));

	for( int i=0; i<iGenreCount; i++ ) {
		m_comboGenre.AddString( genre_names[i] );
	}
}

LRESULT CTrackDlg::OnUpdateDlg( WPARAM wParam, LPARAM lParam )
{
	InitTracks();
	UpdateData( FALSE );
	return 0;
}

void CTrackDlg::OnButtonSelectall() 
{
	static BOOL bChecked = FALSE;

	if( !bChecked ) {
		m_list.SetCheck( -1, TRUE );
		m_buttonSelectAll.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_ARROW_UP ) );
		bChecked = TRUE;
	}
	else {
		m_list.SetCheck( -1, FALSE );
		m_buttonSelectAll.SetIcon( AfxGetApp()->LoadIcon( IDI_ICON_ARROW_DOWN ) );
		bChecked = FALSE;
	}	
}

void CTrackDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POINT p;
	GetCursorPos( &p );

	CMenu menu;
	menu.LoadMenu( IDR_MENU );

	CMenu* pMenu = menu.GetSubMenu( 0 );
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this );

	*pResult = 0;
}


void CTrackDlg::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	CString csItemText = pDispInfo->item.pszText;

	if( csItemText == _T("") ) {
		*pResult = 0;
		return;
	}

	int iSel = m_list.GetSelectionMark();
	m_list.SetItemText( iSel, 0, csItemText );

	TrackInfo::Instance()->GetTracks()[iSel].csTitle = csItemText;
	
	*pResult = 0;
}

void CTrackDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

BOOL CTrackDlg::PreTranslateMessage(MSG* pMsg)
{
	{
		// Diese Nachricht von QuickInfo verarbeiten lassen.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: Dies wurde von der Komponente "QuickInfo" hinzugefügt.
}

void CTrackDlg::OnKillfocusEditArtist() 
{
	UpdateData( TRUE );

	std::vector<CString> vcsSpecialChars;
	vcsSpecialChars.push_back( _T("\\") );
	vcsSpecialChars.push_back( _T("/") );
	vcsSpecialChars.push_back( _T(":") );
	vcsSpecialChars.push_back( _T("*") );
	vcsSpecialChars.push_back( _T("\?") );
	vcsSpecialChars.push_back( _T("\"") );
	vcsSpecialChars.push_back( _T("<") );
	vcsSpecialChars.push_back( _T(">") );
	vcsSpecialChars.push_back( _T("|") );
	vcsSpecialChars.push_back( _T("\0") );
	vcsSpecialChars.push_back( _T(".") );
	for( int i=0; i<vcsSpecialChars.size(); i++ ) {
		m_csArtist.Replace( vcsSpecialChars[i], _T("") );
	}
	m_csArtist.TrimLeft();
	m_csArtist.TrimRight();

	TrackInfo::Instance()->csArtist = m_csArtist;

	UpdateData( FALSE );
}

void CTrackDlg::OnKillfocusEditAlbum() 
{
	UpdateData( TRUE );

	std::vector<CString> vcsSpecialChars;
	vcsSpecialChars.push_back( _T("\\") );
	vcsSpecialChars.push_back( _T("/") );
	vcsSpecialChars.push_back( _T(":") );
	vcsSpecialChars.push_back( _T("*") );
	vcsSpecialChars.push_back( _T("\?") );
	vcsSpecialChars.push_back( _T("\"") );
	vcsSpecialChars.push_back( _T("<") );
	vcsSpecialChars.push_back( _T(">") );
	vcsSpecialChars.push_back( _T("|") );
	vcsSpecialChars.push_back( _T("\0") );
	vcsSpecialChars.push_back( _T(".") );
	for( int i=0; i<vcsSpecialChars.size(); i++ ) {
		m_csAlbum.Replace( vcsSpecialChars[i], _T("") );
	}
	m_csAlbum.TrimLeft();
	m_csAlbum.TrimRight();

	TrackInfo::Instance()->csAlbum = m_csAlbum;

	UpdateData( FALSE );
}

void CTrackDlg::OnKillfocusComboGenre() 
{
	UpdateData( TRUE );
	
	m_comboGenre.GetWindowText( TrackInfo::Instance()->csGenre );
}
