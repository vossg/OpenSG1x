# Microsoft Developer Studio Project File - Name="State" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=State - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "State.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "State.mak" CFG="State - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "State - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "State - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "State - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "State - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /ZI /Od /I "." /I "..\Window" /I "..\Action" /I "..\Action\DrawAction" /I "..\Nodes\Misc" /I "..\FieldContainer" /I "..\Field" /I "..\Log" /I "..\Base" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ENDIF 

# Begin Target

# Name "State - Win32 Release"
# Name "State - Win32 Debug"
# Begin Source File

SOURCE=.\OSGLightChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGLightChunk.h
# End Source File
# Begin Source File

SOURCE=.\OSGLightChunk.inl
# End Source File
# Begin Source File

SOURCE=.\OSGMaterialChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGMaterialChunk.h
# End Source File
# Begin Source File

SOURCE=.\OSGMaterialChunk.inl
# End Source File
# Begin Source File

SOURCE=.\OSGState.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGState.h
# End Source File
# Begin Source File

SOURCE=.\OSGState.inl
# End Source File
# Begin Source File

SOURCE=.\OSGStateChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGStateChunk.h
# End Source File
# Begin Source File

SOURCE=.\OSGStateChunk.inl
# End Source File
# Begin Source File

SOURCE=.\OSGTransformChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGTransformChunk.h
# End Source File
# Begin Source File

SOURCE=.\OSGTransformChunk.inl
# End Source File
# End Target
# End Project
