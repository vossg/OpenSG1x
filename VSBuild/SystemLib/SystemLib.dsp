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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe1125 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=501  -DOSG_SUPPORT_NO_GEO_INTERFACE=1 -DOSG_BUILD_DLL -DOSG_NEW_DLLS -Qvc6 -GX -Gi- -Qansi -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILESYSTEMLIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../Action/DrawAction  -I../../Action/IntersectAction  -I../../Action/RenderAction  -I../../Action  -I../../Base  -I../../BaseLib  -I../../Experimental/BINWriter  -I../../Experimental/BINWriter  -I../../Experimental/Gerrit/Functors  -I../../Experimental/OSGLoader  -I../../Experimental/OSGWriter  -I../../Experimental/StringConversionState  -I../../Experimental/Text  -I../../Experimental/VRMLWriter  -I../../Field  -I../../FieldContainer  -I../../Image  -I../../Loader/OBJ  -I../../Loader/OFF  -I../../Loader/OSG  -I../../Loader/RAW  -I../../Loader/ScanParseSkel  -I../../Loader/WRL  -I../../Loader  -I../../Log  -I../../Material  -I../../MultiThreading  -I../../Nodes/Geometry  -I../../Nodes/Light  -I../../Nodes/Misc  -I../../Nodes/Particles  -I../../RenderingBackend  -I../../State  -I../../Statistics  -I../../Window  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib tif32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGSystemD.dll
      

!ENDIF 

# Begin Target

# Name "SystemLib - Win32 Release"
# Name "SystemLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "Action h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/OSGAction.h
# End Source File


# Begin Source File
SOURCE=../../Action/OSGDrawActionBase.h
# End Source File

# End Group
# Begin Group "ActionDrawAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/DrawAction/OSGDrawAction.h
# End Source File

# End Group
# Begin Group "ActionIntersectAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/IntersectAction/OSGIntersectAction.h
# End Source File

# End Group
# Begin Group "ActionRenderAction h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/RenderAction/OSGRenderAction.h
# End Source File

# End Group
# Begin Group "ExperimentalBINLoader h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/BINLoader/OSGBINLoader.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/BINLoader/OSGBINSceneFileType.h
# End Source File

# End Group
# Begin Group "ExperimentalBINWriter h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/BINWriter/OSGBINWriter.h
# End Source File

# End Group
# Begin Group "ExperimentalOSGLoader h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/OSGLoader/OSGLoader.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/OSGLoader/OSGOSGSceneFileType.h
# End Source File

# End Group
# Begin Group "ExperimentalOSGWriter h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/OSGWriter/OSGOSGWriter.h
# End Source File

# End Group
# Begin Group "ExperimentalStringConversionState h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGIndenter.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStandardStringConversionState.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStringConversionStateBase.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStringTokenizer.h
# End Source File

# End Group
# Begin Group "ExperimentalText h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/Text/OSGFont.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontFactory.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontGlyphContour.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontStyleFactory.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFont.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontGlyphContour.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTVectorFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFont.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFontStyle.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFGlyphInfo.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFImageFontGlyph.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTesselationHandler.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGText.h
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGVectorFontGlyph.h
# End Source File

# End Group
# Begin Group "ExperimentalVRMLWriter h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/VRMLWriter/OSGVRMLWriteAction.h
# End Source File

# End Group
# Begin Group "FieldContainer h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../FieldContainer/OSGAttachment.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainer.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainerFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainerFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentMapFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentMapFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainer.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerFactory.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerProperties.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerPtrForward.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldDescription.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFAttachmentMap.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFFieldContainerTypes.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFNodeCorePtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGMFNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNode.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeCore.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeCoreFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeCoreFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeFields.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFAttachmentContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFAttachmentMap.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFAttachmentPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFFieldContainerPtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFFieldContainerTypes.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFNodeCorePtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSFNodePtr.h
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGSystemDef.h
# End Source File

# End Group
# Begin Group "Image h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Image/OSGDATImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGGIFImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImage.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImageFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImageFileHandler.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImagePFields.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGJPGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGMFImageTypes.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGMNGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGMTDImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGPNGImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGPNMImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGSFImageTypes.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGSGIImageFileType.h
# End Source File


