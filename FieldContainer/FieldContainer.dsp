# Microsoft Developer Studio Project File - Name="FieldContainer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FieldContainer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FieldContainer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FieldContainer.mak" CFG="FieldContainer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FieldContainer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FieldContainer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "FieldContainer - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\Base" /I "..\Field" /I "..\Log" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "FieldContainer - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /ZI /Od /I "." /I "..\Base" /I "..\Field" /I "..\Log" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fr /YX /FD /GZ /c
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

# Name "FieldContainer - Win32 Release"
# Name "FieldContainer - Win32 Debug"
# Begin Source File

SOURCE=.\OSGAttachment.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGAttachment.h
# End Source File
# Begin Source File

SOURCE=.\OSGAttachment.inl
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainer.h
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainer.inl
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerBase.h
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerFactory.h
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerPtr.h
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerPtr.inl
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerType.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFieldContainerType.h
# End Source File
# Begin Source File

SOURCE=.\OSGFieldDescription.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGFieldDescription.h
# End Source File
# Begin Source File

SOURCE=.\OSGNode.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGNode.h
# End Source File
# Begin Source File

SOURCE=.\OSGNode.inl
# End Source File
# Begin Source File

SOURCE=.\OSGNodeCore.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGNodeCore.h
# End Source File
# Begin Source File

SOURCE=.\OSGNodeCore.inl
# End Source File
# End Target
# End Project
