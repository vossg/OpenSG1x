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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/WindowWIN32Lib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/Manipulators  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/QTWidgets  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/BalancedMultiWindow  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Text  -I../../../Source/System/Window  -I../../../Source/WindowSystem/QT  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt312.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGWindowQT.dll

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=600  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/WindowWIN32Lib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/Manipulators  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/QTWidgets  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/BalancedMultiWindow  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Text  -I../../../Source/System/Window  -I../../../Source/WindowSystem/QT  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt312.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowQT.dll
      

!ENDIF 

# Begin Target

# Name "WindowQTLib - Win32 Release"
# Name "WindowQTLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceExperimentalQTWidgets h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.h -i -o OSGQAbstractFieldEditor_qt_moc.cpp

"OSGQAbstractFieldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.h -i -o OSGQAbstractValueEditor_qt_moc.cpp

"OSGQAbstractValueEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.h -i -o OSGQAttachmentMapEditor_qt_moc.cpp

"OSGQAttachmentMapEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.h -i -o OSGQColor3fEditor_qt_moc.cpp

"OSGQColor3fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.h -i -o OSGQColor3ubEditor_qt_moc.cpp

"OSGQColor3ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.h -i -o OSGQColor4fEditor_qt_moc.cpp

"OSGQColor4fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.h -i -o OSGQColor4ubEditor_qt_moc.cpp

"OSGQColor4ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.h -i -o OSGQColorButton_qt_moc.cpp

"OSGQColorButton_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.h -i -o OSGQFieldContainerEditor_qt_moc.cpp

"OSGQFieldContainerEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.h -i -o OSGQFieldContainerPtrEditor_qt_moc.cpp

"OSGQFieldContainerPtrEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.h -i -o OSGQGenericValueEditor_qt_moc.cpp

"OSGQGenericValueEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.h -i -o OSGQInt16Editor_qt_moc.cpp

"OSGQInt16Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.h -i -o OSGQInt32Editor_qt_moc.cpp

"OSGQInt32Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.h -i -o OSGQInt8Editor_qt_moc.cpp

"OSGQInt8Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.h -i -o OSGQMFieldEditor_qt_moc.cpp

"OSGQMFieldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.h -i -o OSGQMatrixEditor_qt_moc.cpp

"OSGQMatrixEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactoryHelper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.h -i -o OSGQPnt2bEditor_qt_moc.cpp

"OSGQPnt2bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.h -i -o OSGQPnt2dEditor_qt_moc.cpp

"OSGQPnt2dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.h -i -o OSGQPnt2fEditor_qt_moc.cpp

"OSGQPnt2fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.h -i -o OSGQPnt2ldEditor_qt_moc.cpp

"OSGQPnt2ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.h -i -o OSGQPnt2sEditor_qt_moc.cpp

"OSGQPnt2sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.h -i -o OSGQPnt2ubEditor_qt_moc.cpp

"OSGQPnt2ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.h -i -o OSGQPnt2usEditor_qt_moc.cpp

"OSGQPnt2usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.h -i -o OSGQPnt3bEditor_qt_moc.cpp

"OSGQPnt3bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.h -i -o OSGQPnt3dEditor_qt_moc.cpp

"OSGQPnt3dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.h -i -o OSGQPnt3fEditor_qt_moc.cpp

"OSGQPnt3fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.h -i -o OSGQPnt3ldEditor_qt_moc.cpp

"OSGQPnt3ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.h -i -o OSGQPnt3sEditor_qt_moc.cpp

"OSGQPnt3sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.h -i -o OSGQPnt3ubEditor_qt_moc.cpp

"OSGQPnt3ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.h -i -o OSGQPnt3usEditor_qt_moc.cpp

"OSGQPnt3usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.h -i -o OSGQPnt4bEditor_qt_moc.cpp

"OSGQPnt4bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.h -i -o OSGQPnt4dEditor_qt_moc.cpp

"OSGQPnt4dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.h -i -o OSGQPnt4fEditor_qt_moc.cpp

"OSGQPnt4fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.h -i -o OSGQPnt4ldEditor_qt_moc.cpp