# Begin Source File
SOURCE=../../Image/OSGTIFImageFileType.h
# End Source File

# End Group
# Begin Group "Loader h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OSGSceneFileHandler.h
# End Source File


# Begin Source File
SOURCE=../../Loader/OSGSceneFileType.h
# End Source File

# End Group
# Begin Group "LoaderOBJ h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OBJ/OSGOBJSceneFileType.h
# End Source File

# End Group
# Begin Group "LoaderOFF h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OFF/OSGOFFSceneFileType.h
# End Source File

# End Group
# Begin Group "LoaderOSG h"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderRAW h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/RAW/OSGRAWSceneFileType.h
# End Source File

# End Group
# Begin Group "LoaderScanParseSkel h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/ScanParseSkel/OSGScanParseFieldTypeMapper.h
# End Source File


# Begin Source File
SOURCE=../../Loader/ScanParseSkel/OSGScanParseSkel.h
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.tab.h
# End Source File

# End Group
# Begin Group "LoaderWRL h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLFile.h
# End Source File


# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLNodeDescs.h
# End Source File


# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLNodeFactory.h
# End Source File


# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLSceneFileType.h
# End Source File

# End Group
# Begin Group "Material h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Material/OSGChunkMaterial.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGChunkMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGChunkMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterial.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterial.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterialFields.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterial.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterialBase.h
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterialFields.h
# End Source File

# End Group
# Begin Group "MultiThreading h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../MultiThreading/OSGChangeList.h
# End Source File


# Begin Source File
SOURCE=../../MultiThreading/OSGThread.h
# End Source File

# End Group
# Begin Group "NodesGeometry h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Geometry/OSGFaceIterator.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoColorsFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoFunctions.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoIndicesFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoNormalsFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPLengthsFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPTypesFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPositionsFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropColors.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropIndices.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropNormals.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPLengths.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPTypes.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPositions.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPtrs.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropTexCoords.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoProperty.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropertyBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropertyInterface.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPumpFactory.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoTexCoordsFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometry.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometryBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometryFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGNodeGraph.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGPrimitiveIterator.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGSimpleGeometry.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGTriangleIterator.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGVolumeDraw.h
# End Source File

# End Group
# Begin Group "NodesLight h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLight.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLightBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLightFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBaseBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBaseFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLight.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLightBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLightFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLight.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLightBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLightFields.h
# End Source File

# End Group
# Begin Group "NodesMisc h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboard.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboardBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboardFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransform.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransformBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransformFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLOD.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLODBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLODFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroup.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroupBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroupFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInline.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInlineBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInlineFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroup.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroupBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroupFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitch.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitchBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitchFields.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransform.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransformBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransformFields.h
# End Source File

# End Group
# Begin Group "NodesParticles h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticleBSP.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticles.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticlesBase.h
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticlesFields.h
# End Source File

# End Group
# Begin Group "RenderingBackend h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../RenderingBackend/OSGDrawTreeNode.h
# End Source File

# End Group
# Begin Group "State h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../State/OSGBlendChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGBlendChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGBlendChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGState.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunkFields.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunk.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunkBase.h
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunkFields.h
# End Source File

# End Group
# Begin Group "Statistics h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Statistics/OSGStatCollector.h
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElem.h
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElemDesc.h
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatIntElem.h
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatRealElem.h
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatTimeElem.h
# End Source File

# End Group
# Begin Group "Window h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Window/OSGBackground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCamera.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForeground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFlyNavigator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForeground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForeground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForeground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForegroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForegroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGLogoData.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCamera.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGNavigator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewport.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindow.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindowFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCamera.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCameraBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCameraFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSimpleSceneManager.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackground.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackgroundBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackgroundFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewport.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecorator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecoratorBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecoratorFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTrackball.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTrackballNavigator.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewport.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewportBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewportFields.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindow.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindowBase.h
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindowFields.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "Action inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/OSGAction.inl
# End Source File


# Begin Source File
SOURCE=../../Action/OSGDrawActionBase.inl
# End Source File

# End Group
# Begin Group "ActionDrawAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/DrawAction/OSGDrawAction.inl
# End Source File

