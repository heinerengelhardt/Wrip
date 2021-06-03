// Wrip.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE WripDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("WRIP.DLL Initializing!\n");
		
		if (!AfxInitExtensionModule(WripDLL, hInstance))
			return 0;

		new CDynLinkLibrary(WripDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("WRIP.DLL Terminating!\n");
		AfxTermExtensionModule(WripDLL);
	}
	return 1;
}
