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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILESYSTEMLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib libjpeg.lib libpng.lib zlib.lib tif32.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGSystem.dll

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILESYSTEMLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/BaseLib  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  -I../../../Source/Experimental/NativeFileIO  -I../../../Source/Experimental/NewAction/Actors  -I../../../Source/Experimental/NewAction  -I../../../Source/Experimental/SHL  -I../../../Source/Experimental/ShadowMapViewport  -I../../../Source/Experimental/Text  -I../../../Source/Experimental/WebInterface  -I../../../Source/System/Action/DrawAction  -I../../../Source/System/Action/IntersectAction  -I../../../Source/System/Action/RenderAction  -I../../../Source/System/Action  -I../../../Source/System/Cluster/Base  -I../../../Source/System/Cluster/Server  -I../../../Source/System/Cluster/Window/Base  -I../../../Source/System/Cluster/Window/MultiDisplay  -I../../../Source/System/Cluster/Window/SortFirst  -I../../../Source/System/Cluster/Window/SortLast  -I../../../Source/System/FieldContainer/Impl  -I../../../Source/System/FieldContainer  -I../../../Source/System/FileIO/3DS  -I../../../Source/System/FileIO/BIN  -I../../../Source/System/FileIO/Base  -I../../../Source/System/FileIO/DXF  -I../../../Source/System/FileIO/OBJ  -I../../../Source/System/FileIO/OFF  -I../../../Source/System/FileIO/OSG  -I../../../Source/System/FileIO/RAW  -I../../../Source/System/FileIO/SLP  -I../../../Source/System/FileIO/ScanParseSkel  -I../../../Source/System/FileIO/WRL  -I../../../Source/System/GraphOp  -I../../../Source/System/Image  -I../../../Source/System/Material  -I../../../Source/System/NodeCores/Drawables/Base  -I../../../Source/System/NodeCores/Drawables/Geometry  -I../../../Source/System/NodeCores/Drawables/Misc  -I../../../Source/System/NodeCores/Drawables/Nurbs/Internal  -I../../../Source/System/NodeCores/Drawables/Nurbs  -I../../../Source/System/NodeCores/Drawables/Particles  -I../../../Source/System/NodeCores/Drawables/VolRen  -I../../../Source/System/NodeCores/Groups/Base  -I../../../Source/System/NodeCores/Groups/Light  -I../../../Source/System/NodeCores/Groups/Misc  -I../../../Source/System/RenderingBackend  -I../../../Source/System/State  -I../../../Source/System/Statistics  -I../../../Source/System/Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib libjpeg.lib libpng.lib zlib.lib tif32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGSystem.dll
      

!ENDIF 

# Begin Target

# Name "SystemLib - Win32 Release"
# Name "SystemLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceExperimentalNativeFileIO h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBitPacker.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeneric.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGenericAtt.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOImage.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOOptions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOQuantizer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceExperimentalNewAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGActorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGBasicActorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGChildrenList.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstAction.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtendActorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtraChildrenList.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGFunctorArgumentType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGMultiFunctorStore.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGPriorityAction.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSingleFunctorStore.h
# End Source File

# End Group
# Begin Group "SourceExperimentalNewActionActors h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.h
# End Source File

# End Group
# Begin Group "SourceExperimentalSHL h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameter.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterAccess.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBool.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterInt.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrix.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterReal.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2f.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3f.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4f.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fFields.h
# End Source File

# End Group
# Begin Group "SourceExperimentalShadowMapViewport h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportFields.h
# End Source File

# End Group
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
# Begin Group "SourceExperimentalWebInterface h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/WebInterface/OSGWebInterface.h
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


# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderActionBase.h
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


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerFields.h
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
# Begin Group "SourceSystemClusterWindowSortLast h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowFields.h
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
SOURCE=../../../Source/System/FieldContainer/OSGCoredNodePtr.h
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
SOURCE=../../../Source/System/FieldContainer/OSGRefPtr.h
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
# Begin Group "SourceSystemFileIO3DS h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSLoader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSSceneFileType.h
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


# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGZStream.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIODXF h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFBlocks.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntities.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntitiesEntry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntityBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFFile.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFHeader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFInsert.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLayer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLine.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLtype.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFPolyline.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFRecord.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFSceneFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTableEntry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTables.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFVertex.h
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
# Begin Group "SourceSystemFileIOSLP h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/SLP/OSGSLPSceneFileType.h
# End Source File

# End Group
# Begin Group "SourceSystemFileIOScanParseSkel h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseLexer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkelBase.h
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
# Begin Group "SourceSystemGraphOp h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpSeq.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMaterialMergeGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMergeGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGPruneGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSharePtrGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSingleTypeGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSplitGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGStripeGraphOp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGVerifyGeoGraphOp.h
# End Source File

# End Group
# Begin Group "SourceSystemImage h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGDATImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGDDSImageFileType.h
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
SOURCE=../../../Source/System/Material/OSGFresnelMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialFields.h
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
SOURCE=../../../Source/System/Material/OSGPhongMaterial.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialFields.h
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
# Begin Group "SourceSystemNodeCoresDrawablesNurbs h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceFields.h
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbsInternal h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineBasisFunction.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineCurve2D.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTensorSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTrimmedSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve2D.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve3D.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierTensorSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPEdge.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPFace.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPMesh.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPVertex.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGErrorQuadTree.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGGraphTraverser.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGNurbsPatchSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGParSpaceTrimmer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGQuadTreeCreator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGSimplePolygon.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGdctptypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGpredicates.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGrounding.h
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
# Begin Group "SourceSystemNodeCoresDrawablesVolRen h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipper.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRRenderSlice.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSlice.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRTriangle.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVertex.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGQBit.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGSlicer.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGTextureManager.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGVolRenDef.h
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
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformFields.h
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
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupFields.h
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


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.h
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
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorFields.h
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
SOURCE=../../../Source/System/Window/OSGPolygonForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundFields.h
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
SOURCE=../../../Source/System/Window/OSGTextureBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForeground.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundFields.h
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

# Begin Group "SourceExperimentalNativeFileIO inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalNewAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGActorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGBasicActorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGChildrenList.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstAction.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtendActorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtraChildrenList.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGFunctorArgumentType.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGMultiFunctorStore.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGPriorityAction.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSingleFunctorStore.inl
# End Source File

# End Group
# Begin Group "SourceExperimentalNewActionActors inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.inl
# End Source File

# End Group
# Begin Group "SourceExperimentalSHL inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameter.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterAccess.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBool.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterInt.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrix.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterReal.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2f.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3f.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4f.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.inl
# End Source File

# End Group
# Begin Group "SourceExperimentalShadowMapViewport inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.inl
# End Source File

# End Group
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
# Begin Group "SourceExperimentalWebInterface inl"
# PROP Default_Filter ""
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

# Begin Source File
SOURCE=../../../Source/System/Cluster/Server/OSGClusterServer.inl
# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposer.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.inl
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
# Begin Group "SourceSystemClusterWindowSortLast inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemFieldContainer inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGCoredNodePtr.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGRefPtr.inl
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
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrDepImpl.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.inl
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
# Begin Group "SourceSystemFileIO3DS inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBIN inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBase inl"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIODXF inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTables.inl
# End Source File

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
# Begin Group "SourceSystemFileIOSLP inl"
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
# Begin Group "SourceSystemGraphOp inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSingleTypeGraphOp.inl
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
SOURCE=../../../Source/System/Material/OSGFresnelMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialBase.inl
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
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.inl
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
# Begin Group "SourceSystemNodeCoresDrawablesNurbs inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.inl
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbsInternal inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.inl
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
# Begin Group "SourceSystemNodeCoresDrawablesVolRen inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.inl
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
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.inl
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

# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNode.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.inl
# End Source File

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
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorBase.inl
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
SOURCE=../../../Source/System/Window/OSGPolygonForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundBase.inl
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
SOURCE=../../../Source/System/Window/OSGTextureBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForeground.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundBase.inl
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

# Begin Group "SourceExperimentalNativeFileIO cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBitPacker.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeneric.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGenericAtt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOImage.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOOptions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOQuantizer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceExperimentalNewAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGActorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGBasicActorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGChildrenList.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstAction.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtendActorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtraChildrenList.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGMultiFunctorStore.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGPriorityAction.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSingleFunctorStore.cpp
# End Source File

# End Group
# Begin Group "SourceExperimentalNewActionActors cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.cpp
# End Source File

# End Group
# Begin Group "SourceExperimentalSHL cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameter.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterAccess.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBool.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterInt.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrix.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterReal.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2f.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3f.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4f.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.cpp
# End Source File

# End Group
# Begin Group "SourceExperimentalShadowMapViewport cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.cpp
# End Source File

# End Group
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
# Begin Group "SourceExperimentalWebInterface cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/WebInterface/OSGWebInterface.cpp
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


# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderActionBase.cpp
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


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.cpp
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
# Begin Group "SourceSystemClusterWindowSortLast cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.cpp
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
# Begin Group "SourceSystemFileIO3DS cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSLoader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSSceneFileType.cpp
# End Source File

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
# Begin Group "SourceSystemFileIODXF cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFBlocks.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntities.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntitiesEntry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntityBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFFile.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFHeader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFInsert.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLayer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLine.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLtype.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFPolyline.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFRecord.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFSceneFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTableEntry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTables.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFVertex.cpp
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
# Begin Group "SourceSystemFileIOSLP cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/SLP/OSGSLPSceneFileType.cpp
# End Source File

# End Group
# Begin Group "SourceSystemFileIOScanParseSkel cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseLexer.cpp
# End Source File


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
# Begin Group "SourceSystemGraphOp cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpSeq.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMaterialMergeGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMergeGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGPruneGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSharePtrGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSplitGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGStripeGraphOp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGVerifyGeoGraphOp.cpp
# End Source File

# End Group
# Begin Group "SourceSystemImage cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGDATImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGDDSImageFileType.cpp
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
SOURCE=../../../Source/System/Material/OSGFresnelMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialBase.cpp
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
# Begin Group "SourceSystemNodeCoresDrawablesNurbs cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.cpp
# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbsInternal cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineBasisFunction.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineCurve2D.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTensorSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTrimmedSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve2D.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve3D.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierTensorSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPMesh.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGErrorQuadTree.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGGraphTraverser.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGNurbsPatchSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGParSpaceTrimmer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGQuadTreeCreator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGSimplePolygon.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGpredicates.cpp
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
# Begin Group "SourceSystemNodeCoresDrawablesVolRen cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipper.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderARBFragmentProgram.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderColorMatrix.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderNVRegisterCombiners.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRRenderSlice.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSlice.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRTriangle.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVertex.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGQBit.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGSlicer.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGTextureManager.cpp
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
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.cpp
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


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.cpp
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
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorBase.cpp
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
SOURCE=../../../Source/System/Window/OSGPolygonForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundBase.cpp
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
SOURCE=../../../Source/System/Window/OSGTextureBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundBase.cpp
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

# Begin Group "SourceExperimentalNativeFileIO ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalNewAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalNewActionActors ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalSHL ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalShadowMapViewport ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalText ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceExperimentalWebInterface ly"
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
# Begin Group "SourceSystemClusterWindowSortLast ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFieldContainer ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFieldContainerImpl ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIO3DS ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBIN ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIOBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemFileIODXF ly"
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
# Begin Group "SourceSystemFileIOSLP ly"
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
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.lpp

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build
InputPath=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.lpp

BuildCmds= \
	flex.exe -+ -POSGScanParseSkel_ ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.lpp \
	type lex.OSGScanParseSkel_.cc | sed -e "s/\(yy\)\(text_ptr\)/OSGScanParseSkel_\2/g" -e "s/\&cin/\&std::cin/g" -e "s/\&cout/\&std::cout/g" -e "s/cerr/std::cerr/g" -e "s/class istream;/#include <iosfwd>/g" -e "s/istream\*/\std::istream\*/g" -e "s/ostream\*/std::ostream\*/g" > OSGScanParseSkel.lex.cpp \

"OSGScanParseSkel.lex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemGraphOp ly"
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
# Begin Group "SourceSystemNodeCoresDrawablesNurbs ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbsInternal ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceSystemNodeCoresDrawablesVolRen ly"
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


