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
# ADD CPP /MD /W3 /GR /GX /O2 /I "." /I ".." /I "..\..\..\Base" /I "..\..\..\Log" /I "..\..\..\FieldContainer" /I "..\..\..\Multithreading" /I "..\..\..\Field" /I "..\..\..\Action" /I "..\..\..\Action\DrawAction" /I "..\..\..\Action\IntersectAction" /I "..\..\..\Nodes\Misc" /I "..\..\..\Nodes\Light" /I "..\..\..\Nodes\Geometry" /I "..\..\..\Material" /I "..\..\..\State" /I "..\..\..\Window" /I "..\..\..\Image" /I "..\..\..\Loader" /I "..\..\..\Loader\Fhs" /I "..\..\..\Experimental\ScanParseSkel" /I "..\..\..\Experimental\OSGLoader" /I "..\..\..\Experimental\VRMLLoader" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x0400 /D WIN32_WINDOWS=0x0410 /D "OSG_BUILD_DLL" /D "_OSG_HAVE_CONFIGURED_H_" /D "OSG_NOFUNCTORS" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "SystemLib - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".." /I "..\..\..\Base" /I "..\..\..\Log" /I "..\..\..\FieldContainer" /I "..\..\..\Multithreading" /I "..\..\..\Field" /I "..\..\..\Action" /I "..\..\..\Action\DrawAction" /I "..\..\..\Action\IntersectAction" /I "..\..\..\Nodes\Misc" /I "..\..\..\Nodes\Light" /I "..\..\..\Nodes\Geometry" /I "..\..\..\Material" /I "..\..\..\State" /I "..\..\..\Window" /I "..\..\..\Image" /I "..\..\..\Loader" /I "..\..\..\Loader\Fhs" /I "..\..\..\Experimental\ScanParseSkel" /I "..\..\..\Experimental\OSGLoader" /I "..\..\..\Experimental\VRMLLoader" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x0400 /D WIN32_WINDOWS=0x0410 /D "OSG_BUILD_DLL" /D "_OSG_HAVE_CONFIGURED_H_" /D "OSG_NOFUNCTORS" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SystemLib - Win32 Release"
# Name "SystemLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "FieldContainer_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGAttachment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGContainerTypeInst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerPtr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldDescription.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNodeCore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNodePtr.cpp
# End Source File
# End Group
# Begin Group "Multithreading_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\MultiThreading\OSGChangeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\MultiThreading\OSGThread.cpp
# End Source File
# End Group
# Begin Group "Action_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Action\OSGAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\DrawAction\OSGDrawAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\IntersectAction\OSGIntersectAction.cpp
# End Source File
# End Group
# Begin Group "Nodes_cpp"

# PROP Default_Filter ""
# Begin Group "Light_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLightBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBaseBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLightBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLightBase.cpp
# End Source File
# End Group
# Begin Group "Misc_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroupBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroupBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransformBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransformBase.cpp
# End Source File
# End Group
# Begin Group "Geometry_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGFaceIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometryBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropColors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropertyBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropFields.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropIndices.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropNormals.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropPositions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropTexCoords.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPumpFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGPrimitiveIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGSimpleGeometry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGTriangleIterator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGVolumeDraw.cpp
# End Source File
# End Group
# End Group
# Begin Group "State_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunkBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunkBase.cpp
# End Source File
# End Group
# Begin Group "Image_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Image\OSGImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImageFileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImageFileType.cpp
# End Source File
# End Group
# Begin Group "Window_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Window\OSGBackground.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGBackgroundBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecorator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecoratorBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackground.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackgroundBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackground.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackgroundBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCameraBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackground.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackgroundBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecorator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecoratorBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTrackball.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewportBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindowBase.cpp
# End Source File
# End Group
# Begin Group "Material_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterialBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterialBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterialBase.cpp
# End Source File
# End Group
# Begin Group "Loader_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\..\Loader\OSGRAWSceneFileType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\OSGSceneFileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\OSGSceneFileType.cpp
# End Source File
# End Group
# Begin Group "Fhs_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\fhs.lex.cpp
# End Source File
# Begin Source File

SOURCE=.\fhs.tab.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\Fhs\OSGFhsFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\Fhs\OSGFhsSceneFileType.cpp
# End Source File
# End Group
# Begin Group "ScanParseSkel_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\ScanParseSkel\OSGScanParseSkel.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGScanParseSkel.lex.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGScanParseSkel.tab.cpp
# End Source File
# End Group
# Begin Group "OSGLoader_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\OSGLoader\OSGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\OSGLoader\OSGOSGSceneFileType.cpp
# End Source File
# End Group
# Begin Group "VRMLLoader_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLNodeDescs.cpp
# End Source File
# End Group
# Begin Group "VRMLWriter_cpp"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\..\VRMLWriter\OSGVRMLWriteAction.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\libSystem.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "FieldContainer_h"

# PROP Default_Filter "hpp"
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGAttachment.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGAttachmentMapFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGContainerFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerProperties.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerPtr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldDescription.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGMFFieldContainerTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNodeCore.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNodePtr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGSFFieldContainerTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGSystemDef.h
# End Source File
# End Group
# Begin Group "Multithreading_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\MultiThreading\OSGChangeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\MultiThreading\OSGThread.h
# End Source File
# End Group
# Begin Group "Action_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Action\OSGAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\DrawAction\OSGDrawAction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\IntersectAction\OSGIntersectAction.h
# End Source File
# End Group
# Begin Group "Nodes_h"

