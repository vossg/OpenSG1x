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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/WindowWIN32Lib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  -I../../../Source/WindowSystem/QT  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt301.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGWindowQT.dll

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEWINDOWQTLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/SystemLib  -I../../../Source/WindowWIN32Lib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  -I../../../Source/WindowSystem/QT  -I../../../Source/WindowSystem/WIN32  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib qt-mt301.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGWindowQTD.dll
      

!ENDIF 

# Begin Target

# Name "WindowQTLib - Win32 Release"
# Name "WindowQTLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

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

# Begin Group "SourceWindowSystemQT ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group


# Begin Group "Header Install"
# PROP Default_Filter "h;hpp;hxx;hm"

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