# Begin Group "Header Install"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceExperimentalNativeFileIO Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOBase.h > ../include/OpenSG/OSGNFIOBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOBitPacker.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOBitPacker.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOBitPacker.h > ../include/OpenSG/OSGNFIOBitPacker.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOFactory.h > ../include/OpenSG/OSGNFIOFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeneric.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOGeneric.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOGeneric.h > ../include/OpenSG/OSGNFIOGeneric.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGenericAtt.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOGenericAtt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOGenericAtt.h > ../include/OpenSG/OSGNFIOGenericAtt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOGeometry.h > ../include/OpenSG/OSGNFIOGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOImage.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOImage.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOImage.h > ../include/OpenSG/OSGNFIOImage.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOOptions.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOOptions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOOptions.h > ../include/OpenSG/OSGNFIOOptions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOQuantizer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOQuantizer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOQuantizer.h > ../include/OpenSG/OSGNFIOQuantizer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NativeFileIO/OSGNFIOSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNFIOSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NativeFileIO/OSGNFIOSceneFileType.h > ../include/OpenSG/OSGNFIOSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalNewAction Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGActorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGActorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGActorBase.h > ../include/OpenSG/OSGActorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGBasicActorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBasicActorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGBasicActorBase.h > ../include/OpenSG/OSGBasicActorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGChildrenList.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChildrenList.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGChildrenList.h > ../include/OpenSG/OSGChildrenList.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDepthFirstAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGDepthFirstAction.h > ../include/OpenSG/OSGDepthFirstAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDepthFirstStateAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.h > ../include/OpenSG/OSGDepthFirstStateAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGEmptyFunctorStore.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.h > ../include/OpenSG/OSGEmptyFunctorStore.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtendActorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExtendActorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGExtendActorBase.h > ../include/OpenSG/OSGExtendActorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtraChildrenList.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExtraChildrenList.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGExtraChildrenList.h > ../include/OpenSG/OSGExtraChildrenList.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGFunctorArgumentType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFunctorArgumentType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGFunctorArgumentType.h > ../include/OpenSG/OSGFunctorArgumentType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGMultiFunctorStore.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiFunctorStore.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGMultiFunctorStore.h > ../include/OpenSG/OSGMultiFunctorStore.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNewActionBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGNewActionBase.h > ../include/OpenSG/OSGNewActionBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNewActionTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGNewActionTypes.h > ../include/OpenSG/OSGNewActionTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGPriorityAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPriorityAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGPriorityAction.h > ../include/OpenSG/OSGPriorityAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleFunctorStore.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.h > ../include/OpenSG/OSGSimpleFunctorStore.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSingleFunctorStore.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSingleFunctorStore.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGSingleFunctorStore.h > ../include/OpenSG/OSGSingleFunctorStore.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGActorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGActorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGActorBase.inl > ../include/OpenSG/OSGActorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGBasicActorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBasicActorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGBasicActorBase.inl > ../include/OpenSG/OSGBasicActorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGChildrenList.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChildrenList.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGChildrenList.inl > ../include/OpenSG/OSGChildrenList.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDepthFirstAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGDepthFirstAction.inl > ../include/OpenSG/OSGDepthFirstAction.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDepthFirstStateAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGDepthFirstStateAction.inl > ../include/OpenSG/OSGDepthFirstStateAction.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGEmptyFunctorStore.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGEmptyFunctorStore.inl > ../include/OpenSG/OSGEmptyFunctorStore.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtendActorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExtendActorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGExtendActorBase.inl > ../include/OpenSG/OSGExtendActorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGExtraChildrenList.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExtraChildrenList.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGExtraChildrenList.inl > ../include/OpenSG/OSGExtraChildrenList.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGFunctorArgumentType.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFunctorArgumentType.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGFunctorArgumentType.inl > ../include/OpenSG/OSGFunctorArgumentType.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGMultiFunctorStore.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiFunctorStore.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGMultiFunctorStore.inl > ../include/OpenSG/OSGMultiFunctorStore.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGNewActionBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNewActionBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGNewActionBase.inl > ../include/OpenSG/OSGNewActionBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGPriorityAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPriorityAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGPriorityAction.inl > ../include/OpenSG/OSGPriorityAction.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleFunctorStore.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGSimpleFunctorStore.inl > ../include/OpenSG/OSGSimpleFunctorStore.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/OSGSingleFunctorStore.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSingleFunctorStore.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/OSGSingleFunctorStore.inl > ../include/OpenSG/OSGSingleFunctorStore.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalNewActionActors Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectActor.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.h > ../include/OpenSG/OSGIntersectActor.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectActorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.h > ../include/OpenSG/OSGIntersectActorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTestingExtendActor.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.h > ../include/OpenSG/OSGTestingExtendActor.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTestingExtendActorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.h > ../include/OpenSG/OSGTestingExtendActorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectActor.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGIntersectActor.inl > ../include/OpenSG/OSGIntersectActor.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectActorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGIntersectActorBase.inl > ../include/OpenSG/OSGIntersectActorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTestingExtendActor.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActor.inl > ../include/OpenSG/OSGTestingExtendActor.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTestingExtendActorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/NewAction/Actors/OSGTestingExtendActorBase.inl > ../include/OpenSG/OSGTestingExtendActorBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalSHL Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLChunk.h > ../include/OpenSG/OSGSHLChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLChunkBase.h > ../include/OpenSG/OSGSHLChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLChunkFields.h > ../include/OpenSG/OSGSHLChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLParameterChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLParameterChunk.h > ../include/OpenSG/OSGSHLParameterChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLParameterChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.h > ../include/OpenSG/OSGSHLParameterChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLParameterChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLParameterChunkFields.h > ../include/OpenSG/OSGSHLParameterChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderChunk.h > ../include/OpenSG/OSGShaderChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderChunkBase.h > ../include/OpenSG/OSGShaderChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderChunkFields.h > ../include/OpenSG/OSGShaderChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameter.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameter.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameter.h > ../include/OpenSG/OSGShaderParameter.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterAccess.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterAccess.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterAccess.h > ../include/OpenSG/OSGShaderParameterAccess.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBase.h > ../include/OpenSG/OSGShaderParameterBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBool.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBool.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBool.h > ../include/OpenSG/OSGShaderParameterBool.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBoolBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.h > ../include/OpenSG/OSGShaderParameterBoolBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBoolFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBoolFields.h > ../include/OpenSG/OSGShaderParameterBoolFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterChunk.h > ../include/OpenSG/OSGShaderParameterChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.h > ../include/OpenSG/OSGShaderParameterChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterChunkFields.h > ../include/OpenSG/OSGShaderParameterChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterFields.h > ../include/OpenSG/OSGShaderParameterFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterInt.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterInt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterInt.h > ../include/OpenSG/OSGShaderParameterInt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterIntBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterIntBase.h > ../include/OpenSG/OSGShaderParameterIntBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterIntFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterIntFields.h > ../include/OpenSG/OSGShaderParameterIntFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrix.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterMatrix.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterMatrix.h > ../include/OpenSG/OSGShaderParameterMatrix.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterMatrixBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.h > ../include/OpenSG/OSGShaderParameterMatrixBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterMatrixFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterMatrixFields.h > ../include/OpenSG/OSGShaderParameterMatrixFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterReal.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterReal.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterReal.h > ../include/OpenSG/OSGShaderParameterReal.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterRealBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterRealBase.h > ../include/OpenSG/OSGShaderParameterRealBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterRealFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterRealFields.h > ../include/OpenSG/OSGShaderParameterRealFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2f.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec2f.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec2f.h > ../include/OpenSG/OSGShaderParameterVec2f.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec2fBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.h > ../include/OpenSG/OSGShaderParameterVec2fBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec2fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec2fFields.h > ../include/OpenSG/OSGShaderParameterVec2fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3f.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec3f.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec3f.h > ../include/OpenSG/OSGShaderParameterVec3f.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec3fBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.h > ../include/OpenSG/OSGShaderParameterVec3fBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec3fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec3fFields.h > ../include/OpenSG/OSGShaderParameterVec3fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4f.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec4f.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec4f.h > ../include/OpenSG/OSGShaderParameterVec4f.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec4fBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.h > ../include/OpenSG/OSGShaderParameterVec4fBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec4fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec4fFields.h > ../include/OpenSG/OSGShaderParameterVec4fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLChunk.inl > ../include/OpenSG/OSGSHLChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLChunkBase.inl > ../include/OpenSG/OSGSHLChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLParameterChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLParameterChunk.inl > ../include/OpenSG/OSGSHLParameterChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSHLParameterChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGSHLParameterChunkBase.inl > ../include/OpenSG/OSGSHLParameterChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderChunk.inl > ../include/OpenSG/OSGShaderChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderChunkBase.inl > ../include/OpenSG/OSGShaderChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameter.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameter.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameter.inl > ../include/OpenSG/OSGShaderParameter.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterAccess.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterAccess.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterAccess.inl > ../include/OpenSG/OSGShaderParameterAccess.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBase.inl > ../include/OpenSG/OSGShaderParameterBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBool.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBool.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBool.inl > ../include/OpenSG/OSGShaderParameterBool.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterBoolBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterBoolBase.inl > ../include/OpenSG/OSGShaderParameterBoolBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterChunk.inl > ../include/OpenSG/OSGShaderParameterChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterChunkBase.inl > ../include/OpenSG/OSGShaderParameterChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterInt.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterInt.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterInt.inl > ../include/OpenSG/OSGShaderParameterInt.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterIntBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterIntBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterIntBase.inl > ../include/OpenSG/OSGShaderParameterIntBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrix.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterMatrix.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterMatrix.inl > ../include/OpenSG/OSGShaderParameterMatrix.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterMatrixBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterMatrixBase.inl > ../include/OpenSG/OSGShaderParameterMatrixBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterReal.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterReal.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterReal.inl > ../include/OpenSG/OSGShaderParameterReal.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterRealBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterRealBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterRealBase.inl > ../include/OpenSG/OSGShaderParameterRealBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2f.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec2f.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec2f.inl > ../include/OpenSG/OSGShaderParameterVec2f.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec2fBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec2fBase.inl > ../include/OpenSG/OSGShaderParameterVec2fBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3f.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec3f.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec3f.inl > ../include/OpenSG/OSGShaderParameterVec3f.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec3fBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec3fBase.inl > ../include/OpenSG/OSGShaderParameterVec3fBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4f.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec4f.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec4f.inl > ../include/OpenSG/OSGShaderParameterVec4f.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShaderParameterVec4fBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/SHL/OSGShaderParameterVec4fBase.inl > ../include/OpenSG/OSGShaderParameterVec4fBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalShadowMapViewport Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShadowMapViewport.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.h > ../include/OpenSG/OSGShadowMapViewport.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShadowMapViewportBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.h > ../include/OpenSG/OSGShadowMapViewportBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShadowMapViewportFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportFields.h > ../include/OpenSG/OSGShadowMapViewportFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShadowMapViewport.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewport.inl > ../include/OpenSG/OSGShadowMapViewport.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShadowMapViewportBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/ShadowMapViewport/OSGShadowMapViewportBase.inl > ../include/OpenSG/OSGShadowMapViewportBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalText Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractText.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAbstractText.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGAbstractText.h > ../include/OpenSG/OSGAbstractText.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAbstractTextBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGAbstractTextBase.h > ../include/OpenSG/OSGAbstractTextBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAbstractTextFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGAbstractTextFields.h > ../include/OpenSG/OSGAbstractTextFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFont.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFont.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFont.h > ../include/OpenSG/OSGFont.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontFactory.h > ../include/OpenSG/OSGFontFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontGlyph.h > ../include/OpenSG/OSGFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontGlyphContour.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontGlyphContour.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontGlyphContour.h > ../include/OpenSG/OSGFontGlyphContour.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyle.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontStyle.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontStyle.h > ../include/OpenSG/OSGFontStyle.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStyleFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontStyleFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontStyleFactory.h > ../include/OpenSG/OSGFontStyleFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontStylePFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontStylePFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontStylePFields.h > ../include/OpenSG/OSGFontStylePFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGImageFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGImageFontGlyph.h > ../include/OpenSG/OSGImageFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedText.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScreenAlignedText.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGScreenAlignedText.h > ../include/OpenSG/OSGScreenAlignedText.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScreenAlignedTextBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGScreenAlignedTextBase.h > ../include/OpenSG/OSGScreenAlignedTextBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScreenAlignedTextFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGScreenAlignedTextFields.h > ../include/OpenSG/OSGScreenAlignedTextFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyle.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyle.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyle.h > ../include/OpenSG/OSGSharedFontStyle.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleBase.h > ../include/OpenSG/OSGSharedFontStyleBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleFields.h > ../include/OpenSG/OSGSharedFontStyleFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleWrapper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.h > ../include/OpenSG/OSGSharedFontStyleWrapper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleWrapperBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.h > ../include/OpenSG/OSGSharedFontStyleWrapperBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleWrapperFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleWrapperFields.h > ../include/OpenSG/OSGSharedFontStyleWrapperFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFont.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTFont.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTFont.h > ../include/OpenSG/OSGTTFont.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTFontGlyph.h > ../include/OpenSG/OSGTTFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontGlyphContour.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTFontGlyphContour.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTFontGlyphContour.h > ../include/OpenSG/OSGTTFontGlyphContour.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTFontStyle.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTFontStyle.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTFontStyle.h > ../include/OpenSG/OSGTTFontStyle.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTImageFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTImageFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTImageFontGlyph.h > ../include/OpenSG/OSGTTImageFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTTVectorFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTTVectorFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTTVectorFontGlyph.h > ../include/OpenSG/OSGTTVectorFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFont.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFFont.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFFont.h > ../include/OpenSG/OSGTXFFont.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFFontGlyph.h > ../include/OpenSG/OSGTXFFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFontStyle.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFFontStyle.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFFontStyle.h > ../include/OpenSG/OSGTXFFontStyle.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFGlyphInfo.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFGlyphInfo.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFGlyphInfo.h > ../include/OpenSG/OSGTXFGlyphInfo.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFImageFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFImageFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFImageFontGlyph.h > ../include/OpenSG/OSGTXFImageFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTesselationHandler.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTesselationHandler.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTesselationHandler.h > ../include/OpenSG/OSGTesselationHandler.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGText.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGText.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGText.h > ../include/OpenSG/OSGText.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGVectorFontGlyph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVectorFontGlyph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGVectorFontGlyph.h > ../include/OpenSG/OSGVectorFontGlyph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractText.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAbstractText.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGAbstractText.inl > ../include/OpenSG/OSGAbstractText.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGAbstractTextBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAbstractTextBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGAbstractTextBase.inl > ../include/OpenSG/OSGAbstractTextBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFont.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFont.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFont.inl > ../include/OpenSG/OSGFont.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGFontFactory.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFontFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGFontFactory.inl > ../include/OpenSG/OSGFontFactory.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedText.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScreenAlignedText.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGScreenAlignedText.inl > ../include/OpenSG/OSGScreenAlignedText.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGScreenAlignedTextBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScreenAlignedTextBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGScreenAlignedTextBase.inl > ../include/OpenSG/OSGScreenAlignedTextBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyle.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyle.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyle.inl > ../include/OpenSG/OSGSharedFontStyle.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleBase.inl > ../include/OpenSG/OSGSharedFontStyleBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleWrapper.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleWrapper.inl > ../include/OpenSG/OSGSharedFontStyleWrapper.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedFontStyleWrapperBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGSharedFontStyleWrapperBase.inl > ../include/OpenSG/OSGSharedFontStyleWrapperBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Experimental/Text/OSGTXFFont.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTXFFont.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/Text/OSGTXFFont.inl > ../include/OpenSG/OSGTXFFont.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceExperimentalWebInterface Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Experimental/WebInterface/OSGWebInterface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWebInterface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Experimental/WebInterface/OSGWebInterface.h > ../include/OpenSG/OSGWebInterface.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemAction Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/OSGAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/OSGAction.h > ../include/OpenSG/OSGAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGDrawActionBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawActionBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/OSGDrawActionBase.h > ../include/OpenSG/OSGDrawActionBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/OSGAction.inl > ../include/OpenSG/OSGAction.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/OSGDrawActionBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawActionBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/OSGDrawActionBase.inl > ../include/OpenSG/OSGDrawActionBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemActionDrawAction Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/DrawAction/OSGDrawAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/DrawAction/OSGDrawAction.h > ../include/OpenSG/OSGDrawAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/DrawAction/OSGDrawAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/DrawAction/OSGDrawAction.inl > ../include/OpenSG/OSGDrawAction.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemActionIntersectAction Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/IntersectAction/OSGIntersectAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/IntersectAction/OSGIntersectAction.h > ../include/OpenSG/OSGIntersectAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/IntersectAction/OSGIntersectAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIntersectAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/IntersectAction/OSGIntersectAction.inl > ../include/OpenSG/OSGIntersectAction.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemActionRenderAction Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRenderAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/RenderAction/OSGRenderAction.h > ../include/OpenSG/OSGRenderAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderActionBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRenderActionBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/RenderAction/OSGRenderActionBase.h > ../include/OpenSG/OSGRenderActionBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Action/RenderAction/OSGRenderAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRenderAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Action/RenderAction/OSGRenderAction.inl > ../include/OpenSG/OSGRenderAction.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterException.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterException.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGClusterException.h > ../include/OpenSG/OSGClusterException.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterNetwork.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterNetwork.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGClusterNetwork.h > ../include/OpenSG/OSGClusterNetwork.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGClusterViewBuffer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterViewBuffer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGClusterViewBuffer.h > ../include/OpenSG/OSGClusterViewBuffer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRemoteAspect.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRemoteAspect.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGRemoteAspect.h > ../include/OpenSG/OSGRemoteAspect.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRenderNode.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRenderNode.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGRenderNode.h > ../include/OpenSG/OSGRenderNode.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Base/OSGRenderNode.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRenderNode.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Base/OSGRenderNode.inl > ../include/OpenSG/OSGRenderNode.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterServer Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Server/OSGClusterServer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterServer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Server/OSGClusterServer.h > ../include/OpenSG/OSGClusterServer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Server/OSGClusterServer.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterServer.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Server/OSGClusterServer.inl > ../include/OpenSG/OSGClusterServer.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGClusterWindow.h > ../include/OpenSG/OSGClusterWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.h > ../include/OpenSG/OSGClusterWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGClusterWindowFields.h > ../include/OpenSG/OSGClusterWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageComposer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGImageComposer.h > ../include/OpenSG/OSGImageComposer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageComposerBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.h > ../include/OpenSG/OSGImageComposerBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageComposerFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGImageComposerFields.h > ../include/OpenSG/OSGImageComposerFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGClusterWindow.inl > ../include/OpenSG/OSGClusterWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClusterWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGClusterWindowBase.inl > ../include/OpenSG/OSGClusterWindowBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposer.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageComposer.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGImageComposer.inl > ../include/OpenSG/OSGImageComposer.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageComposerBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/Base/OSGImageComposerBase.inl > ../include/OpenSG/OSGImageComposerBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowMultiDisplay Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiDisplayWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.h > ../include/OpenSG/OSGMultiDisplayWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiDisplayWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.h > ../include/OpenSG/OSGMultiDisplayWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiDisplayWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowFields.h > ../include/OpenSG/OSGMultiDisplayWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiDisplayWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindow.inl > ../include/OpenSG/OSGMultiDisplayWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMultiDisplayWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/MultiDisplay/OSGMultiDisplayWindowBase.inl > ../include/OpenSG/OSGMultiDisplayWindowBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowSortFirst Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortFirstWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.h > ../include/OpenSG/OSGSortFirstWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortFirstWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.h > ../include/OpenSG/OSGSortFirstWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortFirstWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowFields.h > ../include/OpenSG/OSGSortFirstWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileGeometryLoad.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.h > ../include/OpenSG/OSGTileGeometryLoad.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileLoadBalancer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.h > ../include/OpenSG/OSGTileLoadBalancer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortFirstWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindow.inl > ../include/OpenSG/OSGSortFirstWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortFirstWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGSortFirstWindowBase.inl > ../include/OpenSG/OSGSortFirstWindowBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileGeometryLoad.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGTileGeometryLoad.inl > ../include/OpenSG/OSGTileGeometryLoad.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileLoadBalancer.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortFirst/OSGTileLoadBalancer.inl > ../include/OpenSG/OSGTileLoadBalancer.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemClusterWindowSortLast Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSepiaComposer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposer.h > ../include/OpenSG/OSGSepiaComposer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSepiaComposerBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.h > ../include/OpenSG/OSGSepiaComposerBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSepiaComposerFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerFields.h > ../include/OpenSG/OSGSepiaComposerFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortLastWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.h > ../include/OpenSG/OSGSortLastWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortLastWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.h > ../include/OpenSG/OSGSortLastWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortLastWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowFields.h > ../include/OpenSG/OSGSortLastWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSepiaComposerBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSepiaComposerBase.inl > ../include/OpenSG/OSGSepiaComposerBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortLastWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindow.inl > ../include/OpenSG/OSGSortLastWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSortLastWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Cluster/Window/SortLast/OSGSortLastWindowBase.inl > ../include/OpenSG/OSGSortLastWindowBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFieldContainer Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachment.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachment.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachment.h > ../include/OpenSG/OSGAttachment.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentContainer.h > ../include/OpenSG/OSGAttachmentContainer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentContainerFieldDataType.h > ../include/OpenSG/OSGAttachmentContainerFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentContainerFields.h > ../include/OpenSG/OSGAttachmentContainerFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentContainerPtr.h > ../include/OpenSG/OSGAttachmentContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentFieldDataType.h > ../include/OpenSG/OSGAttachmentFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentFields.h > ../include/OpenSG/OSGAttachmentFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentMapFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentMapFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentMapFieldDataType.h > ../include/OpenSG/OSGAttachmentMapFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentMapFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentMapFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentMapFields.h > ../include/OpenSG/OSGAttachmentMapFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGAttachmentPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGAttachmentPtr.h > ../include/OpenSG/OSGAttachmentPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGChangeList.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChangeList.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGChangeList.h > ../include/OpenSG/OSGChangeList.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGCoredNodePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCoredNodePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGCoredNodePtr.h > ../include/OpenSG/OSGCoredNodePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainer.h > ../include/OpenSG/OSGFieldContainer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerBase.h > ../include/OpenSG/OSGFieldContainerBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerFactory.h > ../include/OpenSG/OSGFieldContainerFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerFieldDataType.h > ../include/OpenSG/OSGFieldContainerFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerFields.h > ../include/OpenSG/OSGFieldContainerFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerProperties.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerProperties.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerProperties.h > ../include/OpenSG/OSGFieldContainerProperties.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerPtr.h > ../include/OpenSG/OSGFieldContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerPtrForward.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrForward.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerPtrForward.h > ../include/OpenSG/OSGFieldContainerPtrForward.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldContainerType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldContainerType.h > ../include/OpenSG/OSGFieldContainerType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGFieldDescription.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldDescription.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGFieldDescription.h > ../include/OpenSG/OSGFieldDescription.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFAttachmentContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFAttachmentContainerPtr.h > ../include/OpenSG/OSGMFAttachmentContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentMap.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFAttachmentMap.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFAttachmentMap.h > ../include/OpenSG/OSGMFAttachmentMap.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFAttachmentPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFAttachmentPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFAttachmentPtr.h > ../include/OpenSG/OSGMFAttachmentPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFFieldContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFFieldContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFFieldContainerPtr.h > ../include/OpenSG/OSGMFFieldContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFFieldContainerTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFFieldContainerTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFFieldContainerTypes.h > ../include/OpenSG/OSGMFFieldContainerTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFNodeCorePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFNodeCorePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFNodeCorePtr.h > ../include/OpenSG/OSGMFNodeCorePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGMFNodePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFNodePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGMFNodePtr.h > ../include/OpenSG/OSGMFNodePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNode.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNode.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNode.h > ../include/OpenSG/OSGNode.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeCore.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeCore.h > ../include/OpenSG/OSGNodeCore.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCoreFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeCoreFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeCoreFieldDataType.h > ../include/OpenSG/OSGNodeCoreFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCoreFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeCoreFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeCoreFields.h > ../include/OpenSG/OSGNodeCoreFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeFieldDataType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeFieldDataType.h > ../include/OpenSG/OSGNodeFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeFields.h > ../include/OpenSG/OSGNodeFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodePtr.h > ../include/OpenSG/OSGNodePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGPrimary.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPrimary.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGPrimary.h > ../include/OpenSG/OSGPrimary.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGRefPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRefPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGRefPtr.h > ../include/OpenSG/OSGRefPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFAttachmentContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFAttachmentContainerPtr.h > ../include/OpenSG/OSGSFAttachmentContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentMap.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFAttachmentMap.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFAttachmentMap.h > ../include/OpenSG/OSGSFAttachmentMap.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFAttachmentPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFAttachmentPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFAttachmentPtr.h > ../include/OpenSG/OSGSFAttachmentPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFFieldContainerPtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFFieldContainerPtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFFieldContainerPtr.h > ../include/OpenSG/OSGSFFieldContainerPtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFFieldContainerTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFFieldContainerTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFFieldContainerTypes.h > ../include/OpenSG/OSGSFFieldContainerTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFNodeCorePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFNodeCorePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFNodeCorePtr.h > ../include/OpenSG/OSGSFNodeCorePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSFNodePtr.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFNodePtr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSFNodePtr.h > ../include/OpenSG/OSGSFNodePtr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSimpleAttachments.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleAttachments.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSimpleAttachments.h > ../include/OpenSG/OSGSimpleAttachments.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGSystemDef.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSystemDef.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGSystemDef.h > ../include/OpenSG/OSGSystemDef.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGThread.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGThread.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGThread.h > ../include/OpenSG/OSGThread.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGCoredNodePtr.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCoredNodePtr.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGCoredNodePtr.inl > ../include/OpenSG/OSGCoredNodePtr.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGNodeCore.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeCore.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGNodeCore.inl > ../include/OpenSG/OSGNodeCore.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/OSGRefPtr.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRefPtr.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/OSGRefPtr.inl > ../include/OpenSG/OSGRefPtr.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFieldContainerImpl Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.h > ../include/OpenSG/OSGAttachmentContainerImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerPtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.h > ../include/OpenSG/OSGAttachmentContainerPtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.h > ../include/OpenSG/OSGAttachmentImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentPtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.h > ../include/OpenSG/OSGAttachmentPtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCNodePtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.h > ../include/OpenSG/OSGCNodePtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerFactoryImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.h > ../include/OpenSG/OSGFieldContainerFactoryImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.h > ../include/OpenSG/OSGFieldContainerImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrFuncsImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.h > ../include/OpenSG/OSGFieldContainerPtrFuncsImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.h > ../include/OpenSG/OSGFieldContainerPtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerTypeImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.h > ../include/OpenSG/OSGFieldContainerTypeImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldDescriptionImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.h > ../include/OpenSG/OSGFieldDescriptionImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGMFNodePtrDepImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFNodePtrDepImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGMFNodePtrDepImpl.h > ../include/OpenSG/OSGMFNodePtrDepImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGMFNodePtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFNodePtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGMFNodePtrImpl.h > ../include/OpenSG/OSGMFNodePtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodeImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGNodeImpl.h > ../include/OpenSG/OSGNodeImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodePtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.h > ../include/OpenSG/OSGNodePtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGSFNodePtrDepImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFNodePtrDepImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGSFNodePtrDepImpl.h > ../include/OpenSG/OSGSFNodePtrDepImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGSFNodePtrImpl.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFNodePtrImpl.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGSFNodePtrImpl.h > ../include/OpenSG/OSGSFNodePtrImpl.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerImpl.inl > ../include/OpenSG/OSGAttachmentContainerImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrDepImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerPtrDepImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrDepImpl.inl > ../include/OpenSG/OSGAttachmentContainerPtrDepImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentContainerPtrImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentContainerPtrImpl.inl > ../include/OpenSG/OSGAttachmentContainerPtrImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentImpl.inl > ../include/OpenSG/OSGAttachmentImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrDepImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentPtrDepImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrDepImpl.inl > ../include/OpenSG/OSGAttachmentPtrDepImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGAttachmentPtrImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGAttachmentPtrImpl.inl > ../include/OpenSG/OSGAttachmentPtrImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCNodePtrImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGCNodePtrImpl.inl > ../include/OpenSG/OSGCNodePtrImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerFactoryImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerFactoryImpl.inl > ../include/OpenSG/OSGFieldContainerFactoryImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerImpl.inl > ../include/OpenSG/OSGFieldContainerImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrDepImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrDepImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrDepImpl.inl > ../include/OpenSG/OSGFieldContainerPtrDepImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrFuncsImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrFuncsImpl.inl > ../include/OpenSG/OSGFieldContainerPtrFuncsImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerPtrImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerPtrImpl.inl > ../include/OpenSG/OSGFieldContainerPtrImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeDepImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerTypeDepImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeDepImpl.inl > ../include/OpenSG/OSGFieldContainerTypeDepImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldContainerTypeImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldContainerTypeImpl.inl > ../include/OpenSG/OSGFieldContainerTypeImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldDescriptionImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGFieldDescriptionImpl.inl > ../include/OpenSG/OSGFieldDescriptionImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodeImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGNodeImpl.inl > ../include/OpenSG/OSGNodeImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrDepImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodePtrDepImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGNodePtrDepImpl.inl > ../include/OpenSG/OSGNodePtrDepImpl.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodePtrImpl.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FieldContainer/Impl/OSGNodePtrImpl.inl > ../include/OpenSG/OSGNodePtrImpl.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIO3DS Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSLoader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSG3DSLoader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/3DS/OSG3DSLoader.h > ../include/OpenSG/OSG3DSLoader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/3DS/OSG3DSSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSG3DSSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/3DS/OSG3DSSceneFileType.h > ../include/OpenSG/OSG3DSSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOBIN Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINLoader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBINLoader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/BIN/OSGBINLoader.h > ../include/OpenSG/OSGBINLoader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBINSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/BIN/OSGBINSceneFileType.h > ../include/OpenSG/OSGBINSceneFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/BIN/OSGBINWriter.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBINWriter.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/BIN/OSGBINWriter.h > ../include/OpenSG/OSGBINWriter.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileHandler.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSceneFileHandler.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/Base/OSGSceneFileHandler.h > ../include/OpenSG/OSGSceneFileHandler.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/Base/OSGSceneFileType.h > ../include/OpenSG/OSGSceneFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/Base/OSGZStream.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGZStream.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/Base/OSGZStream.h > ../include/OpenSG/OSGZStream.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIODXF Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFBlocks.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFBlocks.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFBlocks.h > ../include/OpenSG/OSGDXFBlocks.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntities.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFEntities.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFEntities.h > ../include/OpenSG/OSGDXFEntities.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntitiesEntry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFEntitiesEntry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFEntitiesEntry.h > ../include/OpenSG/OSGDXFEntitiesEntry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFEntityBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFEntityBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFEntityBase.h > ../include/OpenSG/OSGDXFEntityBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFFile.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFFile.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFFile.h > ../include/OpenSG/OSGDXFFile.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFHeader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFHeader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFHeader.h > ../include/OpenSG/OSGDXFHeader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFInsert.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFInsert.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFInsert.h > ../include/OpenSG/OSGDXFInsert.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLayer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFLayer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFLayer.h > ../include/OpenSG/OSGDXFLayer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLine.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFLine.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFLine.h > ../include/OpenSG/OSGDXFLine.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFLtype.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFLtype.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFLtype.h > ../include/OpenSG/OSGDXFLtype.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFPolyline.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFPolyline.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFPolyline.h > ../include/OpenSG/OSGDXFPolyline.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFRecord.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFRecord.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFRecord.h > ../include/OpenSG/OSGDXFRecord.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFSceneFileType.h > ../include/OpenSG/OSGDXFSceneFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTableEntry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFTableEntry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFTableEntry.h > ../include/OpenSG/OSGDXFTableEntry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTables.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFTables.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFTables.h > ../include/OpenSG/OSGDXFTables.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFVertex.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFVertex.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFVertex.h > ../include/OpenSG/OSGDXFVertex.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/DXF/OSGDXFTables.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDXFTables.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/DXF/OSGDXFTables.inl > ../include/OpenSG/OSGDXFTables.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOOBJ Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OBJ/OSGOBJSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGOBJSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/OBJ/OSGOBJSceneFileType.h > ../include/OpenSG/OSGOBJSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOOFF Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OFF/OSGOFFSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGOFFSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/OFF/OSGOFFSceneFileType.h > ../include/OpenSG/OSGOFFSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOOSG Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGLoader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLoader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/OSG/OSGLoader.h > ../include/OpenSG/OSGLoader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGOSGSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/OSG/OSGOSGSceneFileType.h > ../include/OpenSG/OSGOSGSceneFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/OSG/OSGOSGWriter.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGOSGWriter.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/OSG/OSGOSGWriter.h > ../include/OpenSG/OSGOSGWriter.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIORAW Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/RAW/OSGRAWSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRAWSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/RAW/OSGRAWSceneFileType.h > ../include/OpenSG/OSGRAWSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOSLP Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/SLP/OSGSLPSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSLPSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/SLP/OSGSLPSceneFileType.h > ../include/OpenSG/OSGSLPSceneFileType.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOScanParseSkel Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseFieldTypeMapper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.h > ../include/OpenSG/OSGScanParseFieldTypeMapper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseLexer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseLexer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseLexer.h > ../include/OpenSG/OSGScanParseLexer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseSkel.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.h > ../include/OpenSG/OSGScanParseSkel.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkelBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseSkelBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkelBase.h > ../include/OpenSG/OSGScanParseSkelBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseFieldTypeMapper.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseFieldTypeMapper.inl > ../include/OpenSG/OSGScanParseFieldTypeMapper.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.tab.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGScanParseSkel.tab.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" OSGScanParseSkel.tab.h > ../include/OpenSG/OSGScanParseSkel.tab.h

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemFileIOWRL Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLFile.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLFile.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLFile.h > ../include/OpenSG/OSGVRMLFile.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeDescs.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLNodeDescs.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLNodeDescs.h > ../include/OpenSG/OSGVRMLNodeDescs.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLNodeFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.h > ../include/OpenSG/OSGVRMLNodeFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLSceneFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLSceneFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLSceneFileType.h > ../include/OpenSG/OSGVRMLSceneFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLWriteAction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.h > ../include/OpenSG/OSGVRMLWriteAction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLNodeFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLNodeFactory.inl > ../include/OpenSG/OSGVRMLNodeFactory.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVRMLWriteAction.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/FileIO/WRL/OSGVRMLWriteAction.inl > ../include/OpenSG/OSGVRMLWriteAction.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemGraphOp Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGGraphOp.h > ../include/OpenSG/OSGGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphOpFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGGraphOpFactory.h > ../include/OpenSG/OSGGraphOpFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGGraphOpSeq.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphOpSeq.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGGraphOpSeq.h > ../include/OpenSG/OSGGraphOpSeq.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMaterialMergeGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialMergeGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGMaterialMergeGraphOp.h > ../include/OpenSG/OSGMaterialMergeGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGMergeGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMergeGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGMergeGraphOp.h > ../include/OpenSG/OSGMergeGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGPruneGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPruneGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGPruneGraphOp.h > ../include/OpenSG/OSGPruneGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSharePtrGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharePtrGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGSharePtrGraphOp.h > ../include/OpenSG/OSGSharePtrGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSingleTypeGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSingleTypeGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGSingleTypeGraphOp.h > ../include/OpenSG/OSGSingleTypeGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSplitGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSplitGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGSplitGraphOp.h > ../include/OpenSG/OSGSplitGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGStripeGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStripeGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGStripeGraphOp.h > ../include/OpenSG/OSGStripeGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGVerifyGeoGraphOp.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVerifyGeoGraphOp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGVerifyGeoGraphOp.h > ../include/OpenSG/OSGVerifyGeoGraphOp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/GraphOp/OSGSingleTypeGraphOp.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSingleTypeGraphOp.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/GraphOp/OSGSingleTypeGraphOp.inl > ../include/OpenSG/OSGSingleTypeGraphOp.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemImage Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Image/OSGDATImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDATImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGDATImageFileType.h > ../include/OpenSG/OSGDATImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGDDSImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDDSImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGDDSImageFileType.h > ../include/OpenSG/OSGDDSImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGGIFImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGIFImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGGIFImageFileType.h > ../include/OpenSG/OSGGIFImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImage.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImage.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImage.h > ../include/OpenSG/OSGImage.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageBase.h > ../include/OpenSG/OSGImageBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageFields.h > ../include/OpenSG/OSGImageFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileHandler.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageFileHandler.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageFileHandler.h > ../include/OpenSG/OSGImageFileHandler.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageFileType.h > ../include/OpenSG/OSGImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageGenericAtt.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageGenericAtt.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageGenericAtt.h > ../include/OpenSG/OSGImageGenericAtt.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGJPGImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGJPGImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGJPGImageFileType.h > ../include/OpenSG/OSGJPGImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMFImageTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFImageTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGMFImageTypes.h > ../include/OpenSG/OSGMFImageTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMNGImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMNGImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGMNGImageFileType.h > ../include/OpenSG/OSGMNGImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGMTDImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMTDImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGMTDImageFileType.h > ../include/OpenSG/OSGMTDImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNGImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPNGImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGPNGImageFileType.h > ../include/OpenSG/OSGPNGImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGPNMImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPNMImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGPNMImageFileType.h > ../include/OpenSG/OSGPNMImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGSGIImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSGIImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGSGIImageFileType.h > ../include/OpenSG/OSGSGIImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTGAImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTGAImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGTGAImageFileType.h > ../include/OpenSG/OSGTGAImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGTIFImageFileType.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTIFImageFileType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGTIFImageFileType.h > ../include/OpenSG/OSGTIFImageFileType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImage.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImage.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImage.inl > ../include/OpenSG/OSGImage.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Image/OSGImageBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Image/OSGImageBase.inl > ../include/OpenSG/OSGImageBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemMaterial Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChunkMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGChunkMaterial.h > ../include/OpenSG/OSGChunkMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChunkMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGChunkMaterialBase.h > ../include/OpenSG/OSGChunkMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChunkMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGChunkMaterialFields.h > ../include/OpenSG/OSGChunkMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFresnelMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGFresnelMaterial.h > ../include/OpenSG/OSGFresnelMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFresnelMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGFresnelMaterialBase.h > ../include/OpenSG/OSGFresnelMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFresnelMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGFresnelMaterialFields.h > ../include/OpenSG/OSGFresnelMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGMaterial.h > ../include/OpenSG/OSGMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGMaterialBase.h > ../include/OpenSG/OSGMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGMaterialFields.h > ../include/OpenSG/OSGMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPhongMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGPhongMaterial.h > ../include/OpenSG/OSGPhongMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPhongMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGPhongMaterialBase.h > ../include/OpenSG/OSGPhongMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPhongMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGPhongMaterialFields.h > ../include/OpenSG/OSGPhongMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleMaterial.h > ../include/OpenSG/OSGSimpleMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleMaterialBase.h > ../include/OpenSG/OSGSimpleMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleMaterialFields.h > ../include/OpenSG/OSGSimpleMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterial.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleTexturedMaterial.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleTexturedMaterial.h > ../include/OpenSG/OSGSimpleTexturedMaterial.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleTexturedMaterialBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleTexturedMaterialBase.h > ../include/OpenSG/OSGSimpleTexturedMaterialBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleTexturedMaterialFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleTexturedMaterialFields.h > ../include/OpenSG/OSGSimpleTexturedMaterialFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChunkMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGChunkMaterial.inl > ../include/OpenSG/OSGChunkMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGChunkMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGChunkMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGChunkMaterialBase.inl > ../include/OpenSG/OSGChunkMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFresnelMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGFresnelMaterial.inl > ../include/OpenSG/OSGFresnelMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGFresnelMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFresnelMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGFresnelMaterialBase.inl > ../include/OpenSG/OSGFresnelMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGMaterial.inl > ../include/OpenSG/OSGMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGMaterialBase.inl > ../include/OpenSG/OSGMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPhongMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGPhongMaterial.inl > ../include/OpenSG/OSGPhongMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGPhongMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPhongMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGPhongMaterialBase.inl > ../include/OpenSG/OSGPhongMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleMaterial.inl > ../include/OpenSG/OSGSimpleMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleMaterialBase.inl > ../include/OpenSG/OSGSimpleMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterial.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleTexturedMaterial.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleTexturedMaterial.inl > ../include/OpenSG/OSGSimpleTexturedMaterial.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Material/OSGSimpleTexturedMaterialBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleTexturedMaterialBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Material/OSGSimpleTexturedMaterialBase.inl > ../include/OpenSG/OSGSimpleTexturedMaterialBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawable.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.h > ../include/OpenSG/OSGDrawable.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawableBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.h > ../include/OpenSG/OSGDrawableBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawableFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGDrawableFields.h > ../include/OpenSG/OSGDrawableFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialDrawable.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.h > ../include/OpenSG/OSGMaterialDrawable.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialDrawableBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.h > ../include/OpenSG/OSGMaterialDrawableBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialDrawableFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableFields.h > ../include/OpenSG/OSGMaterialDrawableFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawable.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGDrawable.inl > ../include/OpenSG/OSGDrawable.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawableBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGDrawableBase.inl > ../include/OpenSG/OSGDrawableBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialDrawable.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawable.inl > ../include/OpenSG/OSGMaterialDrawable.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialDrawableBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Base/OSGMaterialDrawableBase.inl > ../include/OpenSG/OSGMaterialDrawableBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesGeometry Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGExtrusionGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExtrusionGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGExtrusionGeometry.h > ../include/OpenSG/OSGExtrusionGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFaceIterator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.h > ../include/OpenSG/OSGFaceIterator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoColorsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoColorsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoColorsFields.h > ../include/OpenSG/OSGGeoColorsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoFunctions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.h > ../include/OpenSG/OSGGeoFunctions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoIndicesFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoIndicesFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoIndicesFields.h > ../include/OpenSG/OSGGeoIndicesFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoNormalsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoNormalsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoNormalsFields.h > ../include/OpenSG/OSGGeoNormalsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPLengthsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPLengthsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPLengthsFields.h > ../include/OpenSG/OSGGeoPLengthsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPTypesFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPTypesFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPTypesFields.h > ../include/OpenSG/OSGGeoPTypesFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPositionsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPositionsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPositionsFields.h > ../include/OpenSG/OSGGeoPositionsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropColors.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.h > ../include/OpenSG/OSGGeoPropColors.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropFields.h > ../include/OpenSG/OSGGeoPropFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropIndices.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropIndices.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropIndices.h > ../include/OpenSG/OSGGeoPropIndices.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropNormals.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.h > ../include/OpenSG/OSGGeoPropNormals.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPLengths.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropPLengths.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPLengths.h > ../include/OpenSG/OSGGeoPropPLengths.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropPTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPTypes.h > ../include/OpenSG/OSGGeoPropPTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropPositions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.h > ../include/OpenSG/OSGGeoPropPositions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPtrs.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropPtrs.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPtrs.h > ../include/OpenSG/OSGGeoPropPtrs.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropTexCoords.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.h > ../include/OpenSG/OSGGeoPropTexCoords.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoProperty.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoProperty.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoProperty.h > ../include/OpenSG/OSGGeoProperty.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropertyBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.h > ../include/OpenSG/OSGGeoPropertyBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropertyInterface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.h > ../include/OpenSG/OSGGeoPropertyInterface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPumpFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.h > ../include/OpenSG/OSGGeoPumpFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoTexCoordsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoTexCoordsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoTexCoordsFields.h > ../include/OpenSG/OSGGeoTexCoordsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.h > ../include/OpenSG/OSGGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeometryBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.h > ../include/OpenSG/OSGGeometryBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeometryFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryFields.h > ../include/OpenSG/OSGGeometryFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGNodeGraph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNodeGraph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGNodeGraph.h > ../include/OpenSG/OSGNodeGraph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPrimitiveIterator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.h > ../include/OpenSG/OSGPrimitiveIterator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGSimpleGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGSimpleGeometry.h > ../include/OpenSG/OSGSimpleGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTriangleIterator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.h > ../include/OpenSG/OSGTriangleIterator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGVolumeDraw.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolumeDraw.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGVolumeDraw.h > ../include/OpenSG/OSGVolumeDraw.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFaceIterator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGFaceIterator.inl > ../include/OpenSG/OSGFaceIterator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoFunctions.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoFunctions.inl > ../include/OpenSG/OSGGeoFunctions.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropColors.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropColors.inl > ../include/OpenSG/OSGGeoPropColors.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropNormals.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropNormals.inl > ../include/OpenSG/OSGGeoPropNormals.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropPositions.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropPositions.inl > ../include/OpenSG/OSGGeoPropPositions.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropTexCoords.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropTexCoords.inl > ../include/OpenSG/OSGGeoPropTexCoords.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropertyBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyBase.inl > ../include/OpenSG/OSGGeoPropertyBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPropertyInterface.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPropertyInterface.inl > ../include/OpenSG/OSGGeoPropertyInterface.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeoPumpFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeoPumpFactory.inl > ../include/OpenSG/OSGGeoPumpFactory.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeometry.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometry.inl > ../include/OpenSG/OSGGeometry.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGeometryBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGGeometryBase.inl > ../include/OpenSG/OSGGeometryBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPrimitiveIterator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGPrimitiveIterator.inl > ../include/OpenSG/OSGPrimitiveIterator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTriangleIterator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Geometry/OSGTriangleIterator.inl > ../include/OpenSG/OSGTriangleIterator.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesMisc Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlices.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.h > ../include/OpenSG/OSGSlices.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlicesBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.h > ../include/OpenSG/OSGSlicesBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlicesFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesFields.h > ../include/OpenSG/OSGSlicesFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlices.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Misc/OSGSlices.inl > ../include/OpenSG/OSGSlices.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlicesBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Misc/OSGSlicesBase.inl > ../include/OpenSG/OSGSlicesBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbs Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFatBorderChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.h > ../include/OpenSG/OSGFatBorderChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFatBorderChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.h > ../include/OpenSG/OSGFatBorderChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFatBorderChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkFields.h > ../include/OpenSG/OSGFatBorderChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.h > ../include/OpenSG/OSGSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSurfaceBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.h > ../include/OpenSG/OSGSurfaceBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSurfaceFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceFields.h > ../include/OpenSG/OSGSurfaceFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFatBorderChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunk.inl > ../include/OpenSG/OSGFatBorderChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFatBorderChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGFatBorderChunkBase.inl > ../include/OpenSG/OSGFatBorderChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSurface.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurface.inl > ../include/OpenSG/OSGSurface.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSurfaceBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/OSGSurfaceBase.inl > ../include/OpenSG/OSGSurfaceBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesNurbsInternal Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineBasisFunction.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBSplineBasisFunction.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineBasisFunction.h > ../include/OpenSG/OSGBSplineBasisFunction.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineCurve2D.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBSplineCurve2D.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineCurve2D.h > ../include/OpenSG/OSGBSplineCurve2D.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTensorSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBSplineTensorSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTensorSurface.h > ../include/OpenSG/OSGBSplineTensorSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTrimmedSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBSplineTrimmedSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBSplineTrimmedSurface.h > ../include/OpenSG/OSGBSplineTrimmedSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve2D.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBezierCurve2D.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve2D.h > ../include/OpenSG/OSGBezierCurve2D.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve3D.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBezierCurve3D.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierCurve3D.h > ../include/OpenSG/OSGBezierCurve3D.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierTensorSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBezierTensorSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGBezierTensorSurface.h > ../include/OpenSG/OSGBezierTensorSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPEdge.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDCTPEdge.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPEdge.h > ../include/OpenSG/OSGDCTPEdge.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPFace.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDCTPFace.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPFace.h > ../include/OpenSG/OSGDCTPFace.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPMesh.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDCTPMesh.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPMesh.h > ../include/OpenSG/OSGDCTPMesh.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPVertex.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDCTPVertex.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDCTPVertex.h > ../include/OpenSG/OSGDCTPVertex.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectedGraph.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.h > ../include/OpenSG/OSGDirectedGraph.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGErrorQuadTree.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGErrorQuadTree.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGErrorQuadTree.h > ../include/OpenSG/OSGErrorQuadTree.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGGraphTraverser.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphTraverser.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGGraphTraverser.h > ../include/OpenSG/OSGGraphTraverser.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGNurbsPatchSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNurbsPatchSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGNurbsPatchSurface.h > ../include/OpenSG/OSGNurbsPatchSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGParSpaceTrimmer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParSpaceTrimmer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGParSpaceTrimmer.h > ../include/OpenSG/OSGParSpaceTrimmer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGQuadTreeCreator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQuadTreeCreator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGQuadTreeCreator.h > ../include/OpenSG/OSGQuadTreeCreator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGSimplePolygon.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimplePolygon.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGSimplePolygon.h > ../include/OpenSG/OSGSimplePolygon.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGdctptypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGdctptypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGdctptypes.h > ../include/OpenSG/OSGdctptypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGpredicates.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGpredicates.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGpredicates.h > ../include/OpenSG/OSGpredicates.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGrounding.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGrounding.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGrounding.h > ../include/OpenSG/OSGrounding.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectedGraph.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Nurbs/Internal/OSGDirectedGraph.inl > ../include/OpenSG/OSGDirectedGraph.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesParticles Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticleBSP.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.h > ../include/OpenSG/OSGParticleBSP.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticles.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.h > ../include/OpenSG/OSGParticles.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticlesBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.h > ../include/OpenSG/OSGParticlesBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticlesFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesFields.h > ../include/OpenSG/OSGParticlesFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticleBSP.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticleBSP.inl > ../include/OpenSG/OSGParticleBSP.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticles.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticles.inl > ../include/OpenSG/OSGParticles.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGParticlesBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/Particles/OSGParticlesBase.inl > ../include/OpenSG/OSGParticlesBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresDrawablesVolRen Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBrick.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.h > ../include/OpenSG/OSGBrick.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRAppearance.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.h > ../include/OpenSG/OSGDVRAppearance.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRAppearanceBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.h > ../include/OpenSG/OSGDVRAppearanceBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRAppearanceFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceFields.h > ../include/OpenSG/OSGDVRAppearanceFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.h > ../include/OpenSG/OSGDVRClipGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipGeometryBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.h > ../include/OpenSG/OSGDVRClipGeometryBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipGeometryFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryFields.h > ../include/OpenSG/OSGDVRClipGeometryFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipObjects.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.h > ../include/OpenSG/OSGDVRClipObjects.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipObjectsBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.h > ../include/OpenSG/OSGDVRClipObjectsBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipObjectsFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsFields.h > ../include/OpenSG/OSGDVRClipObjectsFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipper.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipper.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipper.h > ../include/OpenSG/OSGDVRClipper.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRGeometry.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.h > ../include/OpenSG/OSGDVRGeometry.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRGeometryBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.h > ../include/OpenSG/OSGDVRGeometryBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRGeometryFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryFields.h > ../include/OpenSG/OSGDVRGeometryFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoShader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.h > ../include/OpenSG/OSGDVRIsoShader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoShaderBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.h > ../include/OpenSG/OSGDVRIsoShaderBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoShaderFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderFields.h > ../include/OpenSG/OSGDVRIsoShaderFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoSurface.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.h > ../include/OpenSG/OSGDVRIsoSurface.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoSurfaceBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.h > ../include/OpenSG/OSGDVRIsoSurfaceBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoSurfaceFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceFields.h > ../include/OpenSG/OSGDVRIsoSurfaceFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRLookupTable.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.h > ../include/OpenSG/OSGDVRLookupTable.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRLookupTableBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.h > ../include/OpenSG/OSGDVRLookupTableBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRLookupTableFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableFields.h > ../include/OpenSG/OSGDVRLookupTableFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRMtexLUTShader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.h > ../include/OpenSG/OSGDVRMtexLUTShader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRMtexLUTShaderBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.h > ../include/OpenSG/OSGDVRMtexLUTShaderBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRMtexLUTShaderFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderFields.h > ../include/OpenSG/OSGDVRMtexLUTShaderFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRRenderSlice.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRRenderSlice.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRRenderSlice.h > ../include/OpenSG/OSGDVRRenderSlice.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRShader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.h > ../include/OpenSG/OSGDVRShader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRShaderBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.h > ../include/OpenSG/OSGDVRShaderBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRShaderFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderFields.h > ../include/OpenSG/OSGDVRShaderFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleLUTShader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.h > ../include/OpenSG/OSGDVRSimpleLUTShader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleLUTShaderBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.h > ../include/OpenSG/OSGDVRSimpleLUTShaderBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleLUTShaderFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderFields.h > ../include/OpenSG/OSGDVRSimpleLUTShaderFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleShader.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.h > ../include/OpenSG/OSGDVRSimpleShader.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleShaderBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.h > ../include/OpenSG/OSGDVRSimpleShaderBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleShaderFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderFields.h > ../include/OpenSG/OSGDVRSimpleShaderFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSlice.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSlice.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSlice.h > ../include/OpenSG/OSGDVRSlice.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRTriangle.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRTriangle.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRTriangle.h > ../include/OpenSG/OSGDVRTriangle.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVertex.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVertex.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVertex.h > ../include/OpenSG/OSGDVRVertex.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.h > ../include/OpenSG/OSGDVRVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.h > ../include/OpenSG/OSGDVRVolumeBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeFields.h > ../include/OpenSG/OSGDVRVolumeFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeTexture.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.h > ../include/OpenSG/OSGDVRVolumeTexture.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeTextureBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.h > ../include/OpenSG/OSGDVRVolumeTextureBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeTextureFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureFields.h > ../include/OpenSG/OSGDVRVolumeTextureFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGQBit.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQBit.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGQBit.h > ../include/OpenSG/OSGQBit.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGSlicer.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSlicer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGSlicer.h > ../include/OpenSG/OSGSlicer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGTextureManager.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureManager.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGTextureManager.h > ../include/OpenSG/OSGTextureManager.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGVolRenDef.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolRenDef.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGVolRenDef.h > ../include/OpenSG/OSGVolRenDef.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBrick.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGBrick.inl > ../include/OpenSG/OSGBrick.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRAppearance.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearance.inl > ../include/OpenSG/OSGDVRAppearance.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRAppearanceBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRAppearanceBase.inl > ../include/OpenSG/OSGDVRAppearanceBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipGeometry.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometry.inl > ../include/OpenSG/OSGDVRClipGeometry.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipGeometryBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipGeometryBase.inl > ../include/OpenSG/OSGDVRClipGeometryBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipObjects.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjects.inl > ../include/OpenSG/OSGDVRClipObjects.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRClipObjectsBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRClipObjectsBase.inl > ../include/OpenSG/OSGDVRClipObjectsBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRGeometry.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometry.inl > ../include/OpenSG/OSGDVRGeometry.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRGeometryBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRGeometryBase.inl > ../include/OpenSG/OSGDVRGeometryBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoShader.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShader.inl > ../include/OpenSG/OSGDVRIsoShader.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoShaderBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoShaderBase.inl > ../include/OpenSG/OSGDVRIsoShaderBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoSurface.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurface.inl > ../include/OpenSG/OSGDVRIsoSurface.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRIsoSurfaceBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRIsoSurfaceBase.inl > ../include/OpenSG/OSGDVRIsoSurfaceBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRLookupTable.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTable.inl > ../include/OpenSG/OSGDVRLookupTable.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRLookupTableBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRLookupTableBase.inl > ../include/OpenSG/OSGDVRLookupTableBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRMtexLUTShader.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShader.inl > ../include/OpenSG/OSGDVRMtexLUTShader.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRMtexLUTShaderBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRMtexLUTShaderBase.inl > ../include/OpenSG/OSGDVRMtexLUTShaderBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRShader.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShader.inl > ../include/OpenSG/OSGDVRShader.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRShaderBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRShaderBase.inl > ../include/OpenSG/OSGDVRShaderBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleLUTShader.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShader.inl > ../include/OpenSG/OSGDVRSimpleLUTShader.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleLUTShaderBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleLUTShaderBase.inl > ../include/OpenSG/OSGDVRSimpleLUTShaderBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleShader.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShader.inl > ../include/OpenSG/OSGDVRSimpleShader.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRSimpleShaderBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRSimpleShaderBase.inl > ../include/OpenSG/OSGDVRSimpleShaderBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolume.inl > ../include/OpenSG/OSGDVRVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeBase.inl > ../include/OpenSG/OSGDVRVolumeBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeTexture.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTexture.inl > ../include/OpenSG/OSGDVRVolumeTexture.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDVRVolumeTextureBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Drawables/VolRen/OSGDVRVolumeTextureBase.inl > ../include/OpenSG/OSGDVRVolumeTextureBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroup.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroup.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Base/OSGGroup.h > ../include/OpenSG/OSGGroup.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.h > ../include/OpenSG/OSGGroupBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Base/OSGGroupFields.h > ../include/OpenSG/OSGGroupFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroup.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroup.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Base/OSGGroup.inl > ../include/OpenSG/OSGGroup.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Base/OSGGroupBase.inl > ../include/OpenSG/OSGGroupBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsLight Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectionalLight.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.h > ../include/OpenSG/OSGDirectionalLight.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectionalLightBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.h > ../include/OpenSG/OSGDirectionalLightBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectionalLightFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightFields.h > ../include/OpenSG/OSGDirectionalLightFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLight.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLight.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGLight.h > ../include/OpenSG/OSGLight.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGLightBase.h > ../include/OpenSG/OSGLightBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGLightFields.h > ../include/OpenSG/OSGLightFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLight.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointLight.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGPointLight.h > ../include/OpenSG/OSGPointLight.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointLightBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.h > ../include/OpenSG/OSGPointLightBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointLightFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGPointLightFields.h > ../include/OpenSG/OSGPointLightFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpotLight.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.h > ../include/OpenSG/OSGSpotLight.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpotLightBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.h > ../include/OpenSG/OSGSpotLightBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpotLightFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGSpotLightFields.h > ../include/OpenSG/OSGSpotLightFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectionalLight.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLight.inl > ../include/OpenSG/OSGDirectionalLight.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDirectionalLightBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGDirectionalLightBase.inl > ../include/OpenSG/OSGDirectionalLightBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLight.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLight.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGLight.inl > ../include/OpenSG/OSGLight.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGLightBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGLightBase.inl > ../include/OpenSG/OSGLightBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLight.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointLight.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGPointLight.inl > ../include/OpenSG/OSGPointLight.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointLightBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGPointLightBase.inl > ../include/OpenSG/OSGPointLightBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpotLight.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGSpotLight.inl > ../include/OpenSG/OSGSpotLight.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSpotLightBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Light/OSGSpotLightBase.inl > ../include/OpenSG/OSGSpotLightBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemNodeCoresGroupsMisc Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBillboard.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.h > ../include/OpenSG/OSGBillboard.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBillboardBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.h > ../include/OpenSG/OSGBillboardBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBillboardFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGBillboardFields.h > ../include/OpenSG/OSGBillboardFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGComponentTransform.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.h > ../include/OpenSG/OSGComponentTransform.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGComponentTransformBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.h > ../include/OpenSG/OSGComponentTransformBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGComponentTransformFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformFields.h > ../include/OpenSG/OSGComponentTransformFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDistanceLOD.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.h > ../include/OpenSG/OSGDistanceLOD.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDistanceLODBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.h > ../include/OpenSG/OSGDistanceLODBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDistanceLODFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODFields.h > ../include/OpenSG/OSGDistanceLODFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInline.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInline.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInline.h > ../include/OpenSG/OSGInline.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInlineBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.h > ../include/OpenSG/OSGInlineBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInlineFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInlineFields.h > ../include/OpenSG/OSGInlineFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInverseTransform.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.h > ../include/OpenSG/OSGInverseTransform.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInverseTransformBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.h > ../include/OpenSG/OSGInverseTransformBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInverseTransformFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformFields.h > ../include/OpenSG/OSGInverseTransformFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialGroup.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.h > ../include/OpenSG/OSGMaterialGroup.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialGroupBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.h > ../include/OpenSG/OSGMaterialGroupBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialGroupFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupFields.h > ../include/OpenSG/OSGMaterialGroupFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProxyGroup.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.h > ../include/OpenSG/OSGProxyGroup.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProxyGroupBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.h > ../include/OpenSG/OSGProxyGroupBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProxyGroupFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupFields.h > ../include/OpenSG/OSGProxyGroupFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSwitch.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.h > ../include/OpenSG/OSGSwitch.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSwitchBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.h > ../include/OpenSG/OSGSwitchBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSwitchFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGSwitchFields.h > ../include/OpenSG/OSGSwitchFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransform.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransform.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGTransform.h > ../include/OpenSG/OSGTransform.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.h > ../include/OpenSG/OSGTransformBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGTransformFields.h > ../include/OpenSG/OSGTransformFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBillboard.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGBillboard.inl > ../include/OpenSG/OSGBillboard.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBillboardBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGBillboardBase.inl > ../include/OpenSG/OSGBillboardBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGComponentTransform.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransform.inl > ../include/OpenSG/OSGComponentTransform.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGComponentTransformBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGComponentTransformBase.inl > ../include/OpenSG/OSGComponentTransformBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDistanceLOD.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLOD.inl > ../include/OpenSG/OSGDistanceLOD.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDistanceLODBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGDistanceLODBase.inl > ../include/OpenSG/OSGDistanceLODBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInline.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInline.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInline.inl > ../include/OpenSG/OSGInline.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInlineBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInlineBase.inl > ../include/OpenSG/OSGInlineBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInverseTransform.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransform.inl > ../include/OpenSG/OSGInverseTransform.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInverseTransformBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGInverseTransformBase.inl > ../include/OpenSG/OSGInverseTransformBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialGroup.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroup.inl > ../include/OpenSG/OSGMaterialGroup.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialGroupBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGMaterialGroupBase.inl > ../include/OpenSG/OSGMaterialGroupBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProxyGroup.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroup.inl > ../include/OpenSG/OSGProxyGroup.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProxyGroupBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGProxyGroupBase.inl > ../include/OpenSG/OSGProxyGroupBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSwitch.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGSwitch.inl > ../include/OpenSG/OSGSwitch.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSwitchBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGSwitchBase.inl > ../include/OpenSG/OSGSwitchBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransform.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransform.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGTransform.inl > ../include/OpenSG/OSGTransform.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/NodeCores/Groups/Misc/OSGTransformBase.inl > ../include/OpenSG/OSGTransformBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemRenderingBackend Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNode.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawTreeNode.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/RenderingBackend/OSGDrawTreeNode.h > ../include/OpenSG/OSGDrawTreeNode.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawTreeNodeFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.h > ../include/OpenSG/OSGDrawTreeNodeFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNode.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawTreeNode.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/RenderingBackend/OSGDrawTreeNode.inl > ../include/OpenSG/OSGDrawTreeNode.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDrawTreeNodeFactory.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/RenderingBackend/OSGDrawTreeNodeFactory.inl > ../include/OpenSG/OSGDrawTreeNodeFactory.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemState Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBlendChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGBlendChunk.h > ../include/OpenSG/OSGBlendChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBlendChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGBlendChunkBase.h > ../include/OpenSG/OSGBlendChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBlendChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGBlendChunkFields.h > ../include/OpenSG/OSGBlendChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClipPlaneChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGClipPlaneChunk.h > ../include/OpenSG/OSGClipPlaneChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClipPlaneChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGClipPlaneChunkBase.h > ../include/OpenSG/OSGClipPlaneChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClipPlaneChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGClipPlaneChunkFields.h > ../include/OpenSG/OSGClipPlaneChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCubeTextureChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGCubeTextureChunk.h > ../include/OpenSG/OSGCubeTextureChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCubeTextureChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGCubeTextureChunkBase.h > ../include/OpenSG/OSGCubeTextureChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCubeTextureChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGCubeTextureChunkFields.h > ../include/OpenSG/OSGCubeTextureChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFragmentProgramChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGFragmentProgramChunk.h > ../include/OpenSG/OSGFragmentProgramChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFragmentProgramChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGFragmentProgramChunkBase.h > ../include/OpenSG/OSGFragmentProgramChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFragmentProgramChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGFragmentProgramChunkFields.h > ../include/OpenSG/OSGFragmentProgramChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLightChunk.h > ../include/OpenSG/OSGLightChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLightChunkBase.h > ../include/OpenSG/OSGLightChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLightChunkFields.h > ../include/OpenSG/OSGLightChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLineChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLineChunk.h > ../include/OpenSG/OSGLineChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLineChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLineChunkBase.h > ../include/OpenSG/OSGLineChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLineChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLineChunkFields.h > ../include/OpenSG/OSGLineChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGMaterialChunk.h > ../include/OpenSG/OSGMaterialChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGMaterialChunkBase.h > ../include/OpenSG/OSGMaterialChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGMaterialChunkFields.h > ../include/OpenSG/OSGMaterialChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPointChunk.h > ../include/OpenSG/OSGPointChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPointChunkBase.h > ../include/OpenSG/OSGPointChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPointChunkFields.h > ../include/OpenSG/OSGPointChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPolygonChunk.h > ../include/OpenSG/OSGPolygonChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPolygonChunkBase.h > ../include/OpenSG/OSGPolygonChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPolygonChunkFields.h > ../include/OpenSG/OSGPolygonChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProgramChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGProgramChunk.h > ../include/OpenSG/OSGProgramChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProgramChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGProgramChunkBase.h > ../include/OpenSG/OSGProgramChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProgramChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGProgramChunkFields.h > ../include/OpenSG/OSGProgramChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRegisterCombinersChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGRegisterCombinersChunk.h > ../include/OpenSG/OSGRegisterCombinersChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRegisterCombinersChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGRegisterCombinersChunkBase.h > ../include/OpenSG/OSGRegisterCombinersChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRegisterCombinersChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGRegisterCombinersChunkFields.h > ../include/OpenSG/OSGRegisterCombinersChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGState.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGState.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGState.h > ../include/OpenSG/OSGState.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateBase.h > ../include/OpenSG/OSGStateBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateChunk.h > ../include/OpenSG/OSGStateChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateChunkBase.h > ../include/OpenSG/OSGStateChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateChunkFields.h > ../include/OpenSG/OSGStateChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateFields.h > ../include/OpenSG/OSGStateFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTestCubeMaps.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTestCubeMaps.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTestCubeMaps.h > ../include/OpenSG/OSGTestCubeMaps.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTexGenChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTexGenChunk.h > ../include/OpenSG/OSGTexGenChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTexGenChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTexGenChunkBase.h > ../include/OpenSG/OSGTexGenChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTexGenChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTexGenChunkFields.h > ../include/OpenSG/OSGTexGenChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureChunk.h > ../include/OpenSG/OSGTextureChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureChunkBase.h > ../include/OpenSG/OSGTextureChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureChunkFields.h > ../include/OpenSG/OSGTextureChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureTransformChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureTransformChunk.h > ../include/OpenSG/OSGTextureTransformChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureTransformChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureTransformChunkBase.h > ../include/OpenSG/OSGTextureTransformChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureTransformChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureTransformChunkFields.h > ../include/OpenSG/OSGTextureTransformChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTransformChunk.h > ../include/OpenSG/OSGTransformChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTransformChunkBase.h > ../include/OpenSG/OSGTransformChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTransformChunkFields.h > ../include/OpenSG/OSGTransformChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunk.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVertexProgramChunk.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGVertexProgramChunk.h > ../include/OpenSG/OSGVertexProgramChunk.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVertexProgramChunkBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGVertexProgramChunkBase.h > ../include/OpenSG/OSGVertexProgramChunkBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVertexProgramChunkFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGVertexProgramChunkFields.h > ../include/OpenSG/OSGVertexProgramChunkFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBlendChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGBlendChunk.inl > ../include/OpenSG/OSGBlendChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGBlendChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBlendChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGBlendChunkBase.inl > ../include/OpenSG/OSGBlendChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClipPlaneChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGClipPlaneChunk.inl > ../include/OpenSG/OSGClipPlaneChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGClipPlaneChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGClipPlaneChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGClipPlaneChunkBase.inl > ../include/OpenSG/OSGClipPlaneChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCubeTextureChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGCubeTextureChunk.inl > ../include/OpenSG/OSGCubeTextureChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGCubeTextureChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCubeTextureChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGCubeTextureChunkBase.inl > ../include/OpenSG/OSGCubeTextureChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFragmentProgramChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGFragmentProgramChunk.inl > ../include/OpenSG/OSGFragmentProgramChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGFragmentProgramChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFragmentProgramChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGFragmentProgramChunkBase.inl > ../include/OpenSG/OSGFragmentProgramChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLightChunk.inl > ../include/OpenSG/OSGLightChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLightChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLightChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLightChunkBase.inl > ../include/OpenSG/OSGLightChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLineChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLineChunk.inl > ../include/OpenSG/OSGLineChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGLineChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLineChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGLineChunkBase.inl > ../include/OpenSG/OSGLineChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGMaterialChunk.inl > ../include/OpenSG/OSGMaterialChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGMaterialChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMaterialChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGMaterialChunkBase.inl > ../include/OpenSG/OSGMaterialChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPointChunk.inl > ../include/OpenSG/OSGPointChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPointChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPointChunkBase.inl > ../include/OpenSG/OSGPointChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPolygonChunk.inl > ../include/OpenSG/OSGPolygonChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGPolygonChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGPolygonChunkBase.inl > ../include/OpenSG/OSGPolygonChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProgramChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGProgramChunk.inl > ../include/OpenSG/OSGProgramChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGProgramChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProgramChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGProgramChunkBase.inl > ../include/OpenSG/OSGProgramChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRegisterCombinersChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGRegisterCombinersChunk.inl > ../include/OpenSG/OSGRegisterCombinersChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGRegisterCombinersChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGRegisterCombinersChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGRegisterCombinersChunkBase.inl > ../include/OpenSG/OSGRegisterCombinersChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGState.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGState.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGState.inl > ../include/OpenSG/OSGState.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateBase.inl > ../include/OpenSG/OSGStateBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateChunk.inl > ../include/OpenSG/OSGStateChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGStateChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStateChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGStateChunkBase.inl > ../include/OpenSG/OSGStateChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTexGenChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTexGenChunk.inl > ../include/OpenSG/OSGTexGenChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTexGenChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTexGenChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTexGenChunkBase.inl > ../include/OpenSG/OSGTexGenChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureChunk.inl > ../include/OpenSG/OSGTextureChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureChunkBase.inl > ../include/OpenSG/OSGTextureChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureTransformChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureTransformChunk.inl > ../include/OpenSG/OSGTextureTransformChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTextureTransformChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureTransformChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTextureTransformChunkBase.inl > ../include/OpenSG/OSGTextureTransformChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTransformChunk.inl > ../include/OpenSG/OSGTransformChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGTransformChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTransformChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGTransformChunkBase.inl > ../include/OpenSG/OSGTransformChunkBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunk.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVertexProgramChunk.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGVertexProgramChunk.inl > ../include/OpenSG/OSGVertexProgramChunk.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/State/OSGVertexProgramChunkBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVertexProgramChunkBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/State/OSGVertexProgramChunkBase.inl > ../include/OpenSG/OSGVertexProgramChunkBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemStatistics Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsFont.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsFont.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsFont.h > ../include/OpenSG/OSGGraphicStatisticsFont.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsForeground.h > ../include/OpenSG/OSGGraphicStatisticsForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.h > ../include/OpenSG/OSGGraphicStatisticsForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsForegroundFields.h > ../include/OpenSG/OSGGraphicStatisticsForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleStatisticsForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGSimpleStatisticsForeground.h > ../include/OpenSG/OSGSimpleStatisticsForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleStatisticsForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.h > ../include/OpenSG/OSGSimpleStatisticsForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleStatisticsForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGSimpleStatisticsForegroundFields.h > ../include/OpenSG/OSGSimpleStatisticsForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollector.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatCollector.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatCollector.h > ../include/OpenSG/OSGStatCollector.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollectorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatCollectorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatCollectorFields.h > ../include/OpenSG/OSGStatCollectorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElem.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatElem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatElem.h > ../include/OpenSG/OSGStatElem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemDesc.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatElemDesc.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatElemDesc.h > ../include/OpenSG/OSGStatElemDesc.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemTypes.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatElemTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatElemTypes.h > ../include/OpenSG/OSGStatElemTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatIntElem.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatIntElem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatIntElem.h > ../include/OpenSG/OSGStatIntElem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatRealElem.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatRealElem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatRealElem.h > ../include/OpenSG/OSGStatRealElem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatStringElem.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatStringElem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatStringElem.h > ../include/OpenSG/OSGStatStringElem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatTimeElem.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatTimeElem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatTimeElem.h > ../include/OpenSG/OSGStatTimeElem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsDefaultFont.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsDefaultFont.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsDefaultFont.h > ../include/OpenSG/OSGStatisticsDefaultFont.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsForeground.h > ../include/OpenSG/OSGStatisticsForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsForegroundBase.h > ../include/OpenSG/OSGStatisticsForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsForegroundFields.h > ../include/OpenSG/OSGStatisticsForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsForeground.inl > ../include/OpenSG/OSGGraphicStatisticsForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGraphicStatisticsForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGGraphicStatisticsForegroundBase.inl > ../include/OpenSG/OSGGraphicStatisticsForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleStatisticsForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGSimpleStatisticsForeground.inl > ../include/OpenSG/OSGSimpleStatisticsForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleStatisticsForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGSimpleStatisticsForegroundBase.inl > ../include/OpenSG/OSGSimpleStatisticsForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatCollector.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatCollector.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatCollector.inl > ../include/OpenSG/OSGStatCollector.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElem.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatElem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatElem.inl > ../include/OpenSG/OSGStatElem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatElemDesc.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatElemDesc.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatElemDesc.inl > ../include/OpenSG/OSGStatElemDesc.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatIntElem.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatIntElem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatIntElem.inl > ../include/OpenSG/OSGStatIntElem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatRealElem.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatRealElem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatRealElem.inl > ../include/OpenSG/OSGStatRealElem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatStringElem.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatStringElem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatStringElem.inl > ../include/OpenSG/OSGStatStringElem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatTimeElem.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatTimeElem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatTimeElem.inl > ../include/OpenSG/OSGStatTimeElem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsForeground.inl > ../include/OpenSG/OSGStatisticsForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Statistics/OSGStatisticsForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStatisticsForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Statistics/OSGStatisticsForegroundBase.inl > ../include/OpenSG/OSGStatisticsForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceSystemWindow Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGBackground.h > ../include/OpenSG/OSGBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGBackgroundBase.h > ../include/OpenSG/OSGBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGBackgroundFields.h > ../include/OpenSG/OSGBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCamera.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCamera.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCamera.h > ../include/OpenSG/OSGCamera.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraBase.h > ../include/OpenSG/OSGCameraBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraDecorator.h > ../include/OpenSG/OSGCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraDecoratorBase.h > ../include/OpenSG/OSGCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraDecoratorFields.h > ../include/OpenSG/OSGCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraFields.h > ../include/OpenSG/OSGCameraFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewport.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColorBufferViewport.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGColorBufferViewport.h > ../include/OpenSG/OSGColorBufferViewport.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColorBufferViewportBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGColorBufferViewportBase.h > ../include/OpenSG/OSGColorBufferViewportBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColorBufferViewportFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGColorBufferViewportFields.h > ../include/OpenSG/OSGColorBufferViewportFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileGrabForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFileGrabForeground.h > ../include/OpenSG/OSGFileGrabForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileGrabForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFileGrabForegroundBase.h > ../include/OpenSG/OSGFileGrabForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileGrabForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFileGrabForegroundFields.h > ../include/OpenSG/OSGFileGrabForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFlyNavigator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFlyNavigator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFlyNavigator.h > ../include/OpenSG/OSGFlyNavigator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGForeground.h > ../include/OpenSG/OSGForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGForegroundBase.h > ../include/OpenSG/OSGForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGForegroundFields.h > ../include/OpenSG/OSGForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGrabForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGrabForeground.h > ../include/OpenSG/OSGGrabForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGrabForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGrabForegroundBase.h > ../include/OpenSG/OSGGrabForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGrabForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGrabForegroundFields.h > ../include/OpenSG/OSGGrabForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGradientBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGradientBackground.h > ../include/OpenSG/OSGGradientBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGradientBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGradientBackgroundBase.h > ../include/OpenSG/OSGGradientBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGradientBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGradientBackgroundFields.h > ../include/OpenSG/OSGGradientBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageBackground.h > ../include/OpenSG/OSGImageBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageBackgroundBase.h > ../include/OpenSG/OSGImageBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageBackgroundFields.h > ../include/OpenSG/OSGImageBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageForeground.h > ../include/OpenSG/OSGImageForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageForegroundBase.h > ../include/OpenSG/OSGImageForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageForegroundFields.h > ../include/OpenSG/OSGImageForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGLogoData.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLogoData.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGLogoData.h > ../include/OpenSG/OSGLogoData.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCamera.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCamera.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCamera.h > ../include/OpenSG/OSGMatrixCamera.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraBase.h > ../include/OpenSG/OSGMatrixCameraBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraDecorator.h > ../include/OpenSG/OSGMatrixCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraDecoratorBase.h > ../include/OpenSG/OSGMatrixCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraDecoratorFields.h > ../include/OpenSG/OSGMatrixCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraFields.h > ../include/OpenSG/OSGMatrixCameraFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGNavigator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNavigator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGNavigator.h > ../include/OpenSG/OSGNavigator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveBackground.h > ../include/OpenSG/OSGPassiveBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveBackgroundBase.h > ../include/OpenSG/OSGPassiveBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveBackgroundFields.h > ../include/OpenSG/OSGPassiveBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewport.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveViewport.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveViewport.h > ../include/OpenSG/OSGPassiveViewport.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveViewportBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveViewportBase.h > ../include/OpenSG/OSGPassiveViewportBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveViewportFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveViewportFields.h > ../include/OpenSG/OSGPassiveViewportFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveWindow.h > ../include/OpenSG/OSGPassiveWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveWindowBase.h > ../include/OpenSG/OSGPassiveWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveWindowFields.h > ../include/OpenSG/OSGPassiveWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCamera.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPerspectiveCamera.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPerspectiveCamera.h > ../include/OpenSG/OSGPerspectiveCamera.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPerspectiveCameraBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPerspectiveCameraBase.h > ../include/OpenSG/OSGPerspectiveCameraBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPerspectiveCameraFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPerspectiveCameraFields.h > ../include/OpenSG/OSGPerspectiveCameraFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPolygonForeground.h > ../include/OpenSG/OSGPolygonForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPolygonForegroundBase.h > ../include/OpenSG/OSGPolygonForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPolygonForegroundFields.h > ../include/OpenSG/OSGPolygonForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProjectionCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGProjectionCameraDecorator.h > ../include/OpenSG/OSGProjectionCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProjectionCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGProjectionCameraDecoratorBase.h > ../include/OpenSG/OSGProjectionCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProjectionCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGProjectionCameraDecoratorFields.h > ../include/OpenSG/OSGProjectionCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShearedStereoCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGShearedStereoCameraDecorator.h > ../include/OpenSG/OSGShearedStereoCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShearedStereoCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.h > ../include/OpenSG/OSGShearedStereoCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShearedStereoCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGShearedStereoCameraDecoratorFields.h > ../include/OpenSG/OSGShearedStereoCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSimpleSceneManager.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleSceneManager.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSimpleSceneManager.h > ../include/OpenSG/OSGSimpleSceneManager.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSkyBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSkyBackground.h > ../include/OpenSG/OSGSkyBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSkyBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSkyBackgroundBase.h > ../include/OpenSG/OSGSkyBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSkyBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSkyBackgroundFields.h > ../include/OpenSG/OSGSkyBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSolidBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSolidBackground.h > ../include/OpenSG/OSGSolidBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSolidBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSolidBackgroundBase.h > ../include/OpenSG/OSGSolidBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSolidBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSolidBackgroundFields.h > ../include/OpenSG/OSGSolidBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewport.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoBufferViewport.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoBufferViewport.h > ../include/OpenSG/OSGStereoBufferViewport.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoBufferViewportBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoBufferViewportBase.h > ../include/OpenSG/OSGStereoBufferViewportBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoBufferViewportFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoBufferViewportFields.h > ../include/OpenSG/OSGStereoBufferViewportFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoCameraDecorator.h > ../include/OpenSG/OSGStereoCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoCameraDecoratorBase.h > ../include/OpenSG/OSGStereoCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoCameraDecoratorFields.h > ../include/OpenSG/OSGStereoCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureBackground.h > ../include/OpenSG/OSGTextureBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureBackgroundBase.h > ../include/OpenSG/OSGTextureBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureBackgroundFields.h > ../include/OpenSG/OSGTextureBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabBackground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabBackground.h > ../include/OpenSG/OSGTextureGrabBackground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabBackgroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabBackgroundBase.h > ../include/OpenSG/OSGTextureGrabBackgroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabBackgroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabBackgroundFields.h > ../include/OpenSG/OSGTextureGrabBackgroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForeground.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabForeground.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabForeground.h > ../include/OpenSG/OSGTextureGrabForeground.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabForegroundBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabForegroundBase.h > ../include/OpenSG/OSGTextureGrabForegroundBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabForegroundFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabForegroundFields.h > ../include/OpenSG/OSGTextureGrabForegroundFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecorator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileCameraDecorator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTileCameraDecorator.h > ../include/OpenSG/OSGTileCameraDecorator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileCameraDecoratorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTileCameraDecoratorBase.h > ../include/OpenSG/OSGTileCameraDecoratorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileCameraDecoratorFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTileCameraDecoratorFields.h > ../include/OpenSG/OSGTileCameraDecoratorFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackball.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTrackball.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTrackball.h > ../include/OpenSG/OSGTrackball.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTrackballNavigator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTrackballNavigator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTrackballNavigator.h > ../include/OpenSG/OSGTrackballNavigator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewport.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGViewport.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGViewport.h > ../include/OpenSG/OSGViewport.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGViewportBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGViewportBase.h > ../include/OpenSG/OSGViewportBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGViewportFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGViewportFields.h > ../include/OpenSG/OSGViewportFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWalkNavigator.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWalkNavigator.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWalkNavigator.h > ../include/OpenSG/OSGWalkNavigator.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindow.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindow.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWindow.h > ../include/OpenSG/OSGWindow.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowBase.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWindowBase.h > ../include/OpenSG/OSGWindowBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowFields.h

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWindowFields.h > ../include/OpenSG/OSGWindowFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGBackground.inl > ../include/OpenSG/OSGBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGBackgroundBase.inl > ../include/OpenSG/OSGBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCamera.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCamera.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCamera.inl > ../include/OpenSG/OSGCamera.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraBase.inl > ../include/OpenSG/OSGCameraBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraDecorator.inl > ../include/OpenSG/OSGCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGCameraDecoratorBase.inl > ../include/OpenSG/OSGCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewport.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColorBufferViewport.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGColorBufferViewport.inl > ../include/OpenSG/OSGColorBufferViewport.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGColorBufferViewportBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColorBufferViewportBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGColorBufferViewportBase.inl > ../include/OpenSG/OSGColorBufferViewportBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileGrabForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFileGrabForeground.inl > ../include/OpenSG/OSGFileGrabForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGFileGrabForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileGrabForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGFileGrabForegroundBase.inl > ../include/OpenSG/OSGFileGrabForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGForeground.inl > ../include/OpenSG/OSGForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGForegroundBase.inl > ../include/OpenSG/OSGForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGrabForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGrabForeground.inl > ../include/OpenSG/OSGGrabForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGrabForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGrabForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGrabForegroundBase.inl > ../include/OpenSG/OSGGrabForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGradientBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGradientBackground.inl > ../include/OpenSG/OSGGradientBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGGradientBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGradientBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGGradientBackgroundBase.inl > ../include/OpenSG/OSGGradientBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageBackground.inl > ../include/OpenSG/OSGImageBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageBackgroundBase.inl > ../include/OpenSG/OSGImageBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageForeground.inl > ../include/OpenSG/OSGImageForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGImageForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGImageForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGImageForegroundBase.inl > ../include/OpenSG/OSGImageForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCamera.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCamera.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCamera.inl > ../include/OpenSG/OSGMatrixCamera.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraBase.inl > ../include/OpenSG/OSGMatrixCameraBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraDecorator.inl > ../include/OpenSG/OSGMatrixCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGMatrixCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGMatrixCameraDecoratorBase.inl > ../include/OpenSG/OSGMatrixCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveBackground.inl > ../include/OpenSG/OSGPassiveBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveBackgroundBase.inl > ../include/OpenSG/OSGPassiveBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewport.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveViewport.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveViewport.inl > ../include/OpenSG/OSGPassiveViewport.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveViewportBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveViewportBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveViewportBase.inl > ../include/OpenSG/OSGPassiveViewportBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveWindow.inl > ../include/OpenSG/OSGPassiveWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPassiveWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPassiveWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPassiveWindowBase.inl > ../include/OpenSG/OSGPassiveWindowBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCamera.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPerspectiveCamera.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPerspectiveCamera.inl > ../include/OpenSG/OSGPerspectiveCamera.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPerspectiveCameraBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPerspectiveCameraBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPerspectiveCameraBase.inl > ../include/OpenSG/OSGPerspectiveCameraBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPolygonForeground.inl > ../include/OpenSG/OSGPolygonForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGPolygonForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolygonForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGPolygonForegroundBase.inl > ../include/OpenSG/OSGPolygonForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProjectionCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGProjectionCameraDecorator.inl > ../include/OpenSG/OSGProjectionCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGProjectionCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGProjectionCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGProjectionCameraDecoratorBase.inl > ../include/OpenSG/OSGProjectionCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShearedStereoCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGShearedStereoCameraDecorator.inl > ../include/OpenSG/OSGShearedStereoCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShearedStereoCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGShearedStereoCameraDecoratorBase.inl > ../include/OpenSG/OSGShearedStereoCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSimpleSceneManager.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSimpleSceneManager.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSimpleSceneManager.inl > ../include/OpenSG/OSGSimpleSceneManager.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSkyBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSkyBackground.inl > ../include/OpenSG/OSGSkyBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSkyBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSkyBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSkyBackgroundBase.inl > ../include/OpenSG/OSGSkyBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSolidBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSolidBackground.inl > ../include/OpenSG/OSGSolidBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGSolidBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSolidBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGSolidBackgroundBase.inl > ../include/OpenSG/OSGSolidBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewport.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoBufferViewport.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoBufferViewport.inl > ../include/OpenSG/OSGStereoBufferViewport.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoBufferViewportBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoBufferViewportBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoBufferViewportBase.inl > ../include/OpenSG/OSGStereoBufferViewportBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoCameraDecorator.inl > ../include/OpenSG/OSGStereoCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGStereoCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStereoCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGStereoCameraDecoratorBase.inl > ../include/OpenSG/OSGStereoCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureBackground.inl > ../include/OpenSG/OSGTextureBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureBackgroundBase.inl > ../include/OpenSG/OSGTextureBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabBackground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabBackground.inl > ../include/OpenSG/OSGTextureGrabBackground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabBackgroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabBackgroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabBackgroundBase.inl > ../include/OpenSG/OSGTextureGrabBackgroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForeground.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabForeground.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabForeground.inl > ../include/OpenSG/OSGTextureGrabForeground.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTextureGrabForegroundBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTextureGrabForegroundBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTextureGrabForegroundBase.inl > ../include/OpenSG/OSGTextureGrabForegroundBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecorator.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileCameraDecorator.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTileCameraDecorator.inl > ../include/OpenSG/OSGTileCameraDecorator.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGTileCameraDecoratorBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTileCameraDecoratorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGTileCameraDecoratorBase.inl > ../include/OpenSG/OSGTileCameraDecoratorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewport.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGViewport.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGViewport.inl > ../include/OpenSG/OSGViewport.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGViewportBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGViewportBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGViewportBase.inl > ../include/OpenSG/OSGViewportBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindow.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindow.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWindow.inl > ../include/OpenSG/OSGWindow.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/System/Window/OSGWindowBase.inl

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGWindowBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/System/Window/OSGWindowBase.inl > ../include/OpenSG/OSGWindowBase.inl

# End Custom Build

!ENDIF

# End Source File

# End Group

# End Group

# End Target
# End Project
