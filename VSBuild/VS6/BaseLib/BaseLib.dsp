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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -O2 -Ob1 -MD -DOSG_COMPILEBASELIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  /FD /c
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
# ADD CPP -Qwd985 -Qwd530 -Qwd981 -Qwd193 -Qwd444 -Qwd279 -Qwe698  -Qwe47 -Qwe373 -Qwe171 -Qwe373 -Qwe261 -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -D__INTEL_COMPILER_VERSION=700  -DOSG_BUILD_DLL -Qvc6 -GX -Gi- -Qansi -Qoption,cpp,--new_for_init -GR -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_COMPILEBASELIB -DOSG_WITH_GLUT -DOSG_WITH_QT -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_PNG -DOSG_WITH_GIF -DOSG_WITH_FREETYPE1 -DQT_NO_STL -DQT_DLL -DQT_THREAD_SUPPORT -DQT_ACCESSIBILITY_SUPPORT -DQT_NO_DEBUG -I.. -I.  -I../../../Source/Base/Base  -I../../../Source/Base/Field  -I../../../Source/Base/Functors  -I../../../Source/Base/Network/Base  -I../../../Source/Base/Network/Socket  -I../../../Source/Base/StringConversion  /FD /c
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
SOURCE=../../../Source/Base/Base/OSGQuaternion.h
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
SOURCE=../../../Source/Base/Field/OSGVec3fFields.h
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
SOURCE=../../../Source/Base/Network/Base/OSGNetworkMessage.h
# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket h"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramSocket.h
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGMulticastConnection.h
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
SOURCE=../../../Source/Base/Network/Socket/OSGStreamSockConnection.h
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

# End Group


# Begin Group "Inline Files"
# PROP Default_Filter "inl"

# Begin Group "SourceBaseBase inl"
# PROP Default_Filter ""

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
SOURCE=../../../Source/Base/Network/Base/OSGNetworkMessage.cpp
# End Source File

# End Group
# Begin Group "SourceBaseNetworkSocket cpp"
# PROP Default_Filter ""

# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGDgramSocket.cpp
# End Source File


# Begin Source File
SOURCE=../../../Source/Base/Network/Socket/OSGMulticastConnection.cpp
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
SOURCE=../../../Source/Base/Network/Socket/OSGStreamSockConnection.cpp
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

# End Group
# Begin Group "Resource Files"
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"


# End Group

# End Target
# End Project
