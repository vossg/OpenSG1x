# Microsoft Developer Studio Project File - Name="Geometry" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Geometry - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Geometry.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Geometry.mak" CFG="Geometry - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Geometry - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Geometry - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "Geometry - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\Action\DrawAction" /I "." /I "..\..\Base" /I "..\..\Action" /I "..\..\FieldContainer" /I "..\..\Field" /I "..\..\Log" /I "..\..\Material" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Geometry - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /ZI /Od /I "..\..\Action\DrawAction" /I "." /I "..\..\Base" /I "..\..\Action" /I "..\..\FieldContainer" /I "..\..\Field" /I "..\..\Log" /I "..\..\Material" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
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

# Name "Geometry - Win32 Release"
# Name "Geometry - Win32 Debug"
# Begin Source File

SOURCE=.\OSGFaceIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFaceIterator.h
# End Source File
# Begin Source File

SOURCE=.\OSGGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGGeometry.h
# End Source File
# Begin Source File

SOURCE=.\OSGGeometry.inl
# End Source File
# Begin Source File

SOURCE=.\OSGGeoProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGGeoProperty.h
# End Source File
# Begin Source File

SOURCE=.\OSGGeoProperty.inl
# End Source File
# Begin Source File

SOURCE=.\OSGGeoPumpFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGGeoPumpFactory.h
# End Source File
# Begin Source File

SOURCE=.\OSGGeoPumpFactory.inl
# End Source File
# Begin Source File

SOURCE=.\OSGPrimitiveIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGPrimitiveIterator.h
# End Source File
# Begin Source File

SOURCE=.\OSGSimpleGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGSimpleGeometry.h
# End Source File
# Begin Source File

SOURCE=.\OSGTriangleIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGTriangleIterator.h
# End Source File
# End Target
# End Project
