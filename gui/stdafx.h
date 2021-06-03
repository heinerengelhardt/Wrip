// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__65086E59_EE44_4319_ADF6_7B3F6D0882AF__INCLUDED_)
#define AFX_STDAFX_H__65086E59_EE44_4319_ADF6_7B3F6D0882AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC-Socket-Erweiterungen
#include <MMSystem.h>

// CG: Die folgende Zeile wurde von der Komponente "Windows Multimedia" hinzugefügt.
#pragma comment(lib, "winmm.lib")
	#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
//Sie können eine Klasse von CComModule ableiten und dies verwenden, wenn Sie
//etwas überladen wollen. Ändern Sie aber nicht den Namen von _Module
class CWripModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CWripModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__65086E59_EE44_4319_ADF6_7B3F6D0882AF__INCLUDED_)
