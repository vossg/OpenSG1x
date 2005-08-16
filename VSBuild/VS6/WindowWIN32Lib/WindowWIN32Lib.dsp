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
# PROP Output_Dir "..\lib\opt"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP 
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEWINDOWWIN32LIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/Manipulators  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/BalancedMultiWindow  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Text  -I../../../Source/System/Window  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib glut32.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGWindowWIN32.dll

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWWIN32LIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/Manipulators  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/BalancedMultiWindow  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Text  -I../../../Source/System/Window  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib glut32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowWIN32.dll
      

!ENDIF 

# Begin Target

# Name "WindowWIN32Lib - Win32 Release"
# Name "WindowWIN32Lib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceWindowSystemWIN32 h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32Window.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowDataFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWindowWIN32Def.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceWindowSystemWIN32 inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32Window.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "SourceWindowSystemWIN32 cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32Window.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowDataFields.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "SourceWindowSystemWIN32 ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group


# Begin Group "Header Install"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceWindowSystemWIN32 Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32Window.h

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32Window.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32Window.h > ../include/OpenSG/OSGWIN32Window.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.h

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32WindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.h > ../include/OpenSG/OSGWIN32WindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowDataFields.h

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32WindowDataFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32WindowDataFields.h > ../include/OpenSG/OSGWIN32WindowDataFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowFields.h

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32WindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32WindowFields.h > ../include/OpenSG/OSGWIN32WindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWindowWIN32Def.h

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowWIN32Def.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWindowWIN32Def.h > ../include/OpenSG/OSGWindowWIN32Def.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32Window.inl

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32Window.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32Window.inl > ../include/OpenSG/OSGWIN32Window.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.inl

!IF  "$(CFG)" == "WindowWIN32Lib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowWIN32Lib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWIN32WindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/WIN32/OSGWIN32WindowBase.inl > ../include/OpenSG/OSGWIN32WindowBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group

# End Group

# End Target
# End Project
