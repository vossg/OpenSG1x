# Microsoft Developer Studio Project File - Name="WindowGLUTLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WindowGLUTLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WindowGLUTLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WindowGLUTLib.mak" CFG="WindowGLUTLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WindowGLUTLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WindowGLUTLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WindowGLUTLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\opt"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP 
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEWINDOWGLUTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Experimental/Text  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  -I../../../Source/WindowSystem/GLUT  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib glut32.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGWindowGLUT.dll

!ELSEIF  "$(CFG)" == "WindowGLUTLib - Win32 Debug"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWGLUTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Experimental/Text  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  -I../../../Source/WindowSystem/GLUT  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib glut32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowGLUT.dll
      

!ENDIF 

# Begin Target

# Name "WindowGLUTLib - Win32 Release"
# Name "WindowGLUTLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceWindowSystemGLUT h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGWindowGLUTDef.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceWindowSystemGLUT inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "SourceWindowSystemGLUT cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/GLUT/OSGGLUTWindowBase.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "SourceWindowSystemGLUT ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group

# End Target
# End Project
