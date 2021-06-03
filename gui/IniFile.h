// IniFile.h: Schnittstelle für die Klasse IniFile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__D638A3F1_4D3B_4411_9057_03851066F811__INCLUDED_)
#define AFX_INIFILE_H__D638A3F1_4D3B_4411_9057_03851066F811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IniFile  
{
public:
	static void LoadSettings();
	static void SaveSettings();
	IniFile();
	virtual ~IniFile();

protected:
	static CString GetCurrentFolder();
};

#endif // !defined(AFX_INIFILE_H__D638A3F1_4D3B_4411_9057_03851066F811__INCLUDED_)
