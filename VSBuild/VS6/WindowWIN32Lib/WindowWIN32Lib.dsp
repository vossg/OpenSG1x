# Microsoft Developer Studio Project File - Name="WindowWIN32Lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WindowWIN32Lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WindowWIN32Lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WindowWIN32Lib.mak" CFG="WindowWIN32Lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WindowWIN32Lib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WindowWIN32Lib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /MD /W3 /GR /GX /O2 /I ".." /I "..\..\..\Base" /I "..\..\..\Log" /I "..\..\..\Field" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x0400 /D WIN32_WINDOWS=0x0410 /D "OSG_BUILD_DLL" /D "_OSG_HAVE_CONFIGURED_H_" /FD /c
# SUBTRACT CPP /nologo /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /dll /machine:I386
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\dbg"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP 
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWWIN32LIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Action/DrawAction  -I../../../Action/IntersectAction  -I../../../Action/RenderAction  -I../../../Action  -I../../../Base  -I../../../BaseLib  -I../../../SystemLib  -I../../../Cluster/MultiDisplay  -I../../../Cluster/SortFirst  -I../../../Cluster  -I../../../Experimental/BINWriter  -I../../../Experimental/BINWriter  -I../../../Experimental/OSGLoader  -I../../../Experimental/OSGWriter  -I../../../Experimental/StringConversionState  -I../../../Experimental/Text  -I../../../Experimental/VRMLLoader  -I../../../Experimental/VRMLWriter  -I../../../Field  -I../../../FieldContainer/Impl  -I../../../FieldContainer  -I../../../Functors  -I../../../Image  -I../../../Loader/Fhs  -I../../../Loader/OBJ  -I../../../Loader/OFF  -I../../../Loader/OSG  -I../../../Loader/RAW  -I../../../Loader/ScanParseSkel  -I../../../Loader/WRL  -I../../../Loader  -I../../../Log  -I../../../Material  -I../../../MultiThreading  -I../../../Network/Socket  -I../../../Network  -I../../../Nodes/Geometry  -I../../../Nodes/Light  -I../../../Nodes/Misc  -I../../../Nodes/Particles  -I../../../RenderingBackend  -I../../../State  -I../../../Statistics  -I../../../Window/WIN32  -I../../../Window  /FD /c
# SUBTRACT CPP 
# ADD BASE MTL /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32           
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib glut32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowWIN32D.dll
      

!ENDIF 

# Begin Target

# Name "WindowWIN32Lib - Win32 Release"
# Name "WindowWIN32Lib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "WindowWIN32 h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32Window.h
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowDataFields.h
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWindowWIN32Def.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "WindowWIN32 inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32Window.inl
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "WindowWIN32 cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32Window.cpp
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Window/WIN32/OSGWIN32WindowDataFields.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "WindowWIN32 ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group

# End Target
# End Project
