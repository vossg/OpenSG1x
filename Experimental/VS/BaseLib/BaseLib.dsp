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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "BaseLib - Win32 Debug"

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
# ADD CPP /MDd /W3 /Gm /GR /GX /ZI /Od /I ".." /I "..\..\..\Base" /I "..\..\..\Log" /I "..\..\..\Field" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x0400 /D WIN32_WINDOWS=0x0410 /D "OSG_BUILD_DLL" /D "_OSG_HAVE_CONFIGURED_H_" /FD /GZ /c
# SUBTRACT CPP /nologo /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BaseLib - Win32 Release"
# Name "BaseLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Field_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Field\OSGField.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGFieldFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGFieldType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGTypeInst.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Base\OSGBarrier.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBoxVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGCylinderVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDynamicVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGFrustumVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGLock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Log\OSGLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMatrixUtility.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMemoryObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMPBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGPlane.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGSphereVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGStringLink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTypeBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolume.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolumeFunctions.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Field_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Field\OSGBaseFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGBoolFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGColor3fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGColor3ubFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGColor4fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGColor4ubFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGDynamicVolumeFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGField.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGFieldFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGFieldType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGInt16Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGInt32Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGInt64Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGInt8Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMathFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMatrixFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMFBaseTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMField.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMFMathTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMFSysTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGMFVecTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGPlaneFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGPnt2fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGPnt3fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGPnt4fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGQuaternionFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGReal32Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGReal64Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSFBaseTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSField.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSFMathTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSFSysTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSFVecTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGStringFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSysFieldDataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGTimeFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGUInt16Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGUInt32Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGUInt64Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGUInt8Fields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGVec2fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGVec3fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGVec4fFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGVec4ubFields.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGVecFieldDataType.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Base\OSGBarrier.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseFunctions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBoxVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGColor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGConceptPropertyChecks.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGConfig.h
# End Source File
# Begin Source File

SOURCE=..\OSGConfigured.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGCylinderVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDynamicVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGFrustumVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGFunctors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGLock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Log\OSGLog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMatrix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMatrixUtility.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMemoryObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMPBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGPlane.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGQuaternion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGSphereVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGStringLink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTypeBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGTypeFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolume.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolumeFunctions.h
# End Source File
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "inl"
# Begin Group "Field_inl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Field\OSGMField.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Field\OSGSField.inl
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Base\OSGBaseFunctions.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGBoxVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGColor.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGCylinderVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDate.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGDynamicVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGFrustumVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGFunctors.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGLine.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Log\OSGLog.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGMatrix.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGQuaternion.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGSphereVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGThreadManager.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVector.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolume.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Base\OSGVolumeFunctions.inl
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