"OSGQPnt4ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.h -i -o OSGQPnt4sEditor_qt_moc.cpp

"OSGQPnt4sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.h -i -o OSGQPnt4ubEditor_qt_moc.cpp

"OSGQPnt4ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.h -i -o OSGQPnt4usEditor_qt_moc.cpp

"OSGQPnt4usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.h -i -o OSGQReal32Editor_qt_moc.cpp

"OSGQReal32Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.h -i -o OSGQReal64Editor_qt_moc.cpp

"OSGQReal64Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.h -i -o OSGQSFieldEditor_qt_moc.cpp

"OSGQSFieldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.h -i -o OSGQSpinBoxBase_qt_moc.cpp

"OSGQSpinBoxBase_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.h -i -o OSGQSpinBoxInt16_qt_moc.cpp

"OSGQSpinBoxInt16_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.h -i -o OSGQSpinBoxInt32_qt_moc.cpp

"OSGQSpinBoxInt32_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.h -i -o OSGQSpinBoxInt8_qt_moc.cpp

"OSGQSpinBoxInt8_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.h -i -o OSGQSpinBoxReal128_qt_moc.cpp

"OSGQSpinBoxReal128_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.h -i -o OSGQSpinBoxReal32_qt_moc.cpp

"OSGQSpinBoxReal32_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.h -i -o OSGQSpinBoxReal64_qt_moc.cpp

"OSGQSpinBoxReal64_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.h -i -o OSGQSpinBoxUInt16_qt_moc.cpp

"OSGQSpinBoxUInt16_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.h -i -o OSGQSpinBoxUInt32_qt_moc.cpp

"OSGQSpinBoxUInt32_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.h -i -o OSGQSpinBoxUInt8_qt_moc.cpp

"OSGQSpinBoxUInt8_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxes_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQSpinBoxes_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQSpinBoxes_qt.h -i -o OSGQSpinBoxes_qt_moc.cpp

"OSGQSpinBoxes_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.h -i -o OSGQUInt16Editor_qt_moc.cpp

"OSGQUInt16Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.h -i -o OSGQUInt32Editor_qt_moc.cpp

"OSGQUInt32Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.h -i -o OSGQUInt8Editor_qt_moc.cpp

"OSGQUInt8Editor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.h -i -o OSGQVec2bEditor_qt_moc.cpp

"OSGQVec2bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.h -i -o OSGQVec2dEditor_qt_moc.cpp

"OSGQVec2dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.h -i -o OSGQVec2fEditor_qt_moc.cpp

"OSGQVec2fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.h -i -o OSGQVec2ldEditor_qt_moc.cpp

"OSGQVec2ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.h -i -o OSGQVec2sEditor_qt_moc.cpp

"OSGQVec2sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.h -i -o OSGQVec2ubEditor_qt_moc.cpp

"OSGQVec2ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.h -i -o OSGQVec2usEditor_qt_moc.cpp

"OSGQVec2usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.h -i -o OSGQVec3bEditor_qt_moc.cpp

"OSGQVec3bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.h -i -o OSGQVec3dEditor_qt_moc.cpp

"OSGQVec3dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.h -i -o OSGQVec3fEditor_qt_moc.cpp

"OSGQVec3fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.h -i -o OSGQVec3ldEditor_qt_moc.cpp

"OSGQVec3ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.h -i -o OSGQVec3sEditor_qt_moc.cpp

"OSGQVec3sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.h -i -o OSGQVec3ubEditor_qt_moc.cpp

"OSGQVec3ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.h -i -o OSGQVec3usEditor_qt_moc.cpp

"OSGQVec3usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.h -i -o OSGQVec4bEditor_qt_moc.cpp

"OSGQVec4bEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.h -i -o OSGQVec4dEditor_qt_moc.cpp

"OSGQVec4dEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.h -i -o OSGQVec4fEditor_qt_moc.cpp

"OSGQVec4fEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.h -i -o OSGQVec4ldEditor_qt_moc.cpp

"OSGQVec4ldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.h -i -o OSGQVec4sEditor_qt_moc.cpp

"OSGQVec4sEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.h -i -o OSGQVec4ubEditor_qt_moc.cpp