# End Group
# Begin Group "ActionIntersectAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/IntersectAction/OSGIntersectAction.inl
# End Source File

# End Group
# Begin Group "ActionRenderAction inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/RenderAction/OSGRenderAction.inl
# End Source File

# End Group
# Begin Group "ExperimentalBINLoader inl"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalBINWriter inl"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalOSGLoader inl"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalOSGWriter inl"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalStringConversionState inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGIndenter.inl
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStandardStringConversionState.inl
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStringTokenizer.inl
# End Source File

# End Group
# Begin Group "ExperimentalText inl"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalVRMLWriter inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/VRMLWriter/OSGVRMLWriteAction.inl
# End Source File

# End Group
# Begin Group "FieldContainer inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../FieldContainer/OSGAttachment.inl
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainer.inl
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainer.inl
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerPtr.inl
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNode.inl
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeCore.inl
# End Source File

# End Group
# Begin Group "Image inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Image/OSGImage.inl
# End Source File

# End Group
# Begin Group "Loader inl"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOBJ inl"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOFF inl"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOSG inl"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderRAW inl"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderScanParseSkel inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/ScanParseSkel/OSGScanParseFieldTypeMapper.inl
# End Source File

# End Group
# Begin Group "LoaderWRL inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLNodeFactory.inl
# End Source File

# End Group
# Begin Group "Material inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Material/OSGChunkMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGChunkMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterialBase.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterial.inl
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterialBase.inl
# End Source File

# End Group
# Begin Group "MultiThreading inl"
# PROP Default_Filter ""
# End Group
# Begin Group "NodesGeometry inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Geometry/OSGFaceIterator.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropColors.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPositions.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropTexCoords.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropertyBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropertyInterface.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPumpFactory.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometry.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometryBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGPrimitiveIterator.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGTriangleIterator.inl
# End Source File

# End Group
# Begin Group "NodesLight inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLight.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBaseBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLight.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLightBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLight.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLightBase.inl
# End Source File

# End Group
# Begin Group "NodesMisc inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboard.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboardBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransform.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransformBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLOD.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLODBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroup.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroupBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInline.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInlineBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroup.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroupBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitch.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitchBase.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransform.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransformBase.inl
# End Source File

# End Group
# Begin Group "NodesParticles inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticleBSP.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticles.inl
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticlesBase.inl
# End Source File

# End Group
# Begin Group "RenderingBackend inl"
# PROP Default_Filter ""
# End Group
# Begin Group "State inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../State/OSGBlendChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGBlendChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGState.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunkBase.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunk.inl
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunkBase.inl
# End Source File

# End Group
# Begin Group "Statistics inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Statistics/OSGStatCollector.inl
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElem.inl
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElemDesc.inl
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatIntElem.inl
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatRealElem.inl
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatTimeElem.inl
# End Source File

# End Group
# Begin Group "Window inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Window/OSGBackground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCamera.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForeground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForeground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForeground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForeground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForegroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCamera.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewport.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindow.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindowBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCamera.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCameraBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSimpleSceneManager.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackground.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackgroundBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewport.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecorator.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecoratorBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewport.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewportBase.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindow.inl
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindowBase.inl
# End Source File

# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "Action cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/OSGAction.cpp
# End Source File


# Begin Source File
SOURCE=../../Action/OSGDrawActionBase.cpp
# End Source File

# End Group
# Begin Group "ActionDrawAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/DrawAction/OSGDrawAction.cpp
# End Source File

# End Group
# Begin Group "ActionIntersectAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/IntersectAction/OSGIntersectAction.cpp
# End Source File

# End Group
# Begin Group "ActionRenderAction cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Action/RenderAction/OSGRenderAction.cpp
# End Source File

# End Group
# Begin Group "ExperimentalBINLoader cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/BINLoader/OSGBINLoader.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/BINLoader/OSGBINSceneFileType.cpp
# End Source File

# End Group
# Begin Group "ExperimentalBINWriter cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/BINWriter/OSGBINWriter.cpp
# End Source File

# End Group
# Begin Group "ExperimentalOSGLoader cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/OSGLoader/OSGLoader.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/OSGLoader/OSGOSGSceneFileType.cpp
# End Source File

