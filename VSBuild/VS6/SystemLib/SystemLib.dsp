# Microsoft Developer Studio Project File - Name="SystemLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SystemLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SystemLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SystemLib.mak" CFG="SystemLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SystemLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SystemLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SystemLib - Win32 Release"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILESYSTEMLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Experimental/Text  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  freetype.lib opengl32.lib glu32.lib gdi32.lib libjpeg.lib libpng.lib zlib.lib tif32.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGSystem.dll

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILESYSTEMLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Experimental/Text  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  freetype.lib opengl32.lib glu32.lib gdi32.lib libjpeg.lib libpng.lib zlib.lib tif32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGSystem.dll
      

!ENDIF 

# Begin Target

# Name "SystemLib - Win32 Release"
# Name "SystemLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceExperimentalText h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractText.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFont.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyphContour.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyleFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStylePFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedText.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFont.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyphContour.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTVectorFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFont.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFGlyphInfo.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTesselationHandler.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGText.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGVectorFontGlyph.h
# End Source File

# End Group
# Begin Group "SourceSystemAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/OSGAction.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGDrawActionBase.h
# End Source File

# End Group
# Begin Group "SourceSystemActionDrawAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/DrawAction/OSGDrawAction.h
# End Source File

# End Group
# Begin Group "SourceSystemActionIntersectAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/IntersectAction/OSGIntersectAction.h
# End Source File

# End Group
# Begin Group "SourceSystemActionRenderAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderAction.h
# End Source File

# End Group
# Begin Group "SourceSystemClusterBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterException.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterNetwork.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterViewBuffer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRemoteAspect.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRenderNode.h
# End Source File

# End Group
# Begin Group "SourceSystemClusterServer h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Server/OSGClusterServer.h
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowFields.h
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowMultiDisplay h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowFields.h
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowSortFirst h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.h
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainer h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachment.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentMapFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentMapFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGChangeList.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerProperties.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerPtrForward.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldDescription.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentMap.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFFieldContainerTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFNodeCorePtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNode.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCoreFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCoreFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGPrimary.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentMap.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFFieldContainerTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFNodeCorePtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSimpleAttachments.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSystemDef.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGThread.h
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainerImpl h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGMFNodePtrDepImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGMFNodePtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodeImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGSFNodePtrDepImpl.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGSFNodePtrImpl.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOBIN h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINLoader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINSceneFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINWriter.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileHandler.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOBJ h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OBJ/OSGOBJSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOFF h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OFF/OSGOFFSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOSG h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGLoader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGSceneFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGWriter.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIORAW h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/RAW/OSGRAWSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOScanParseSkel h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.h
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.tab.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLFile.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeDescs.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLSceneFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.h
# End Source File

# End Group
# Begin Group "SourceSystemImage h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGDATImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGGIFImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImage.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileHandler.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageGenericAtt.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGJPGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMFImageTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMNGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMTDImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNMImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGSGIImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTGAImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTIFImageFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemMaterial h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesGeometry h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGExtrusionGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoColorsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoIndicesFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoNormalsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPLengthsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPTypesFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPositionsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropIndices.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPLengths.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPtrs.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoProperty.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoTexCoordsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGNodeGraph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGSimpleGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGVolumeDraw.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesMisc h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroup.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsLight h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLight.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLight.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsMisc h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInline.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransform.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformFields.h
# End Source File

# End Group
# Begin Group "SourceSystemRenderingBackend h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNode.h
# End Source File

# End Group
# Begin Group "SourceSystemState h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGState.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTestCubeMaps.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkFields.h
# End Source File

# End Group
# Begin Group "SourceSystemStatistics h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsFont.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollector.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollectorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemDesc.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatIntElem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatRealElem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatStringElem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatTimeElem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsDefaultFont.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundFields.h
# End Source File

# End Group
# Begin Group "SourceSystemWindow h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCamera.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewport.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFlyNavigator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGLogoData.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCamera.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGNavigator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewport.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCamera.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSimpleSceneManager.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewport.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackball.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackballNavigator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewport.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWalkNavigator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowFields.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceExperimentalText inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractText.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFont.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontFactory.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedText.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyle.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFont.inl
# End Source File

# End Group
# Begin Group "SourceSystemAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/OSGAction.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGDrawActionBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemActionDrawAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/DrawAction/OSGDrawAction.inl
# End Source File

# End Group
# Begin Group "SourceSystemActionIntersectAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/IntersectAction/OSGIntersectAction.inl
# End Source File

# End Group
# Begin Group "SourceSystemActionRenderAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderAction.inl
# End Source File

# End Group
# Begin Group "SourceSystemClusterBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRenderNode.inl
# End Source File

