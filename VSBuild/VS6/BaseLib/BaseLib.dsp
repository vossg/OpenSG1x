# Microsoft Developer Studio Project File - Name="BaseLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BaseLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BaseLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BaseLib.mak" CFG="BaseLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BaseLib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BaseLib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BaseLib - Win32 Release"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEBASELIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib libmmd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib -NODEFAULTLIB -dll -map -out:..\lib\opt\OSGBase.dll

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=710  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi_alias -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEBASELIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  -I../../../Source/Base/Xml  /FD /c
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
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib libmmdd.lib winmm.lib wsock32.lib  opengl32.lib glu32.lib gdi32.lib -NODEFAULTLIB -dll -map -Debug -out:..\lib\dbg\OSGBase.dll
      

!ENDIF 

# Begin Target

# Name "BaseLib - Win32 Release"
# Name "BaseLib - Win32 Debug"

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceBaseBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBarrier.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseFunctions.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseThread.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseTypeTraits.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBinaryDataHandler.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBoxVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGColor.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGConceptPropertyChecks.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGConfig.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGCylinderVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDate.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDynamicVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGException.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGExportDefines.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFileSystem.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFrustumVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGL.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLEXT.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLU.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLUT.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDString.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDStringLink.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLine.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLinearTransform.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLock.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLog.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMPBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrix.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrixUtility.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMemoryObject.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGNormalQuantifier.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPathHandler.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPlane.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPolytopeVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGQuaternion.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGReal16.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSharedLibrary.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSphereVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGThreadManager.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTime.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVector.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolume.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolumeFunctions.h
# End Source File

# End Group
# Begin Group "SourceBaseField h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Field/OSGBaseFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGBoolFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor3fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor3ubFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor4fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor4ubFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGDynamicVolumeFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGField.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGGLenumFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt16Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt32Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt64Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt8Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFBaseTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFMathTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFSysTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFVecTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMField.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldVector.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMathFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMatrixFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPlaneFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt2fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt3fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt4fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGQuaternionFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGReal32Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGReal64Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFBaseTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFMathTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFSysTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFVecTypes.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSField.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGStringFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSysFieldDataType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGTimeFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt16Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt32Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt64Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt8Fields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2sFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2usFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec3fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec3sFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec4fFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec4ubFields.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVecFieldDataType.h
# End Source File

# End Group
# Begin Group "SourceBaseFunctors h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGFunctorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctorBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors1.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors2.h
# End Source File

# End Group
# Begin Group "SourceBaseNetworkBase h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGBinaryMessage.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionFactory.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionType.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGGroupConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGNetworkMessage.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGPointConnection.h
# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgram.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramQueue.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramSocket.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupMCastConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockPipeline.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointMCastConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockConnection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockPipeline.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocket.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketAddress.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketException.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketSelection.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGStreamSocket.h
# End Source File

# End Group
# Begin Group "SourceBaseStringConversion h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGIndenter.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStandardStringConversionState.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringConversionStateBase.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringTokenizer.h
# End Source File

# End Group
# Begin Group "SourceBaseXml h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGShared_ptr.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlconfig.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlparser.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlpp.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmltokenizer.h
# End Source File

# End Group

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceBaseBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBarrier.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseFunctions.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBinaryDataHandler.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBoxVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGColor.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGCylinderVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDate.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDynamicVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFileSystem.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFrustumVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDString.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDStringLink.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLine.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLinearTransform.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLog.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrix.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGNormalQuantifier.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPlane.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPolytopeVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGQuaternion.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSphereVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGThreadManager.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTime.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVector.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolume.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolumeFunctions.inl
# End Source File

# End Group
# Begin Group "SourceBaseField inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMField.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldTypeDef.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldTypeScanTypeDef.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldVector.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSField.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFieldTypeDef.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFieldTypeScanTypeDef.inl
# End Source File

# End Group
# Begin Group "SourceBaseFunctors inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGFunctorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctorBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors1.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors2.inl
# End Source File

# End Group
# Begin Group "SourceBaseNetworkBase inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGBinaryMessage.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnection.inl
# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgram.inl
# End Source File

# End Group
# Begin Group "SourceBaseStringConversion inl"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGIndenter.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStandardStringConversionState.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringConversionStateBase.inl
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringTokenizer.inl
# End Source File