# End Group
# Begin Group "ExperimentalOSGWriter cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/OSGWriter/OSGOSGWriter.cpp
# End Source File

# End Group
# Begin Group "ExperimentalStringConversionState cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGIndenter.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStandardStringConversionState.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/StringConversionState/OSGStringTokenizer.cpp
# End Source File

# End Group
# Begin Group "ExperimentalText cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/Text/OSGFont.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontGlyphContour.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGFontStyleFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFont.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontGlyphContour.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTTVectorFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFont.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFFontStyle.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFGlyphInfo.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTXFImageFontGlyph.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGTesselationHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGText.cpp
# End Source File


# Begin Source File
SOURCE=../../Experimental/Text/OSGVectorFontGlyph.cpp
# End Source File

# End Group
# Begin Group "ExperimentalVRMLWriter cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Experimental/VRMLWriter/OSGVRMLWriteAction.cpp
# End Source File

# End Group
# Begin Group "FieldContainer cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../FieldContainer/OSGAttachment.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainer.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentContainerPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGAttachmentPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGContainerTypeInst.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainer.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerPtr.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldContainerType.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGFieldDescription.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNode.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodeCore.cpp
# End Source File


# Begin Source File
SOURCE=../../FieldContainer/OSGNodePtr.cpp
# End Source File

# End Group
# Begin Group "Image cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Image/OSGDATImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGGIFImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImage.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImageFileHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGJPGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGMNGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGMTDImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGPNGImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGPNMImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGSGIImageFileType.cpp
# End Source File


# Begin Source File
SOURCE=../../Image/OSGTIFImageFileType.cpp
# End Source File

# End Group
# Begin Group "Loader cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OSGSceneFileHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../Loader/OSGSceneFileType.cpp
# End Source File

# End Group
# Begin Group "LoaderOBJ cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OBJ/OSGOBJSceneFileType.cpp
# End Source File

# End Group
# Begin Group "LoaderOFF cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/OFF/OSGOFFSceneFileType.cpp
# End Source File

# End Group
# Begin Group "LoaderOSG cpp"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderRAW cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/RAW/OSGRAWSceneFileType.cpp
# End Source File

# End Group
# Begin Group "LoaderScanParseSkel cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/ScanParseSkel/OSGScanParseSkel.cpp
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.tab.cpp
# End Source File


# Begin Source File
SOURCE=OSGScanParseSkel.lex.cpp
# End Source File

# End Group
# Begin Group "LoaderWRL cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLFile.cpp
# End Source File


# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLNodeDescs.cpp
# End Source File


# Begin Source File
SOURCE=../../Loader/WRL/OSGVRMLSceneFileType.cpp
# End Source File

# End Group
# Begin Group "Material cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Material/OSGChunkMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGChunkMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleMaterialBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterial.cpp
# End Source File


# Begin Source File
SOURCE=../../Material/OSGSimpleTexturedMaterialBase.cpp
# End Source File

# End Group
# Begin Group "MultiThreading cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../MultiThreading/OSGChangeList.cpp
# End Source File


# Begin Source File
SOURCE=../../MultiThreading/OSGThread.cpp
# End Source File

# End Group
# Begin Group "NodesGeometry cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Geometry/OSGFaceIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoFunctions.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropColors.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropFields.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropIndices.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropNormals.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPLengths.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPTypes.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropPositions.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropTexCoords.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPropertyBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeoPumpFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGGeometryBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGNodeGraph.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGPrimitiveIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGSimpleGeometry.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGTriangleIterator.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Geometry/OSGVolumeDraw.cpp
# End Source File

# End Group
# Begin Group "NodesLight cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLight.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGDirectionalLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGLightBaseBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLight.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGPointLightBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLight.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Light/OSGSpotLightBase.cpp
# End Source File

# End Group
# Begin Group "NodesMisc cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboard.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGBillboardBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransform.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGComponentTransformBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLOD.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGDistanceLODBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGGroupBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInline.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGInlineBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroup.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGMaterialGroupBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitch.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGSwitchBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransform.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Misc/OSGTransformBase.cpp
# End Source File

