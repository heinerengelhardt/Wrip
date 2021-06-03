// ConversionDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Wrip.h"
#include "WripDlg.h"
#include "ConversionDlg.h"
#include "Ripper.h"
#include "Mp3Encoder.h"
#include "OggEncoder.h"
#include "TimeMeasure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CConversionDlg 


CConversionDlg::CConversionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConversionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConversionDlg)
	m_csWAVCurrentTrack = _T("");
	m_csWAVCurrentSector = _T("");
	m_csWAVEndSector = _T("");
	m_csWAVStartSector = _T("");
	m_csWAVPerCent = _T("");
	m_csWAVCount = _T("");
	m_csMP3PerCent = _T("");
	m_csMP3CurrentTrack = _T("");
	m_csMP3Count = _T("");
	m_csMP3Size = _T("");
	m_csWAVCurrentSize = _T("");
	m_csWAVSize = _T("");
	m_bShutdown = FALSE;
	//}}AFX_DATA_INIT
}

CConversionDlg* CConversionDlg::m_instance = NULL;

void CConversionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConversionDlg)
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_buttonCancel);
	DDX_Control(pDX, IDC_PROGRESS_WAV, m_progressWAV);
	DDX_Control(pDX, IDC_PROGRESS_MP3, m_progressMP3);
	DDX_Text(pDX, IDC_STATIC_WAV_TRACK, m_csWAVCurrentTrack);
	DDV_MaxChars(pDX, m_csWAVCurrentTrack, 1000);
	DDX_Text(pDX, IDC_STATIC_WAV_CURRENTSECTOR, m_csWAVCurrentSector);
	DDV_MaxChars(pDX, m_csWAVCurrentSector, 1000);
	DDX_Text(pDX, IDC_STATIC_WAV_ENDSECTOR, m_csWAVEndSector);
	DDV_MaxChars(pDX, m_csWAVEndSector, 1000);
	DDX_Text(pDX, IDC_STATIC_WAV_STARTSECTOR, m_csWAVStartSector);
	DDV_MaxChars(pDX, m_csWAVStartSector, 1000);
	DDX_Text(pDX, IDC_STATIC_WAV_PERCENT, m_csWAVPerCent);
	DDV_MaxChars(pDX, m_csWAVPerCent, 100);
	DDX_Text(pDX, IDC_STATIC_WAV_COUNT, m_csWAVCount);
	DDV_MaxChars(pDX, m_csWAVCount, 100);
	DDX_Text(pDX, IDC_STATIC_MP3_PERCENT, m_csMP3PerCent);
	DDV_MaxChars(pDX, m_csMP3PerCent, 100);
	DDX_Text(pDX, IDC_STATIC_MP3_TRACK, m_csMP3CurrentTrack);
	DDV_MaxChars(pDX, m_csMP3CurrentTrack, 1000);
	DDX_Text(pDX, IDC_STATIC_MP3_COUNT, m_csMP3Count);
	DDV_MaxChars(pDX, m_csMP3Count, 100);
	DDX_Text(pDX, IDC_STATIC_MP3_SIZE, m_csMP3Size);
	DDV_MaxChars(pDX, m_csMP3Size, 100);
	DDX_Text(pDX, IDC_STATIC_WAV_CURRENTSIZE, m_csWAVCurrentSize);
	DDV_MaxChars(pDX, m_csWAVCurrentSize, 100);
	DDX_Text(pDX, IDC_STATIC_WAV_SIZE, m_csWAVSize);
	DDV_MaxChars(pDX, m_csWAVSize, 100);
	DDX_Check(pDX, IDC_CHECK_SHUTDOWN, m_bShutdown);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConversionDlg, CDialog)
	//{{AFX_MSG_MAP(CConversionDlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_CHECK_SHUTDOWN, OnCheckShutdown)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_UPDATE, OnUpdateDlg )
	ON_MESSAGE( WM_WAV_FINISH, OnWAVFinish )
	ON_MESSAGE( WM_ENC_FINISH, OnEncFinish )
	ON_MESSAGE( WM_WAV_ABORTED, OnWAVAborted )
	ON_MESSAGE( WM_ENC_ABORTED, OnEncAborted )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CConversionDlg 

CConversionDlg* CConversionDlg::Instance()
{
	if( m_instance == NULL ) {
		m_instance = new CConversionDlg();
	}

	return m_instance;
}

LRESULT CConversionDlg::OnUpdateDlg( WPARAM wParam, LPARAM lParam )
{
	UpdateData( FALSE );
	return 0;
}