# End Group
# Begin Group "SourceBaseXml inl"
# PROP Default_Filter ""
# End Group

# End Group


# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Group "SourceBaseBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBarrier.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseFunctions.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseThread.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBinaryDataHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBoxVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGColor.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGCylinderVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDataType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDate.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDynamicVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGException.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFrustumVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDString.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDStringLink.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLine.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLock.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLog.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMPBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrixUtility.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMemoryObject.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGNormalQuantifier.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPathHandler.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPlane.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPolytopeVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGReal16.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSharedLibrary.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSphereVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGThreadManager.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTime.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeBase.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVector.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolume.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolumeFunctions.cpp
# End Source File

# End Group
# Begin Group "SourceBaseField cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Field/OSGField.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGTypeInst.cpp
# End Source File

# End Group
# Begin Group "SourceBaseFunctors cpp"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseNetworkBase cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGBinaryMessage.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionFactory.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionType.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGGroupConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGNetworkMessage.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGPointConnection.cpp
# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgram.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramQueue.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramSocket.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupMCastConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockPipeline.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointMCastConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockConnection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockPipeline.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocket.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketAddress.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketException.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketSelection.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGStreamSocket.cpp
# End Source File

# End Group
# Begin Group "SourceBaseStringConversion cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGIndenter.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStandardStringConversionState.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringTokenizer.cpp
# End Source File

# End Group
# Begin Group "SourceBaseXml cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlparser.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlpp.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmltokenizer.cpp
# End Source File

# End Group

# End Group
# Begin Group "Scan/Parse Files"
# PROP Default_Filter "y;l"

# Begin Group "SourceBaseBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseField ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseFunctors ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseNetworkBase ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseNetworkSocket ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseStringConversion ly"
# PROP Default_Filter ""
# End Group
# Begin Group "SourceBaseXml ly"
# PROP Default_Filter ""
# End Group

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group


# Begin Group "Header Install"
# PROP Default_Filter "h;hpp;hxx;hm"