# PROP Default_Filter "h"
# Begin Group "Light_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLight.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLightBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLightFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBaseBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBaseFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLight.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLightBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLightFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLight.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLightBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLightFields.h
# End Source File
# End Group
# Begin Group "Misc_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroupBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroupFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroupBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroupFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransformBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransformFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransformBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransformFields.h
# End Source File
# End Group
# Begin Group "Geometry_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGFaceIterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoColorsFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoFunctions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoIndicesFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometryBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometryFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoNormalsFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPLengthsFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPositionsFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropColors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoProperty.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropertyBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropIndices.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropNormals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropPositions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropPtrs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropTexCoords.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPTypesFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPumpFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGPrimitiveIterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGSimpleGeometry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGTriangleIterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGVolumeDraw.h
# End Source File
# End Group
# End Group
# Begin Group "State_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunkFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunk.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunkBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunkFields.h
# End Source File
# End Group
# Begin Group "Image_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Image\OSGImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImageFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImageFileHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImageFileType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGImagePFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGMFImageTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Image\OSGSFImageTypes.h
# End Source File
# End Group
# Begin Group "Window_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Window\OSGBackground.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGBackgroundBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGBackgroundFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCamera.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecorator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecoratorBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecoratorFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackground.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackgroundBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackgroundFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackground.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackgroundBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCamera.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCameraBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCameraFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackground.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackgroundBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackgroundFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecorator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecoratorBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecoratorFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTrackball.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewportBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindowBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindowFields.h
# End Source File
# End Group
# Begin Group "Material_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterial.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterialBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterialFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterial.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterialBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterialFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterial.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterialBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterialFields.h
# End Source File
# End Group
# Begin Group "Loader_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\..\Loader\OSGRAWSceneFileType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\OSGSceneFileHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\OSGSceneFileType.h
# End Source File
# End Group
# Begin Group "Fhs_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\fhs.tab.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\Fhs\OSGFhsComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\Fhs\OSGFhsFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Loader\Fhs\OSGFhsSceneFileType.h
# End Source File
# End Group
# Begin Group "ScanParseSkel_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\ScanParseSkel\OSGScanParseFieldTypeMapper.h
# End Source File
# Begin Source File

SOURCE=..\..\ScanParseSkel\OSGScanParseSkel.h
# End Source File
# Begin Source File

SOURCE=.\OSGScanParseSkel.tab.h
# End Source File
# End Group
# Begin Group "OSGLoader_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\OSGLoader\OSGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\OSGLoader\OSGOSGSceneFileType.h
# End Source File
# End Group
# Begin Group "VRMLLoader_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLFile.h
# End Source File
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLNodeDescs.h
# End Source File
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLNodeFactory.h
# End Source File
# End Group
# Begin Group "VRMLWriter_h"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\..\VRMLWriter\OSGVRMLWriteAction.h
# End Source File
# End Group
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
# Begin Group "FieldContainer_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGAttachment.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainer.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGFieldContainerPtr.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNode.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\FieldContainer\OSGNodeCore.inl
# End Source File
# End Group
# Begin Group "Field_inl"

# PROP Default_Filter "inl"
# End Group
# Begin Group "Action_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Action\OSGAction.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\DrawAction\OSGDrawAction.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Action\IntersectAction\OSGIntersectAction.inl
# End Source File
# End Group
# Begin Group "Nodes_inl"

# PROP Default_Filter "inl"
# Begin Group "Light_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLight.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGDirectionalLightBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGLightBaseBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLight.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGPointLightBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLight.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Light\OSGSpotLightBase.inl
# End Source File
# End Group
# Begin Group "Misc_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroup.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGGroupBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroup.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGMaterialGroupBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransform.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGTransformBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransform.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Misc\OSGComponentTransformBase.inl
# End Source File
# End Group
# Begin Group "Geometry_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGFaceIterator.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometry.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeometryBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropColors.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropertyBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPropTexCoords.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGGeoPumpFactory.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGPrimitiveIterator.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Nodes\Geometry\OSGTriangleIterator.inl
# End Source File
# End Group
# End Group
# Begin Group "State_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGBlendChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGLightChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGMaterialChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGPolygonChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGState.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGStateChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTextureChunkBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\State\OSGTransformChunkBase.inl
# End Source File
# End Group
# Begin Group "Image_inl"

# PROP Default_Filter "inl"
# End Group
# Begin Group "Window_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Window\OSGBackground.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGBackgroundBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCamera.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecorator.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGCameraDecoratorBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackground.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGDynamicBackgroundBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackground.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGGradientBackgroundBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCamera.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGPerspectiveCameraBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackground.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGSolidBackgroundBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecorator.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGTileCameraDecoratorBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewport.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGViewportBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindow.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Window\OSGWindowBase.inl
# End Source File
# End Group
# Begin Group "Material_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterial.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGChunkMaterialBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterial.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGMaterialBase.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterial.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Material\OSGSimpleMaterialBase.inl
# End Source File
# End Group
# Begin Group "Loader_inl"

# PROP Default_Filter "inl"
# End Group
# Begin Group "Fhs_inl"

# PROP Default_Filter "inl"
# End Group
# Begin Group "ScanParserSkel_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\ScanParseSkel\OSGScanParseFieldTypeMapper.inl
# End Source File
# End Group
# Begin Group "OSGLoader_inl"

# PROP Default_Filter "inl"
# End Group
# Begin Group "VRMLLoader_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\VRMLLoader\OSGVRMLNodeFactory.inl
# End Source File
# End Group
# Begin Group "VRMLWriter_inl"

# PROP Default_Filter "inl"
# Begin Source File

SOURCE=..\..\VRMLWriter\OSGVRMLWriteAction.inl
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "tmpStore"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\defs
# End Source File
# End Group
# End Target
# End Project