BOOL CConversionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	m_buttonCancel.EnableWindow( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CConversionDlg::OnButtonCancel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	if( MessageBox( _T("Really cancel?"), _T("Cancel"), MB_YESNO | MB_ICONEXCLAMATION ) == IDNO ) {
		return;
	}
	
	Ripper::StopRip();
	Mp3Encoder::StopEncode();
	OggEncoder::StopEncode();

	Ripper::StopRip();
	Mp3Encoder::StopEncode();
	OggEncoder::StopEncode();

	UpdateData( FALSE );
}

LRESULT CConversionDlg::OnWAVFinish( WPARAM wParam, LPARAM lParam )
{
	UpdateData( TRUE );

	m_csWAVPerCent = _T("finished");
	m_progressWAV.SetPos( -1 );
	m_csWAVCurrentTrack = _T("---");
	m_csWAVCount = _T("( - / - )");
	m_csWAVCurrentSector = _T("");
	m_csWAVEndSector = _T("");
	m_csWAVStartSector = _T("");

	CWripDlg::Instance()->m_wtRipThread = NULL;

	if( CWripDlg::Instance()->m_wtEncodeThread == NULL ) {
		if( m_bShutdown ) {
	        InitiateSystemShutdown( NULL, NULL, (DWORD) 1, TRUE, FALSE );

		    HANDLE hToken = NULL;
			TOKEN_PRIVILEGES tkp = {0};

	        OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken );
		    LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );

	        tkp.PrivilegeCount = 1;
		    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	        AdjustTokenPrivileges( hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0 );

		    ExitWindowsEx( EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE, 0 );
		}
		else {
			CWripDlg::Instance()->EnableControls();
			TimeMeasure::Instance()->Stop();
			CString csMsg = _T("Ripping successful\n\n");
			csMsg += _T("Elapsed Time: ");
			csMsg += TimeMeasure::Instance()->GetElapsedTime();

			MessageBox( csMsg, _T("Rip"), MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND );
		}
	}

	UpdateData( FALSE );

	return 0;
}

LRESULT CConversionDlg::OnEncFinish( WPARAM wParam, LPARAM lParam )
{
	UpdateData( TRUE );

	m_csMP3PerCent = _T("finished");
	m_progressMP3.SetPos( -1 );
	m_csMP3CurrentTrack = _T("---");
	m_csMP3Count = _T("( - / - )");
	m_csMP3Size = _T("");
	m_csWAVCurrentSize = _T("");
	m_csWAVSize = _T("");

	CWripDlg::Instance()->EnableControls();

	CWripDlg::Instance()->m_wtEncodeThread = NULL;

	if( m_bShutdown ) {
	    InitiateSystemShutdown( NULL, NULL, (DWORD) 1, TRUE, FALSE );

	    HANDLE hToken = NULL;
		TOKEN_PRIVILEGES tkp = {0};

	    OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken );
	    LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );

	    tkp.PrivilegeCount = 1;
	    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	    AdjustTokenPrivileges( hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0 );

	    ExitWindowsEx( EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE, 0 );
	}
	else {
		TimeMeasure::Instance()->Stop();
		CString csMsg = _T("Encoding successful\n\n");
		csMsg += _T("Elapsed Time: ");
		csMsg += TimeMeasure::Instance()->GetElapsedTime();

		MessageBox( csMsg, _T("Encode"), MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND );
	}

	UpdateData( FALSE );

	return 0;
}

LRESULT CConversionDlg::OnEncAborted( WPARAM wParam, LPARAM lParam )
{
	m_csMP3PerCent = _T("aborted");
	m_progressMP3.SetPos( -1 );
	m_csMP3CurrentTrack = _T("---");
	m_csMP3Count = _T("( - / - )");
	m_csMP3Size = _T("");
	m_csWAVCurrentSize = _T("");
	m_csWAVSize = _T("");

	CWripDlg::Instance()->EnableControls();

	CWripDlg::Instance()->m_wtEncodeThread = NULL;

	UpdateData( FALSE );

	return 0;
}

LRESULT CConversionDlg::OnWAVAborted( WPARAM wParam, LPARAM lParam )
{
	m_csWAVPerCent = _T("aborted");
	m_progressWAV.SetPos( -1 );
	m_csWAVCurrentTrack = _T("---");
	m_csWAVCount = _T("( - / - )");
	m_csWAVCurrentSector = _T("");
	m_csWAVEndSector = _T("");
	m_csWAVStartSector = _T("");

	CWripDlg::Instance()->EnableControls();

	CWripDlg::Instance()->m_wtRipThread = NULL;

	UpdateData( FALSE );

	return 0;
}

void CConversionDlg::OnCheckShutdown() 
{
	UpdateData( TRUE );
	UpdateData( FALSE );
}