"OSGQVec4ubEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.h -i -o OSGQVec4usEditor_qt_moc.cpp

"OSGQVec4usEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelperTraits.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxMapper.h
# End Source File

# End Group
# Begin Group "SourceWindowSystemQT h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.h -i -o OSGQFieldContainerView_qt_moc.cpp

"OSGQFieldContainerView_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditorFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.h -i -o OSGQFieldEditor_qt_moc.cpp

"OSGQFieldEditor_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldValueLabel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQFieldView_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQFieldView_qt.h -i -o OSGQFieldView_qt_moc.cpp

"OSGQFieldView_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.h -i -o OSGQGLManagedDesignerWidget_qt_moc.cpp

"OSGQGLManagedDesignerWidget_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.h -i -o OSGQGLManagedWidget_qt_moc.cpp

"OSGQGLManagedWidget_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQGLWidget_qt.h -i -o OSGQGLWidget_qt_moc.cpp

"OSGQGLWidget_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.h -i -o OSGQNodeTreeView_qt_moc.cpp

"OSGQNodeTreeView_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphViewFunctions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.h

BuildCmds= \
moc.exe ../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.h -i -o OSGQSceneGraphView_qt_moc.cpp

"OSGQSceneGraphView_qt_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowDataFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTypedFieldValueLabel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQWidgetFunctions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGWindowQTDef.h
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGWindowQTPlugin.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceExperimentalQTWidgets inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.inl
# End Source File

# End Group
# Begin Group "SourceWindowSystemQT inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldValueLabel.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldView_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQWidgetFunctions.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "SourceExperimentalQTWidgets cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactoryHelper.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelperTraits.cpp
# End Source File

# End Group
# Begin Group "SourceWindowSystemQT cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditorFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldValueLabel.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldView_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphViewFunctions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTypedFieldValueLabel.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQWidgetFunctions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGWindowQTPlugin.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "SourceExperimentalQTWidgets ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceWindowSystemQT ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group


