# Microsoft Developer Studio Project File - Name="fcdEdit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=fcdEdit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fcdEdit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fcdEdit.mak" CFG="fcdEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fcdEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "fcdEdit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fcdEdit - Win32 Release"

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
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "fcdEdit - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "FCD_GUI" /D "XMLPP_NOEXPORTS" /D "QT_NO_STL" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "QT_ACCESSIBILITY_SUPPORT" /D "QT_NO_DEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qt-mt301.lib qtmain.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /debug /machine:I386 /out:"fcdEdit.exe" /pdbtype:sept
# SUBTRACT LINK32 /nologo

!ENDIF 

# Begin Target

# Name "fcdEdit - Win32 Release"
# Name "fcdEdit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Field.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldContainerView.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldContainerView_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldContainerViewCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldContainerViewCtl_moc.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseComandLine.cpp
# End Source File
# Begin Source File

SOURCE=.\xmlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\xmlpp.cpp
# End Source File
# Begin Source File

SOURCE=.\xmltokenizer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\FCBaseTemplate_cpp.h
# End Source File
# Begin Source File

SOURCE=.\FCBaseTemplate_h.h
# End Source File
# Begin Source File

SOURCE=.\FCBaseTemplate_inl.h
# End Source File
# Begin Source File

SOURCE=.\FCFieldsTemplate_h.h
# End Source File
# Begin Source File

SOURCE=.\FCTemplate_cpp.h
# End Source File
# Begin Source File

SOURCE=.\FCTemplate_h.h
# End Source File
# Begin Source File

SOURCE=.\FCTemplate_inl.h
# End Source File
# Begin Source File

SOURCE=.\Field.h
# End Source File
# Begin Source File

SOURCE=.\FieldContainer.h
# End Source File
# Begin Source File

SOURCE=.\FieldContainerView.h

!IF  "$(CFG)" == "fcdEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "fcdEdit - Win32 Debug"

# Begin Custom Build
InputPath=.\FieldContainerView.h

"FieldContainerView_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	moc.exe -fFieldContainerView.h FieldContainerView.h -o FieldContainerView_moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FieldContainerViewCtl.h

!IF  "$(CFG)" == "fcdEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "fcdEdit - Win32 Debug"

# Begin Custom Build
InputPath=.\FieldContainerViewCtl.h

"FieldContainerViewCtl_moc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	moc.exe -fFieldContainerViewCtl.h FieldContainerViewCtl.h -o FieldContainerViewCtl_moc.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParseComandLine.h
# End Source File
# Begin Source File

SOURCE=.\shared_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\xmlconfig.hpp
# End Source File
# Begin Source File

SOURCE=.\xmlparser.hpp
# End Source File
# Begin Source File

SOURCE=.\xmlpp.hpp
# End Source File
# Begin Source File

SOURCE=.\xmltokenizer.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
