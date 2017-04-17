# Microsoft Developer Studio Project File - Name="PWEffect" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PWEffect - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PWEffect.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PWEffect.mak" CFG="PWEffect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PWEffect - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PWEffect - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PWEffect - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWEffect_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./Utilities" /I "./GDIPlus/Includes" /I "D:\DirectX\DMSDK6\Include" /I "./" /I "./Base" /I "./Effects" /I "./Transitions" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWEffect_EXPORTS" /D "UNICODE" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 Winmm.lib ddraw.lib dxguid.lib d3dx.lib uuid.lib Msimg32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
TargetPath=.\Release\PWEffect.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=@echo Registering DLL...	REM regsvr32 /s $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PWEffect - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWEffect_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./Utilities" /I "./GDIPlus/Includes" /I "./" /I "D:\DirectX\DMSDK6\Include" /I "./Base" /I "./Effects" /I "./Transitions" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PWEffect_EXPORTS" /D "UNICODE" /FR /YX /FD /GZ /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib ddraw.lib dxguid.lib d3dx.lib DXTrans.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Msimg32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
TargetPath=.\Debug\PWEffect.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=@echo Registering DLL...	regsvr32 /s $(TargetPath)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PWEffect - Win32 Release"
# Name "PWEffect - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PWEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\PWEffect.def
# End Source File
# Begin Source File

SOURCE=.\PWEffect.idl
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\PWEffect.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Utilities\DebugMacros.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\frametimer.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\frametimer.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\RandMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\RandMgr.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\SmartPtr.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\TMPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\TMPoint.h
# End Source File
# Begin Source File

SOURCE=.\Utilities\TravelRect.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\TravelRect.h
# End Source File
# End Group
# Begin Group "SWAP_TEMP"

# PROP Default_Filter ""
# End Group
# Begin Group "SpecialEffect"

# PROP Default_Filter ""
# Begin Group "BASE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Base\DTOBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Base\DTOBase.h
# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Group "_EffectBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\DTOEffectBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\DTOEffectBase.h
# End Source File
# End Group
# Begin Group "Bijou Effect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\Bijou.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\Bijou.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Bijou.rgs
# End Source File
# End Group
# Begin Group "Text Effect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\DTOText.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\DTOText.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\DTOText.rgs
# End Source File
# End Group
# Begin Group "ColorAdjust Effect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\rgsfiles\ColorAdjust.rgs
# End Source File
# Begin Source File

SOURCE=.\Effects\DTOClrAdjust.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\DTOClrAdjust.h
# End Source File
# End Group
# Begin Group "PixelPlay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\PixelPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\PixelPlay.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\PixelPlay.rgs
# End Source File
# End Group
# Begin Group "Snow"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\Snow.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\Snow.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Snow.rgs
# End Source File
# End Group
# Begin Group "Sparkle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\Sparkle.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\Sparkle.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Sparkle.rgs
# End Source File
# End Group
# Begin Group "Flash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\Flash.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\Flash.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Flash.rgs
# End Source File
# End Group
# Begin Group "Travel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\Travel.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\Travel.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Travel.rgs
# End Source File
# End Group
# Begin Group "WrapAround"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Effects\WrapAround.cpp
# End Source File
# Begin Source File

SOURCE=.\Effects\WrapAround.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\WrapAround.rgs
# End Source File
# End Group
# End Group
# Begin Group "Transitions"

# PROP Default_Filter ""
# Begin Group "_TransBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\DTOTransBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\DTOTransBase.h
# End Source File
# End Group
# Begin Group "Bounce"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Bounce.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Bounce.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Bounce.rgs
# End Source File
# End Group
# Begin Group "BlackHole"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\BlackHole.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\BlackHole.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\BlackHole.rgs
# End Source File
# End Group
# Begin Group "Slot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Slot.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Slot.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Slot.rgs
# End Source File
# End Group
# Begin Group "Filter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Filter.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Filter.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Filter.rgs
# End Source File
# End Group
# Begin Group "Interleave"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Interleave.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Interleave.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Interleave.rgs
# End Source File
# End Group
# Begin Group "LineOn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\LineOn.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\LineOn.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\LineOn.rgs
# End Source File
# End Group
# Begin Group "Rain"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Rain.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Rain.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Rain.rgs
# End Source File
# End Group
# Begin Group "Slide"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Slide.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Slide.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Slide.rgs
# End Source File
# End Group
# Begin Group "Wipe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Wipe.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Wipe.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Wipe.rgs
# End Source File
# End Group
# Begin Group "MultiWipe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\MultiWipe.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\MultiWipe.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\MultiWipe.rgs
# End Source File
# End Group
# Begin Group "PushOn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\PushOn.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\PushOn.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\PushOn.rgs
# End Source File
# End Group
# Begin Group "Radar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Radar.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Radar.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Radar.rgs
# End Source File
# End Group
# Begin Group "Venetian"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\TVenetianCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\TVenetianCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Transitions\Venetian.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Venetian.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Venetian.rgs
# End Source File
# End Group
# Begin Group "Fade"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Fade.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Fade.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Fade.rgs
# End Source File
# End Group
# Begin Group "Coalesce"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Transitions\Coalesce.cpp
# End Source File
# Begin Source File

SOURCE=.\Transitions\Coalesce.h
# End Source File
# Begin Source File

SOURCE=.\rgsfiles\Coalesce.rgs
# End Source File
# End Group
# End Group
# End Group
# End Target
# End Project