# End Group
# Begin Group "SourceSystemClusterServer inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterWindowBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowMultiDisplay inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowSortFirst inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.inl
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainer inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.inl
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainerImpl inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodeImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.inl
# End Source File

# End Group
# Begin Group "SourceSystemFileIOBIN inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBase inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOBJ inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOFF inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOSG inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIORAW inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOScanParseSkel inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.inl
# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.inl
# End Source File

# End Group
# Begin Group "SourceSystemImage inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGImage.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemMaterial inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesGeometry inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesMisc inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroup.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsLight inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLight.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLight.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsMisc inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInline.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransform.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemRenderingBackend inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemState inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGState.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemStatistics inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollector.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemDesc.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatIntElem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatRealElem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatStringElem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatTimeElem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemWindow inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCamera.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewport.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCamera.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewport.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCamera.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSimpleSceneManager.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewport.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewport.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "SourceExperimentalText cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractText.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFont.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyphContour.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyleFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStylePFields.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedText.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFont.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyphContour.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTVectorFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFont.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFGlyphInfo.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTesselationHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGText.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGVectorFontGlyph.cpp
# End Source File

# End Group
# Begin Group "SourceSystemAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/OSGAction.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGDrawActionBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemActionDrawAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/DrawAction/OSGDrawAction.cpp
# End Source File

# End Group
# Begin Group "SourceSystemActionIntersectAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/IntersectAction/OSGIntersectAction.cpp
# End Source File

# End Group
# Begin Group "SourceSystemActionRenderAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderAction.cpp
# End Source File

# End Group
# Begin Group "SourceSystemClusterBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterException.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterNetwork.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterViewBuffer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRemoteAspect.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRenderNode.cpp
# End Source File

# End Group
# Begin Group "SourceSystemClusterServer cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Server/OSGClusterServer.cpp
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowMultiDisplay cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowSortFirst cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainer cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachment.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGChangeList.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGContainerTypeInst.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldDescription.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNode.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodePtr.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSimpleAttachments.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGThread.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainerImpl cpp"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBIN cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINLoader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINSceneFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINWriter.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOBJ cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OBJ/OSGOBJSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOFF cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OFF/OSGOFFSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOOSG cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGLoader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGSceneFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGWriter.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIORAW cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/RAW/OSGRAWSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOScanParseSkel cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.cpp
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.tab.cpp
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.lex.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLFile.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeDescs.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLSceneFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.cpp
# End Source File

# End Group
# Begin Group "SourceSystemImage cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGDATImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGGIFImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImage.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageGenericAtt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGJPGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMNGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMTDImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNMImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGSGIImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTGAImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTIFImageFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemMaterial cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesGeometry cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGExtrusionGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropFields.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropIndices.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPLengths.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPTypes.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGNodeGraph.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGSimpleGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGVolumeDraw.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesMisc cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsLight cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLight.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLight.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsMisc cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInline.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransform.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemRenderingBackend cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNode.cpp
# End Source File

# End Group
# Begin Group "SourceSystemState cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGState.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTestCubeMaps.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemStatistics cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsFont.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollector.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElem.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemDesc.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatIntElem.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatRealElem.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatStringElem.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatTimeElem.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsDefaultFont.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemWindow cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFlyNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGLogoData.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSimpleSceneManager.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackball.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackballNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWalkNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowBase.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "SourceExperimentalText ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemActionDrawAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemActionIntersectAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemActionRenderAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterServer ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterWindowBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterWindowMultiDisplay ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemClusterWindowSortFirst ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFieldContainer ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFieldContainerImpl ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBIN ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOBJ ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOFF ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOOSG ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIORAW ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOScanParseSkel ly"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y

BuildCmds= \
	bison.exe -d -v -pOSGScanParseSkel_  -bOSGScanParseSkel_ ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y \
	move OSGScanParseSkel_.tab.c OSGScanParseSkel.tab.cpp \
	move OSGScanParseSkel_.tab.h OSGScanParseSkel.tab.h \
	move OSGScanParseSkel_.output OSGScanParseSkel.tab.output \

"OSGScanParseSkel.tab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OSGScanParseSkel.tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.l

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.l

BuildCmds= \
	flex.exe -l -POSGScanParseSkel_ ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.l \
	move lex.OSGScanParseSkel_.c OSGScanParseSkel.lex.cpp \

"OSGScanParseSkel.lex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemImage ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemMaterial ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesGeometry ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesMisc ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresGroupsBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresGroupsLight ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresGroupsMisc ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemRenderingBackend ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemState ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemStatistics ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemWindow ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group

# End Target
# End Project
