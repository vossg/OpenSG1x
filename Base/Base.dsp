# Microsoft Developer Studio Project File - Name="Base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Base - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Base.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Base.mak" CFG="Base - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Base - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Base - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "Base - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\Log" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Base - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX- /ZI /Od /I "." /I "..\Log" /I "..\FieldContainer" /I "..\Field" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Base - Win32 Release"
# Name "Base - Win32 Debug"
# Begin Source File

SOURCE=.\OSGAspect.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGAspect.h
# End Source File
# Begin Source File

SOURCE=.\OSGBarrier.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGBarrier.h
# End Source File
# Begin Source File

SOURCE=.\OSGBaseFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGBaseFunctions.h
# End Source File
# Begin Source File

SOURCE=.\OSGBaseTypes.h
# End Source File
# Begin Source File

SOURCE=.\OSGBoxVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGBoxVolume.h
# End Source File
# Begin Source File

SOURCE=.\OSGChangeList.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGChangeList.h
# End Source File
# Begin Source File

SOURCE=.\OSGColor.h
# End Source File
# Begin Source File

SOURCE=.\OSGColor.inl
# End Source File
# Begin Source File

SOURCE=.\OSGConfig.h
# End Source File
# Begin Source File

SOURCE=.\OSGCylinderVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGCylinderVolume.h
# End Source File
# Begin Source File

SOURCE=.\OSGDate.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGDate.h
# End Source File
# Begin Source File

SOURCE=.\OSGDynamicVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGDynamicVolume.h
# End Source File
# Begin Source File

SOURCE=.\OSGFrustumVolume.h
# End Source File
# Begin Source File

SOURCE=.\OSGFunctors.h
# End Source File
# Begin Source File

SOURCE=.\OSGFunctors.inl
# End Source File
# Begin Source File

SOURCE=.\OSGLine.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGLine.h
# End Source File
# Begin Source File

SOURCE=.\OSGLock.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGLock.h
# End Source File
# Begin Source File

SOURCE=.\OSGMatrix.h
# End Source File
# Begin Source File

SOURCE=.\OSGMatrix.inl
# End Source File
# Begin Source File

SOURCE=.\OSGMatrixUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGMatrixUtility.h
# End Source File
# Begin Source File

SOURCE=.\OSGMemoryObject.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGMemoryObject.h
# End Source File
# Begin Source File

SOURCE=.\OSGPlane.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGPlane.h
# End Source File
# Begin Source File

SOURCE=.\OSGQuaternion.h
# End Source File
# Begin Source File

SOURCE=.\OSGQuaternion.inl
# End Source File
# Begin Source File

SOURCE=.\OSGSphereVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGSphereVolume.h
# End Source File
# Begin Source File

SOURCE=.\OSGString.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGString.h
# End Source File
# Begin Source File

SOURCE=.\OSGStringLink.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGStringLink.h
# End Source File
# Begin Source File

SOURCE=.\OSGThread.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGThread.h
# End Source File
# Begin Source File

SOURCE=.\OSGThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGThreadManager.h
# End Source File
# Begin Source File

SOURCE=.\OSGTime.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGTime.h
# End Source File
# Begin Source File

SOURCE=.\OSGVector.h
# End Source File
# Begin Source File

SOURCE=.\OSGVector.inl
# End Source File
# Begin Source File

SOURCE=.\OSGVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGVolume.h
# End Source File
# End Target
# End Project