# Begin Group "Header Install"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceExperimentalQTWidgets Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAbstractFieldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.h > ../include/OpenSG/OSGQAbstractFieldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAbstractValueEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.h > ../include/OpenSG/OSGQAbstractValueEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAttachmentMapEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.h > ../include/OpenSG/OSGQAttachmentMapEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor3fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.h > ../include/OpenSG/OSGQColor3fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor3ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.h > ../include/OpenSG/OSGQColor3ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor4fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.h > ../include/OpenSG/OSGQColor4fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor4ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.h > ../include/OpenSG/OSGQColor4ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColorButton_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.h > ../include/OpenSG/OSGQColorButton_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.h > ../include/OpenSG/OSGQFieldContainerEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerPtrEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.h > ../include/OpenSG/OSGQFieldContainerPtrEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGenericValueEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.h > ../include/OpenSG/OSGQGenericValueEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQInt16Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQInt16Editor_qt.h > ../include/OpenSG/OSGQInt16Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQInt32Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQInt32Editor_qt.h > ../include/OpenSG/OSGQInt32Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQInt8Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQInt8Editor_qt.h > ../include/OpenSG/OSGQInt8Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQMFieldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.h > ../include/OpenSG/OSGQMFieldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQMatrixEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQMatrixEditor_qt.h > ../include/OpenSG/OSGQMatrixEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQOSGWidgetFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.h > ../include/OpenSG/OSGQOSGWidgetFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactoryHelper.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQOSGWidgetFactoryHelper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactoryHelper.h > ../include/OpenSG/OSGQOSGWidgetFactoryHelper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2bEditor_qt.h > ../include/OpenSG/OSGQPnt2bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2dEditor_qt.h > ../include/OpenSG/OSGQPnt2dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2fEditor_qt.h > ../include/OpenSG/OSGQPnt2fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2ldEditor_qt.h > ../include/OpenSG/OSGQPnt2ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2sEditor_qt.h > ../include/OpenSG/OSGQPnt2sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2ubEditor_qt.h > ../include/OpenSG/OSGQPnt2ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt2usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt2usEditor_qt.h > ../include/OpenSG/OSGQPnt2usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3bEditor_qt.h > ../include/OpenSG/OSGQPnt3bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3dEditor_qt.h > ../include/OpenSG/OSGQPnt3dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3fEditor_qt.h > ../include/OpenSG/OSGQPnt3fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3ldEditor_qt.h > ../include/OpenSG/OSGQPnt3ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3sEditor_qt.h > ../include/OpenSG/OSGQPnt3sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3ubEditor_qt.h > ../include/OpenSG/OSGQPnt3ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt3usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt3usEditor_qt.h > ../include/OpenSG/OSGQPnt3usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4bEditor_qt.h > ../include/OpenSG/OSGQPnt4bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4dEditor_qt.h > ../include/OpenSG/OSGQPnt4dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4fEditor_qt.h > ../include/OpenSG/OSGQPnt4fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4ldEditor_qt.h > ../include/OpenSG/OSGQPnt4ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4sEditor_qt.h > ../include/OpenSG/OSGQPnt4sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4ubEditor_qt.h > ../include/OpenSG/OSGQPnt4ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPnt4usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQPnt4usEditor_qt.h > ../include/OpenSG/OSGQPnt4usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQReal32Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQReal32Editor_qt.h > ../include/OpenSG/OSGQReal32Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQReal64Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQReal64Editor_qt.h > ../include/OpenSG/OSGQReal64Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSFieldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSFieldEditor_qt.h > ../include/OpenSG/OSGQSFieldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQScalarEditorHelper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.h > ../include/OpenSG/OSGQScalarEditorHelper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxBase_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.h > ../include/OpenSG/OSGQSpinBoxBase_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt16_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.h > ../include/OpenSG/OSGQSpinBoxInt16_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt32_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.h > ../include/OpenSG/OSGQSpinBoxInt32_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt8_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.h > ../include/OpenSG/OSGQSpinBoxInt8_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal128_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.h > ../include/OpenSG/OSGQSpinBoxReal128_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal32_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.h > ../include/OpenSG/OSGQSpinBoxReal32_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal64_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.h > ../include/OpenSG/OSGQSpinBoxReal64_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt16_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.h > ../include/OpenSG/OSGQSpinBoxUInt16_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt32_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.h > ../include/OpenSG/OSGQSpinBoxUInt32_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt8_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.h > ../include/OpenSG/OSGQSpinBoxUInt8_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxes_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxes_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxes_qt.h > ../include/OpenSG/OSGQSpinBoxes_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQUInt16Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQUInt16Editor_qt.h > ../include/OpenSG/OSGQUInt16Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQUInt32Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQUInt32Editor_qt.h > ../include/OpenSG/OSGQUInt32Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQUInt8Editor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQUInt8Editor_qt.h > ../include/OpenSG/OSGQUInt8Editor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2bEditor_qt.h > ../include/OpenSG/OSGQVec2bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2dEditor_qt.h > ../include/OpenSG/OSGQVec2dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2fEditor_qt.h > ../include/OpenSG/OSGQVec2fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2ldEditor_qt.h > ../include/OpenSG/OSGQVec2ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2sEditor_qt.h > ../include/OpenSG/OSGQVec2sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2ubEditor_qt.h > ../include/OpenSG/OSGQVec2ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec2usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec2usEditor_qt.h > ../include/OpenSG/OSGQVec2usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3bEditor_qt.h > ../include/OpenSG/OSGQVec3bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3dEditor_qt.h > ../include/OpenSG/OSGQVec3dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3fEditor_qt.h > ../include/OpenSG/OSGQVec3fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3ldEditor_qt.h > ../include/OpenSG/OSGQVec3ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3sEditor_qt.h > ../include/OpenSG/OSGQVec3sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3ubEditor_qt.h > ../include/OpenSG/OSGQVec3ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec3usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec3usEditor_qt.h > ../include/OpenSG/OSGQVec3usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4bEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4bEditor_qt.h > ../include/OpenSG/OSGQVec4bEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4dEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4dEditor_qt.h > ../include/OpenSG/OSGQVec4dEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4fEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4fEditor_qt.h > ../include/OpenSG/OSGQVec4fEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4ldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4ldEditor_qt.h > ../include/OpenSG/OSGQVec4ldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4sEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4sEditor_qt.h > ../include/OpenSG/OSGQVec4sEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4ubEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4ubEditor_qt.h > ../include/OpenSG/OSGQVec4ubEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVec4usEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVec4usEditor_qt.h > ../include/OpenSG/OSGQVec4usEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVectorPointEditorHelper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.h > ../include/OpenSG/OSGQVectorPointEditorHelper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpinBoxHelper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.h > ../include/OpenSG/OSGSpinBoxHelper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelperTraits.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpinBoxHelperTraits.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGSpinBoxHelperTraits.h > ../include/OpenSG/OSGSpinBoxHelperTraits.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxMapper.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpinBoxMapper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGSpinBoxMapper.h > ../include/OpenSG/OSGSpinBoxMapper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAbstractFieldEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAbstractFieldEditor_qt.inl > ../include/OpenSG/OSGQAbstractFieldEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAbstractValueEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAbstractValueEditor_qt.inl > ../include/OpenSG/OSGQAbstractValueEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQAttachmentMapEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQAttachmentMapEditor_qt.inl > ../include/OpenSG/OSGQAttachmentMapEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor3fEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor3fEditor_qt.inl > ../include/OpenSG/OSGQColor3fEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor3ubEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor3ubEditor_qt.inl > ../include/OpenSG/OSGQColor3ubEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor4fEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor4fEditor_qt.inl > ../include/OpenSG/OSGQColor4fEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColor4ubEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColor4ubEditor_qt.inl > ../include/OpenSG/OSGQColor4ubEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQColorButton_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQColorButton_qt.inl > ../include/OpenSG/OSGQColorButton_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQFieldContainerEditor_qt.inl > ../include/OpenSG/OSGQFieldContainerEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerPtrEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQFieldContainerPtrEditor_qt.inl > ../include/OpenSG/OSGQFieldContainerPtrEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGenericValueEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQGenericValueEditor_qt.inl > ../include/OpenSG/OSGQGenericValueEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQMFieldEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQMFieldEditor_qt.inl > ../include/OpenSG/OSGQMFieldEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQOSGWidgetFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQOSGWidgetFactory.inl > ../include/OpenSG/OSGQOSGWidgetFactory.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQScalarEditorHelper.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQScalarEditorHelper.inl > ../include/OpenSG/OSGQScalarEditorHelper.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxBase_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxBase_qt.inl > ../include/OpenSG/OSGQSpinBoxBase_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt16_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt16_qt.inl > ../include/OpenSG/OSGQSpinBoxInt16_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt32_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt32_qt.inl > ../include/OpenSG/OSGQSpinBoxInt32_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxInt8_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxInt8_qt.inl > ../include/OpenSG/OSGQSpinBoxInt8_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal128_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal128_qt.inl > ../include/OpenSG/OSGQSpinBoxReal128_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal32_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal32_qt.inl > ../include/OpenSG/OSGQSpinBoxReal32_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxReal64_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxReal64_qt.inl > ../include/OpenSG/OSGQSpinBoxReal64_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt16_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt16_qt.inl > ../include/OpenSG/OSGQSpinBoxUInt16_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt32_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt32_qt.inl > ../include/OpenSG/OSGQSpinBoxUInt32_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSpinBoxUInt8_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQSpinBoxUInt8_qt.inl > ../include/OpenSG/OSGQSpinBoxUInt8_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVectorPointEditorHelper.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGQVectorPointEditorHelper.inl > ../include/OpenSG/OSGQVectorPointEditorHelper.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpinBoxHelper.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/QTWidgets/OSGSpinBoxHelper.inl > ../include/OpenSG/OSGSpinBoxHelper.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceWindowSystemQT Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerView_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.h > ../include/OpenSG/OSGQFieldContainerView_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditorFactory.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldEditorFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldEditorFactory.h > ../include/OpenSG/OSGQFieldEditorFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldEditor_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.h > ../include/OpenSG/OSGQFieldEditor_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldLabelFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.h > ../include/OpenSG/OSGQFieldLabelFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldValueLabel.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldValueLabel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldValueLabel.h > ../include/OpenSG/OSGQFieldValueLabel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldView_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldView_qt.h > ../include/OpenSG/OSGQFieldView_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGLManagedDesignerWidget_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQGLManagedDesignerWidget_qt.h > ../include/OpenSG/OSGQGLManagedDesignerWidget_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGLManagedWidget_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQGLManagedWidget_qt.h > ../include/OpenSG/OSGQGLManagedWidget_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGLWidget_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQGLWidget_qt.h > ../include/OpenSG/OSGQGLWidget_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQMatrixFieldValueLabel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.h > ../include/OpenSG/OSGQMatrixFieldValueLabel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQNodeTreeView_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQNodeTreeView_qt.h > ../include/OpenSG/OSGQNodeTreeView_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPointFieldValueLabel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.h > ../include/OpenSG/OSGQPointFieldValueLabel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphViewFunctions.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSceneGraphViewFunctions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQSceneGraphViewFunctions.h > ../include/OpenSG/OSGQSceneGraphViewFunctions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQSceneGraphView_qt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQSceneGraphView_qt.h > ../include/OpenSG/OSGQSceneGraphView_qt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindow.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindow.h > ../include/OpenSG/OSGQTWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowBase.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindowBase.h > ../include/OpenSG/OSGQTWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowDataFields.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindowDataFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindowDataFields.h > ../include/OpenSG/OSGQTWindowDataFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowFields.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindowFields.h > ../include/OpenSG/OSGQTWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTypedFieldValueLabel.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTypedFieldValueLabel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTypedFieldValueLabel.h > ../include/OpenSG/OSGQTypedFieldValueLabel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVectorFieldValueLabel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.h > ../include/OpenSG/OSGQVectorFieldValueLabel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQWidgetFunctions.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQWidgetFunctions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQWidgetFunctions.h > ../include/OpenSG/OSGQWidgetFunctions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGWindowQTDef.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowQTDef.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGWindowQTDef.h > ../include/OpenSG/OSGWindowQTDef.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGWindowQTPlugin.h

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowQTPlugin.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGWindowQTPlugin.h > ../include/OpenSG/OSGWindowQTPlugin.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldContainerView_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldContainerView_qt.inl > ../include/OpenSG/OSGQFieldContainerView_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldEditor_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldEditor_qt.inl > ../include/OpenSG/OSGQFieldEditor_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldLabelFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldLabelFactory.inl > ../include/OpenSG/OSGQFieldLabelFactory.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldValueLabel.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldValueLabel.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldValueLabel.inl > ../include/OpenSG/OSGQFieldValueLabel.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQFieldView_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQFieldView_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQFieldView_qt.inl > ../include/OpenSG/OSGQFieldView_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQGLWidget_qt.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQGLWidget_qt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQGLWidget_qt.inl > ../include/OpenSG/OSGQGLWidget_qt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQMatrixFieldValueLabel.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQMatrixFieldValueLabel.inl > ../include/OpenSG/OSGQMatrixFieldValueLabel.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQPointFieldValueLabel.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQPointFieldValueLabel.inl > ../include/OpenSG/OSGQPointFieldValueLabel.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindow.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindow.inl > ../include/OpenSG/OSGQTWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQTWindowBase.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQTWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQTWindowBase.inl > ../include/OpenSG/OSGQTWindowBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQVectorFieldValueLabel.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQVectorFieldValueLabel.inl > ../include/OpenSG/OSGQVectorFieldValueLabel.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/WindowSystem/QT/OSGQWidgetFunctions.inl

!IF  "$(CFG)" == "WindowQTLib - Win32 Release"

!ELSEIF  "$(CFG)" == "WindowQTLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQWidgetFunctions.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/WindowSystem/QT/OSGQWidgetFunctions.inl > ../include/OpenSG/OSGQWidgetFunctions.inl

# End Custom Build

!ENDIF

# End Source File

# End Group

# End Group

# End Target
# End Project