# End Group
# Begin Group "NodesParticles cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticleBSP.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticles.cpp
# End Source File


# Begin Source File
SOURCE=../../Nodes/Particles/OSGParticlesBase.cpp
# End Source File

# End Group
# Begin Group "RenderingBackend cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../RenderingBackend/OSGDrawTreeNode.cpp
# End Source File

# End Group
# Begin Group "State cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../State/OSGBlendChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGBlendChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGLightChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGLineChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGMaterialChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGPolygonChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGState.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGStateChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTextureTransformChunkBase.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunk.cpp
# End Source File


# Begin Source File
SOURCE=../../State/OSGTransformChunkBase.cpp
# End Source File

# End Group
# Begin Group "Statistics cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Statistics/OSGStatCollector.cpp
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElem.cpp
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatElemDesc.cpp
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatIntElem.cpp
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatRealElem.cpp
# End Source File


# Begin Source File
SOURCE=../../Statistics/OSGStatTimeElem.cpp
# End Source File

# End Group
# Begin Group "Window cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Window/OSGBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFileGrabForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGFlyNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGrabForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGGradientBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForeground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGImageForegroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGLogoData.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGMatrixCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPassiveWindowBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCamera.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGPerspectiveCameraBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGProjectionCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGShearedStereoCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSimpleSceneManager.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSkyBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackground.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGSolidBackgroundBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoBufferViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGStereoCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecorator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTileCameraDecoratorBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTrackball.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGTrackballNavigator.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewport.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGViewportBase.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindow.cpp
# End Source File


# Begin Source File
SOURCE=../../Window/OSGWindowBase.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "Action ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ActionDrawAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ActionIntersectAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ActionRenderAction ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalBINLoader ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalBINWriter ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalOSGLoader ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalOSGWriter ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalStringConversionState ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalText ly"
# PROP Default_Filter ""
# End Group
# Begin Group "ExperimentalVRMLWriter ly"
# PROP Default_Filter ""
# End Group
# Begin Group "FieldContainer ly"
# PROP Default_Filter ""
# End Group
# Begin Group "Image ly"
# PROP Default_Filter ""
# End Group
# Begin Group "Loader ly"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOBJ ly"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOFF ly"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderOSG ly"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderRAW ly"
# PROP Default_Filter ""
# End Group
# Begin Group "LoaderScanParseSkel ly"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../Loader/ScanParseSkel/OSGScanParseSkel.y

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build
InputPath=../../Loader/ScanParseSkel/OSGScanParseSkel.y

BuildCmds= \
	bison.exe -d -v -pOSGScanParseSkel_  -bOSGScanParseSkel_ ../../Loader/ScanParseSkel/OSGScanParseSkel.y \
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
SOURCE=../../Loader/ScanParseSkel/OSGScanParseSkel.l

!IF  "$(CFG)" == "SystemLib - Win32 Release"

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

# Begin Custom Build
InputPath=../../Loader/ScanParseSkel/OSGScanParseSkel.l

BuildCmds= \
	flex.exe -l -POSGScanParseSkel_ ../../Loader/ScanParseSkel/OSGScanParseSkel.l \
	move lex.OSGScanParseSkel_.c OSGScanParseSkel.lex.cpp \

"OSGScanParseSkel.lex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "LoaderWRL ly"
# PROP Default_Filter ""
# End Group
# Begin Group "Material ly"
# PROP Default_Filter ""
# End Group
# Begin Group "MultiThreading ly"
# PROP Default_Filter ""
# End Group
# Begin Group "NodesGeometry ly"
# PROP Default_Filter ""
# End Group
# Begin Group "NodesLight ly"
# PROP Default_Filter ""
# End Group
# Begin Group "NodesMisc ly"
# PROP Default_Filter ""
# End Group
# Begin Group "NodesParticles ly"
# PROP Default_Filter ""
# End Group
# Begin Group "RenderingBackend ly"
# PROP Default_Filter ""
# End Group
# Begin Group "State ly"
# PROP Default_Filter ""
# End Group
# Begin Group "Statistics ly"
# PROP Default_Filter ""
# End Group
# Begin Group "Window ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# Begin Source File
SOURCE=lib.dbg.def
# End Source File


# End Group

# End Target
# End Project
