# Microsoft Developer Studio Project File - Name="WindowQTLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WindowQTLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WindowQTLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WindowQTLib.mak" CFG="WindowQTLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WindowQTLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WindowQTLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\lib\opt"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP 
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -GR -O2 -Ob1 -MD -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Action/DrawAction  -I../../../Action/IntersectAction  -I../../../Action/RenderAction  -I../../../Action  -I../../../Base  -I../../../BaseLib  -I../../../SystemLib  -I../../../WindowWIN32Lib  -I../../../Cluster/MultiDisplay  -I../../../Cluster/SortFirst  -I../../../Cluster  -I../../../Experimental/BINWriter  -I../../../Experimental/BINWriter  -I../../../Experimental/OSGLoader  -I../../../Experimental/OSGWriter  -I../../../Experimental/StringConversionState  -I../../../Experimental/Text  -I../../../Experimental/VRMLLoader  -I../../../Experimental/VRMLWriter  -I../../../Field  -I../../../FieldContainer/Impl  -I../../../FieldContainer  -I../../../Functors  -I../../../Image  -I../../../Loader/OBJ  -I../../../Loader/OFF  -I../../../Loader/OSG  -I../../../Loader/RAW  -I../../../Loader/ScanParseSkel  -I../../../Loader/WRL  -I../../../Loader  -I../../../Log  -I../../../Material  -I../../../MultiThreading  -I../../../Network/Socket  -I../../../Network  -I../../../Nodes/Geometry  -I../../../Nodes/Light  -I../../../Nodes/Misc  -I../../../Nodes/Particles  -I../../../RenderingBackend  -I../../../State  -I../../../Statistics  -I../../../Window/QT  -I../../../Window/WIN32  -I../../../Window  /FD /c
# SUBTRACT CPP 
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt301.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGWindowQT.dll

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Action/DrawAction  -I../../../Action/IntersectAction  -I../../../Action/RenderAction  -I../../../Action  -I../../../Base  -I../../../BaseLib  -I../../../SystemLib  -I../../../WindowWIN32Lib  -I../../../Cluster/MultiDisplay  -I../../../Cluster/SortFirst  -I../../../Cluster  -I../../../Experimental/BINWriter  -I../../../Experimental/BINWriter  -I../../../Experimental/OSGLoader  -I../../../Experimental/OSGWriter  -I../../../Experimental/StringConversionState  -I../../../Experimental/Text  -I../../../Experimental/VRMLLoader  -I../../../Experimental/VRMLWriter  -I../../../Field  -I../../../FieldContainer/Impl  -I../../../FieldContainer  -I../../../Functors  -I../../../Image  -I../../../Loader/OBJ  -I../../../Loader/OFF  -I../../../Loader/OSG  -I../../../Loader/RAW  -I../../../Loader/ScanParseSkel  -I../../../Loader/WRL  -I../../../Loader  -I../../../Log  -I../../../Material  -I../../../MultiThreading  -I../../../Network/Socket  -I../../../Network  -I../../../Nodes/Geometry  -I../../../Nodes/Light  -I../../../Nodes/Misc  -I../../../Nodes/Particles  -I../../../RenderingBackend  -I../../../State  -I../../../Statistics  -I../../../Window/QT  -I../../../Window/WIN32  -I../../../Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt301.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowQT.dll
      

!ENDIF 

# Begin Target

# Name "WindowQTLib - Win32 Release"
# Name "WindowQTLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "WindowQT h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/QT/OSGQGLManagedWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Window/QT/OSGQGLManagedWidget_qt.h

BuildCmds= \
moc.exe ../../../Window/QT/OSGQGLManagedWidget_qt.h -i -o OSGQGLManagedWidget_qt_moc.cpp

"OSGQGLManagedWidget_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQGLWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Window/QT/OSGQGLWidget_qt.h

BuildCmds= \
moc.exe ../../../Window/QT/OSGQGLWidget_qt.h -i -o OSGQGLWidget_qt_moc.cpp

"OSGQGLWidget_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindowDataFields.h
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGWindowQTDef.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "WindowQT inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/QT/OSGQGLWidget_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "WindowQT cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Window/QT/OSGQGLManagedWidget_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQGLWidget_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Window/QT/OSGQTWindowBase.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "WindowQT ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group

# End Target
# End Project
