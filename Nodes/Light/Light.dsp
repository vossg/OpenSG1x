# Microsoft Developer Studio Project File - Name="Light" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Light - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Light.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Light.mak" CFG="Light - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Light - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Light - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "Light - Win32 Release"

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

!ELSEIF  "$(CFG)" == "Light - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX- /ZI /Od /I "." /I "..\..\Action" /I "..\..\Action\DrawAction" /I "..\Geometry" /I "..\Misc" /I "..\..\FieldContainer" /I "..\..\Field" /I "..\..\Log" /I "..\..\Base" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
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

# Name "Light - Win32 Release"
# Name "Light - Win32 Debug"
# Begin Source File

SOURCE=.\OSGDirectionalLight.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGDirectionalLight.h
# End Source File
# Begin Source File

SOURCE=.\OSGDirectionalLight.inl
# End Source File
# Begin Source File

SOURCE=.\OSGLightBase.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGLightBase.h
# End Source File
# Begin Source File

SOURCE=.\OSGLightBase.inl
# End Source File
# Begin Source File

SOURCE=.\OSGPointLight.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGPointLight.h
# End Source File
# Begin Source File

SOURCE=.\OSGPointLight.inl
# End Source File
# Begin Source File

SOURCE=.\OSGSpotLight.cpp
# End Source File
# Begin Source File

SOURCE=.\OSGSpotLight.h
# End Source File
# Begin Source File

SOURCE=.\OSGSpotLight.inl
# End Source File
# End Target
# End Project
