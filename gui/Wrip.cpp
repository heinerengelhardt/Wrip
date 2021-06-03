// Wrip.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "Wrip.h"
#include "WripDlg.h"
#include <initguid.h>
#include "Wrip_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWripApp

BEGIN_MESSAGE_MAP(CWripApp, CWinApp)
	//{{AFX_MSG_MAP(CWripApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWripApp Konstruktion

CWripApp::CWripApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CWripApp-Objekt

CWripApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWripApp Initialisierung

BOOL CWripApp::InitInstance()
{
	if (!InitATL())
		return FALSE;


	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}


	HANDLE hMutexOneInstance = CreateMutex( NULL, TRUE, _T("PreventSecondInstanceOfWrip") );
	BOOL bFound = FALSE;
    
	if( GetLastError() == ERROR_ALREADY_EXISTS ) {
        bFound = TRUE;
	}

    if( hMutexOneInstance ) {
        ReleaseMutex( hMutexOneInstance );
	}
    
	if( bFound ) {
		AfxMessageBox( _T("Wrip is already running") );
		return FALSE;
	}

	if( !AfxSocketInit() ) {
		AfxMessageBox( IDP_SOCKETS_INIT_FAILED );
		return FALSE;
	}

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

//	CWripDlg dlg;
//	m_pMainWnd = &dlg;
//	int nResponse = dlg.DoModal();
	CWripDlg* dlg = CWripDlg::Instance();
	m_pMainWnd = dlg;
	int nResponse = dlg->DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: Fügen Sie hier Code ein, um ein Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	delete dlg;
	return FALSE;
}

	
CWripModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG CWripModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CWripModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CWripModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}


int CWripApp::ExitInstance()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
		CoUninitialize();
	}

	return CWinApp::ExitInstance();

}

BOOL CWripApp::InitATL()
{
	m_bATLInited = TRUE;

#if _WIN32_WINNT >= 0x0400
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	HRESULT hRes = CoInitialize(NULL);
#endif

	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");

	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_WRIP, FALSE);
			_Module.UnregisterServer(TRUE); //TRUE zeigt an, daß die Typbibliothek nicht registriert ist
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_WRIP, TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if (!bRun)
	{
		m_bATLInited = FALSE;
		_Module.Term();
		CoUninitialize();
		return FALSE;
	}

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		CoUninitialize();
		return FALSE;
	}	

	return TRUE;

}