# Begin Group "SourceBaseBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBarrier.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBarrier.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBarrier.h > ../include/OpenSG/OSGBarrier.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBase.h > ../include/OpenSG/OSGBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseFunctions.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseFunctions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBaseFunctions.h > ../include/OpenSG/OSGBaseFunctions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseThread.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseThread.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBaseThread.h > ../include/OpenSG/OSGBaseThread.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseTypeTraits.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseTypeTraits.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBaseTypeTraits.h > ../include/OpenSG/OSGBaseTypeTraits.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBaseTypes.h > ../include/OpenSG/OSGBaseTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBinaryDataHandler.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBinaryDataHandler.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBinaryDataHandler.h > ../include/OpenSG/OSGBinaryDataHandler.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBoxVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBoxVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBoxVolume.h > ../include/OpenSG/OSGBoxVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGColor.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGColor.h > ../include/OpenSG/OSGColor.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGConceptPropertyChecks.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConceptPropertyChecks.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGConceptPropertyChecks.h > ../include/OpenSG/OSGConceptPropertyChecks.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGConfig.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConfig.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGConfig.h > ../include/OpenSG/OSGConfig.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGCylinderVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCylinderVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGCylinderVolume.h > ../include/OpenSG/OSGCylinderVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGDataType.h > ../include/OpenSG/OSGDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDate.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDate.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGDate.h > ../include/OpenSG/OSGDate.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDynamicVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDynamicVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGDynamicVolume.h > ../include/OpenSG/OSGDynamicVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGException.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGException.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGException.h > ../include/OpenSG/OSGException.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGExportDefines.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGExportDefines.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGExportDefines.h > ../include/OpenSG/OSGExportDefines.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFileSystem.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileSystem.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGFileSystem.h > ../include/OpenSG/OSGFileSystem.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFrustumVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFrustumVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGFrustumVolume.h > ../include/OpenSG/OSGFrustumVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGL.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGL.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGGL.h > ../include/OpenSG/OSGGL.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLEXT.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGLEXT.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGGLEXT.h > ../include/OpenSG/OSGGLEXT.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLU.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGLU.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGGLU.h > ../include/OpenSG/OSGGLU.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGGLUT.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGLUT.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGGLUT.h > ../include/OpenSG/OSGGLUT.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDString.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIDString.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGIDString.h > ../include/OpenSG/OSGIDString.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDStringLink.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIDStringLink.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGIDStringLink.h > ../include/OpenSG/OSGIDStringLink.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLine.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLine.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLine.h > ../include/OpenSG/OSGLine.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLinearTransform.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLinearTransform.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLinearTransform.h > ../include/OpenSG/OSGLinearTransform.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLock.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLock.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLock.h > ../include/OpenSG/OSGLock.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLog.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLog.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLog.h > ../include/OpenSG/OSGLog.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMPBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMPBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGMPBase.h > ../include/OpenSG/OSGMPBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrix.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrix.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGMatrix.h > ../include/OpenSG/OSGMatrix.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrixUtility.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixUtility.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGMatrixUtility.h > ../include/OpenSG/OSGMatrixUtility.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMemoryObject.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMemoryObject.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGMemoryObject.h > ../include/OpenSG/OSGMemoryObject.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGNormalQuantifier.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNormalQuantifier.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGNormalQuantifier.h > ../include/OpenSG/OSGNormalQuantifier.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPathHandler.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPathHandler.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGPathHandler.h > ../include/OpenSG/OSGPathHandler.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPlane.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPlane.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGPlane.h > ../include/OpenSG/OSGPlane.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPolytopeVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolytopeVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGPolytopeVolume.h > ../include/OpenSG/OSGPolytopeVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGQuaternion.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQuaternion.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGQuaternion.h > ../include/OpenSG/OSGQuaternion.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGReal16.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGReal16.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGReal16.h > ../include/OpenSG/OSGReal16.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSharedLibrary.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSharedLibrary.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGSharedLibrary.h > ../include/OpenSG/OSGSharedLibrary.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSphereVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSphereVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGSphereVolume.h > ../include/OpenSG/OSGSphereVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGThreadManager.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGThreadManager.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGThreadManager.h > ../include/OpenSG/OSGThreadManager.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTime.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTime.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGTime.h > ../include/OpenSG/OSGTime.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypeBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGTypeBase.h > ../include/OpenSG/OSGTypeBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTypeFactory.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypeFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGTypeFactory.h > ../include/OpenSG/OSGTypeFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVector.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVector.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVector.h > ../include/OpenSG/OSGVector.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolume.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolume.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVolume.h > ../include/OpenSG/OSGVolume.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolumeFunctions.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolumeFunctions.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVolumeFunctions.h > ../include/OpenSG/OSGVolumeFunctions.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBarrier.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBarrier.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBarrier.inl > ../include/OpenSG/OSGBarrier.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBaseFunctions.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseFunctions.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBaseFunctions.inl > ../include/OpenSG/OSGBaseFunctions.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBinaryDataHandler.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBinaryDataHandler.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBinaryDataHandler.inl > ../include/OpenSG/OSGBinaryDataHandler.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGBoxVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBoxVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGBoxVolume.inl > ../include/OpenSG/OSGBoxVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGColor.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGColor.inl > ../include/OpenSG/OSGColor.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGCylinderVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGCylinderVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGCylinderVolume.inl > ../include/OpenSG/OSGCylinderVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDate.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDate.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGDate.inl > ../include/OpenSG/OSGDate.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGDynamicVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDynamicVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGDynamicVolume.inl > ../include/OpenSG/OSGDynamicVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFileSystem.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFileSystem.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGFileSystem.inl > ../include/OpenSG/OSGFileSystem.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGFrustumVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFrustumVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGFrustumVolume.inl > ../include/OpenSG/OSGFrustumVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDString.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIDString.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGIDString.inl > ../include/OpenSG/OSGIDString.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGIDStringLink.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIDStringLink.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGIDStringLink.inl > ../include/OpenSG/OSGIDStringLink.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLine.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLine.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLine.inl > ../include/OpenSG/OSGLine.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLinearTransform.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLinearTransform.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLinearTransform.inl > ../include/OpenSG/OSGLinearTransform.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGLog.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGLog.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGLog.inl > ../include/OpenSG/OSGLog.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGMatrix.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrix.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGMatrix.inl > ../include/OpenSG/OSGMatrix.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGNormalQuantifier.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNormalQuantifier.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGNormalQuantifier.inl > ../include/OpenSG/OSGNormalQuantifier.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPlane.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPlane.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGPlane.inl > ../include/OpenSG/OSGPlane.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGPolytopeVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPolytopeVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGPolytopeVolume.inl > ../include/OpenSG/OSGPolytopeVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGQuaternion.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQuaternion.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGQuaternion.inl > ../include/OpenSG/OSGQuaternion.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGSphereVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSphereVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGSphereVolume.inl > ../include/OpenSG/OSGSphereVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGThreadManager.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGThreadManager.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGThreadManager.inl > ../include/OpenSG/OSGThreadManager.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGTime.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTime.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGTime.inl > ../include/OpenSG/OSGTime.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVector.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVector.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVector.inl > ../include/OpenSG/OSGVector.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolume.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolume.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVolume.inl > ../include/OpenSG/OSGVolume.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Base/OSGVolumeFunctions.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVolumeFunctions.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Base/OSGVolumeFunctions.inl > ../include/OpenSG/OSGVolumeFunctions.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseField Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Field/OSGBaseFieldDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBaseFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGBaseFieldDataType.h > ../include/OpenSG/OSGBaseFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGBoolFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBoolFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGBoolFields.h > ../include/OpenSG/OSGBoolFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor3fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor3fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGColor3fFields.h > ../include/OpenSG/OSGColor3fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor3ubFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor3ubFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGColor3ubFields.h > ../include/OpenSG/OSGColor3ubFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor4fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor4fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGColor4fFields.h > ../include/OpenSG/OSGColor4fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGColor4ubFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGColor4ubFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGColor4ubFields.h > ../include/OpenSG/OSGColor4ubFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGDynamicVolumeFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDynamicVolumeFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGDynamicVolumeFields.h > ../include/OpenSG/OSGDynamicVolumeFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGField.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGField.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGField.h > ../include/OpenSG/OSGField.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGFieldDataType.h > ../include/OpenSG/OSGFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldFactory.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGFieldFactory.h > ../include/OpenSG/OSGFieldFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGFieldType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFieldType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGFieldType.h > ../include/OpenSG/OSGFieldType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGGLenumFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGLenumFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGGLenumFields.h > ../include/OpenSG/OSGGLenumFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt16Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInt16Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGInt16Fields.h > ../include/OpenSG/OSGInt16Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt32Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInt32Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGInt32Fields.h > ../include/OpenSG/OSGInt32Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt64Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInt64Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGInt64Fields.h > ../include/OpenSG/OSGInt64Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGInt8Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGInt8Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGInt8Fields.h > ../include/OpenSG/OSGInt8Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFBaseTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFBaseTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFBaseTypes.h > ../include/OpenSG/OSGMFBaseTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFMathTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFMathTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFMathTypes.h > ../include/OpenSG/OSGMFMathTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFSysTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFSysTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFSysTypes.h > ../include/OpenSG/OSGMFSysTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFVecTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFVecTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFVecTypes.h > ../include/OpenSG/OSGMFVecTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMField.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMField.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMField.h > ../include/OpenSG/OSGMField.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldVector.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFieldVector.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFieldVector.h > ../include/OpenSG/OSGMFieldVector.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMathFieldDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMathFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMathFieldDataType.h > ../include/OpenSG/OSGMathFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMatrixFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMatrixFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMatrixFields.h > ../include/OpenSG/OSGMatrixFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPlaneFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPlaneFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGPlaneFields.h > ../include/OpenSG/OSGPlaneFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt2fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPnt2fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGPnt2fFields.h > ../include/OpenSG/OSGPnt2fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt3fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPnt3fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGPnt3fFields.h > ../include/OpenSG/OSGPnt3fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGPnt4fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPnt4fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGPnt4fFields.h > ../include/OpenSG/OSGPnt4fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGQuaternionFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGQuaternionFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGQuaternionFields.h > ../include/OpenSG/OSGQuaternionFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGReal32Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGReal32Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGReal32Fields.h > ../include/OpenSG/OSGReal32Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGReal64Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGReal64Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGReal64Fields.h > ../include/OpenSG/OSGReal64Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFBaseTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFBaseTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFBaseTypes.h > ../include/OpenSG/OSGSFBaseTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFMathTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFMathTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFMathTypes.h > ../include/OpenSG/OSGSFMathTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFSysTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFSysTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFSysTypes.h > ../include/OpenSG/OSGSFSysTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFVecTypes.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFVecTypes.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFVecTypes.h > ../include/OpenSG/OSGSFVecTypes.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSField.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSField.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSField.h > ../include/OpenSG/OSGSField.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGStringFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStringFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGStringFields.h > ../include/OpenSG/OSGStringFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSysFieldDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSysFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSysFieldDataType.h > ../include/OpenSG/OSGSysFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGTimeFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTimeFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGTimeFields.h > ../include/OpenSG/OSGTimeFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt16Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGUInt16Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGUInt16Fields.h > ../include/OpenSG/OSGUInt16Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt32Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGUInt32Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGUInt32Fields.h > ../include/OpenSG/OSGUInt32Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt64Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGUInt64Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGUInt64Fields.h > ../include/OpenSG/OSGUInt64Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGUInt8Fields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGUInt8Fields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGUInt8Fields.h > ../include/OpenSG/OSGUInt8Fields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec2fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec2fFields.h > ../include/OpenSG/OSGVec2fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2sFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec2sFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec2sFields.h > ../include/OpenSG/OSGVec2sFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec2usFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec2usFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec2usFields.h > ../include/OpenSG/OSGVec2usFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec3fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec3fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec3fFields.h > ../include/OpenSG/OSGVec3fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec3sFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec3sFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec3sFields.h > ../include/OpenSG/OSGVec3sFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec4fFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec4fFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec4fFields.h > ../include/OpenSG/OSGVec4fFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVec4ubFields.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVec4ubFields.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVec4ubFields.h > ../include/OpenSG/OSGVec4ubFields.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGVecFieldDataType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGVecFieldDataType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGVecFieldDataType.h > ../include/OpenSG/OSGVecFieldDataType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMField.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMField.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMField.inl > ../include/OpenSG/OSGMField.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldTypeDef.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFieldTypeDef.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFieldTypeDef.inl > ../include/OpenSG/OSGMFieldTypeDef.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldTypeScanTypeDef.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFieldTypeScanTypeDef.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFieldTypeScanTypeDef.inl > ../include/OpenSG/OSGMFieldTypeScanTypeDef.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGMFieldVector.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGMFieldVector.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGMFieldVector.inl > ../include/OpenSG/OSGMFieldVector.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSField.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSField.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSField.inl > ../include/OpenSG/OSGSField.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFieldTypeDef.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFieldTypeDef.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFieldTypeDef.inl > ../include/OpenSG/OSGSFieldTypeDef.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Field/OSGSFieldTypeScanTypeDef.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSFieldTypeScanTypeDef.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Field/OSGSFieldTypeScanTypeDef.inl > ../include/OpenSG/OSGSFieldTypeScanTypeDef.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseFunctors Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGFunctorBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFunctorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGFunctorBase.h > ../include/OpenSG/OSGFunctorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctorBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctorBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctorBase.h > ../include/OpenSG/OSGTypedFunctorBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors.h > ../include/OpenSG/OSGTypedFunctors.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors1.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors1.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors1.h > ../include/OpenSG/OSGTypedFunctors1.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors2.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors2.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors2.h > ../include/OpenSG/OSGTypedFunctors2.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGFunctorBase.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGFunctorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGFunctorBase.inl > ../include/OpenSG/OSGFunctorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctorBase.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctorBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctorBase.inl > ../include/OpenSG/OSGTypedFunctorBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors.inl > ../include/OpenSG/OSGTypedFunctors.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors1.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors1.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors1.inl > ../include/OpenSG/OSGTypedFunctors1.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Functors/OSGTypedFunctors2.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGTypedFunctors2.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Functors/OSGTypedFunctors2.inl > ../include/OpenSG/OSGTypedFunctors2.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseNetworkBase Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGBinaryMessage.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBinaryMessage.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGBinaryMessage.h > ../include/OpenSG/OSGBinaryMessage.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGConnection.h > ../include/OpenSG/OSGConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionFactory.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConnectionFactory.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGConnectionFactory.h > ../include/OpenSG/OSGConnectionFactory.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnectionType.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConnectionType.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGConnectionType.h > ../include/OpenSG/OSGConnectionType.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGGroupConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGGroupConnection.h > ../include/OpenSG/OSGGroupConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGNetworkMessage.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGNetworkMessage.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGNetworkMessage.h > ../include/OpenSG/OSGNetworkMessage.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGPointConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGPointConnection.h > ../include/OpenSG/OSGPointConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGBinaryMessage.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGBinaryMessage.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGBinaryMessage.inl > ../include/OpenSG/OSGBinaryMessage.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Base/OSGConnection.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGConnection.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Base/OSGConnection.inl > ../include/OpenSG/OSGConnection.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgram.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDgram.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGDgram.h > ../include/OpenSG/OSGDgram.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramQueue.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDgramQueue.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGDgramQueue.h > ../include/OpenSG/OSGDgramQueue.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramSocket.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDgramSocket.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGDgramSocket.h > ../include/OpenSG/OSGDgramSocket.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupMCastConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupMCastConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGGroupMCastConnection.h > ../include/OpenSG/OSGGroupMCastConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupSockConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGGroupSockConnection.h > ../include/OpenSG/OSGGroupSockConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGGroupSockPipeline.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGGroupSockPipeline.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGGroupSockPipeline.h > ../include/OpenSG/OSGGroupSockPipeline.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointMCastConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointMCastConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGPointMCastConnection.h > ../include/OpenSG/OSGPointMCastConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockConnection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointSockConnection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGPointSockConnection.h > ../include/OpenSG/OSGPointSockConnection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGPointSockPipeline.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGPointSockPipeline.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGPointSockPipeline.h > ../include/OpenSG/OSGPointSockPipeline.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocket.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSocket.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGSocket.h > ../include/OpenSG/OSGSocket.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketAddress.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSocketAddress.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGSocketAddress.h > ../include/OpenSG/OSGSocketAddress.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketException.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSocketException.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGSocketException.h > ../include/OpenSG/OSGSocketException.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGSocketSelection.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGSocketSelection.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGSocketSelection.h > ../include/OpenSG/OSGSocketSelection.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGStreamSocket.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStreamSocket.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGStreamSocket.h > ../include/OpenSG/OSGStreamSocket.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgram.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGDgram.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Network/Socket/OSGDgram.inl > ../include/OpenSG/OSGDgram.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseStringConversion Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGIndenter.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIndenter.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGIndenter.h > ../include/OpenSG/OSGIndenter.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStandardStringConversionState.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStandardStringConversionState.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStandardStringConversionState.h > ../include/OpenSG/OSGStandardStringConversionState.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringConversionStateBase.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStringConversionStateBase.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStringConversionStateBase.h > ../include/OpenSG/OSGStringConversionStateBase.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringTokenizer.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStringTokenizer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStringTokenizer.h > ../include/OpenSG/OSGStringTokenizer.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGIndenter.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGIndenter.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGIndenter.inl > ../include/OpenSG/OSGIndenter.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStandardStringConversionState.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStandardStringConversionState.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStandardStringConversionState.inl > ../include/OpenSG/OSGStandardStringConversionState.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringConversionStateBase.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStringConversionStateBase.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStringConversionStateBase.inl > ../include/OpenSG/OSGStringConversionStateBase.inl

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/StringConversion/OSGStringTokenizer.inl

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGStringTokenizer.inl": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/StringConversion/OSGStringTokenizer.inl > ../include/OpenSG/OSGStringTokenizer.inl

# End Custom Build

!ENDIF

# End Source File

# End Group
# Begin Group "SourceBaseXml Install "
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGShared_ptr.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGShared_ptr.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Xml/OSGShared_ptr.h > ../include/OpenSG/OSGShared_ptr.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlconfig.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGXmlconfig.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Xml/OSGXmlconfig.h > ../include/OpenSG/OSGXmlconfig.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlparser.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGXmlparser.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Xml/OSGXmlparser.h > ../include/OpenSG/OSGXmlparser.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmlpp.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGXmlpp.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Xml/OSGXmlpp.h > ../include/OpenSG/OSGXmlpp.h

# End Custom Build

!ENDIF

# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Xml/OSGXmltokenizer.h

!IF  "$(CFG)" == "BaseLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

# Begin Custom Build

"../include/OpenSG/OSGXmltokenizer.h": $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	sed.exe -e "s/include[ ]*<OSG/include <OpenSG\/OSG/g" -e "s/include[ ]*\"OSG/include \"OpenSG\/OSG/g" ../../../Source/Base/Xml/OSGXmltokenizer.h > ../include/OpenSG/OSGXmltokenizer.h

# End Custom Build

!ENDIF

# End Source File

# End Group

# End Group

# End Target
# End Project
