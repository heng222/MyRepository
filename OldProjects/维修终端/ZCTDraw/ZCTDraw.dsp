# Microsoft Developer Studio Project File - Name="ZCTDraw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ZCTDraw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZCTDraw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZCTDraw.mak" CFG="ZCTDraw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZCTDraw - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZCTDraw - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZCTDraw - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\ExeFiles\Release\ZCTDraw.dll"

!ELSEIF  "$(CFG)" == "ZCTDraw - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\ExeFiles\ZCTDraw.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ZCTDraw - Win32 Release"
# Name "ZCTDraw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnN.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseElement.cpp
# End Source File
# Begin Source File

SOURCE=.\BSD.cpp
# End Source File
# Begin Source File

SOURCE=.\CommFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoC.cpp
# End Source File
# Begin Source File

SOURCE=.\DCAN.cpp
# End Source File
# Begin Source File

SOURCE=.\EntRailway.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameTrainNo.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameTrainNoList.cpp
# End Source File
# Begin Source File

SOURCE=.\FuncBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\GdStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\HanZ.cpp
# End Source File
# Begin Source File

SOURCE=.\JT.cpp
# End Source File
# Begin Source File

SOURCE=.\JYJ.cpp
# End Source File
# Begin Source File

SOURCE=.\NQD.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseStationInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PasRailway.cpp
# End Source File
# Begin Source File

SOURCE=.\PassWordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QjStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadStationInf.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WcQD.cpp
# End Source File
# Begin Source File

SOURCE=.\XinHJ.cpp
# End Source File
# Begin Source File

SOURCE=.\ZCTDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\ZCTDraw.def
# End Source File
# Begin Source File

SOURCE=.\ZCTDraw.rc
# End Source File
# Begin Source File

SOURCE=.\ZCTInterlockJuge.cpp
# End Source File
# Begin Source File

SOURCE=.\zctmag.cpp
# End Source File
# Begin Source File

SOURCE=.\ZCTMultiWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ZCTWnd.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnN.h
# End Source File
# Begin Source File

SOURCE=.\BaseElement.h
# End Source File
# Begin Source File

SOURCE=.\BSD.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\CommFunction.h
# End Source File
# Begin Source File

SOURCE=.\DaoC.h
# End Source File
# Begin Source File

SOURCE=.\DCAN.h
# End Source File
# Begin Source File

SOURCE=.\EntRailway.h
# End Source File
# Begin Source File

SOURCE=.\FrameTrainNo.h
# End Source File
# Begin Source File

SOURCE=.\FrameTrainNoList.h
# End Source File
# Begin Source File

SOURCE=.\FuncBtn.h
# End Source File
# Begin Source File

SOURCE=.\GdStatus.h
# End Source File
# Begin Source File

SOURCE=.\HanZ.h
# End Source File
# Begin Source File

SOURCE=.\JT.h
# End Source File
# Begin Source File

SOURCE=.\JYJ.h
# End Source File
# Begin Source File

SOURCE=.\NQD.h
# End Source File
# Begin Source File

SOURCE=.\ParseStationInfo.h
# End Source File
# Begin Source File

SOURCE=.\PasRailway.h
# End Source File
# Begin Source File

SOURCE=.\PassWordDlg.h
# End Source File
# Begin Source File

SOURCE=.\QjStatus.h
# End Source File
# Begin Source File

SOURCE=.\ReadStationInf.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WcQD.h
# End Source File
# Begin Source File

SOURCE=.\XinHJ.h
# End Source File
# Begin Source File

SOURCE=.\ZCTInterlockJuge.h
# End Source File
# Begin Source File

SOURCE=.\ZCTMag.h
# End Source File
# Begin Source File

SOURCE=.\ZCTMultiWnd.h
# End Source File
# Begin Source File

SOURCE=.\ZCTWnd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\InCompent.CUR
# End Source File
# Begin Source File

SOURCE=.\res\LeftBtnDown.cur
# End Source File
# Begin Source File

SOURCE=.\res\ZCTDraw.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
