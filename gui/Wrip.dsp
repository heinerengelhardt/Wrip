# Microsoft Developer Studio Project File - Name="Wrip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Wrip - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Wrip.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Wrip.mak" CFG="Wrip - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Wrip - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Wrip - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wrip - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin/release"
# PROP Intermediate_Dir "tmp/release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D ID3LIB_LINKOPTION=1 /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib akrip/akrip.lib id3/id3lib.lib oggvorbis/ogg_static.lib oggvorbis/vorbis_static.lib oggvorbis/vorbisenc_static.lib lib/Wrip.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Wrip - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin/debug"
# PROP Intermediate_Dir "tmp/debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D ID3LIB_LINKOPTION=1 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib akrip/akrip.lib id3/id3lib.lib oggvorbis/ogg_static.lib oggvorbis/vorbis_static.lib oggvorbis/vorbisenc_static.lib lib/Wrip.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Wrip - Win32 Release"
# Name "Wrip - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CommonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConversionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Drive.cpp
# End Source File
# Begin Source File

SOURCE=.\DriveInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\EncoderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeDBQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3Tag.cpp
# End Source File
# Begin Source File

SOURCE=.\InformationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp3Encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\OggDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OggEncoder.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Playlist.cpp
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ripper.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Track.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WavDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Wrip.cpp
# End Source File
# Begin Source File

SOURCE=.\Wrip.idl
# ADD MTL /h "Wrip_i.h" /iid "Wrip_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\Wrip.rc
# End Source File
# Begin Source File

SOURCE=.\WripDlg.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CommonDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConversionDlg.h
# End Source File
# Begin Source File

SOURCE=.\Drive.h
# End Source File
# Begin Source File

SOURCE=.\DriveInfo.h
# End Source File
# Begin Source File

SOURCE=.\Encoder.h
# End Source File
# Begin Source File

SOURCE=.\EncoderDlg.h
# End Source File
# Begin Source File

SOURCE=.\FreeDBQuery.h
# End Source File
# Begin Source File

SOURCE=.\ID3Tag.h
# End Source File
# Begin Source File

SOURCE=.\InformationDlg.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Mp3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Mp3Encoder.h
# End Source File
# Begin Source File

SOURCE=.\OggDlg.h
# End Source File
# Begin Source File

SOURCE=.\OggEncoder.h
# End Source File
# Begin Source File

SOURCE=.\OutputInfo.h
# End Source File
# Begin Source File

SOURCE=.\Playlist.h
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Ripper.h
# End Source File
# Begin Source File

SOURCE=.\SplashDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TR.H
# End Source File
# Begin Source File

SOURCE=.\Track.h
# End Source File
# Begin Source File

SOURCE=.\TrackDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrackInfo.h
# End Source File
# Begin Source File

SOURCE=.\WavDlg.h
# End Source File
# Begin Source File

SOURCE=.\Wrip.h
# End Source File
# Begin Source File

SOURCE=.\WripDlg.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_arr.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_eje.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_nex.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_pla.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_pre.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_sto.ico
# End Source File
# Begin Source File

SOURCE=.\res\MISC01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\TRFFC09.ICO
# End Source File
# Begin Source File

SOURCE=.\res\wrip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wrip.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wrip.rc2
# End Source File
# Begin Source File

SOURCE=.\Wrip.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Wrip : {000001CF-01CF-0000-CF01-0000A91F0000}
# 	1:8:IDR_WRIP:108
# End Section
# Section Wrip : {72ADFD7E-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDS_DISK_SPACE:106
# 	1:19:CG_IDS_PHYSICAL_MEM:105
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:107
# 	2:14:PhysicalMemory:CG_IDS_PHYSICAL_MEM
# 	2:9:DiskSpace:CG_IDS_DISK_SPACE
# 	2:16:SpaceUnavailable:CG_IDS_DISK_SPACE_UNAVAIL
# 	2:7:NewFunc:1
# 	2:10:SysInfoKey:1234
# End Section
