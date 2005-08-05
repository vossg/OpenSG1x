# Microsoft Developer Studio Project File - Name="##NAME##" - Package Owner=<4>%
# Microsoft Developer Studio Generated Build File, Format Version 6.00%
# ** DO NOT EDIT **%
%
# TARGTYPE "Win32 (x86) Console Application" 0x0103%
%
CFG=##NAME## - Win32 Debug%
!MESSAGE This is not a valid makefile. To build this project using NMAKE,%
!MESSAGE use the Export Makefile command and run%
!MESSAGE %
!MESSAGE NMAKE /f "##NAME##.mak".%
!MESSAGE %
!MESSAGE You can specify a configuration when running NMAKE%
!MESSAGE by defining the macro CFG on the command line. For example:%
!MESSAGE %
!MESSAGE NMAKE /f "##NAME##.mak" CFG="##NAME## - Win32 Debug"%
!MESSAGE %
!MESSAGE Possible choices for configuration are:%
!MESSAGE %
!MESSAGE "##NAME## - Win32 Release" (based on "Win32 (x86) Console Application")%
!MESSAGE "##NAME## - Win32 Debug" (based on "Win32 (x86) Console Application")%
!MESSAGE %
%
# Begin Project%
# PROP AllowPerConfigDependencies 0%
# PROP Scc_ProjName ""%
# PROP Scc_LocalPath ""%
CPP=cl.exe%
RSC=rc.exe%
%
!IF  "$(CFG)" == "##NAME## - Win32 Release"%
%
# PROP BASE Use_MFC 0%
# PROP BASE Use_Debug_Libraries 0%
# PROP BASE Output_Dir "Release"%
# PROP BASE Intermediate_Dir "Release"%
# PROP BASE Target_Dir ""%
# PROP Use_MFC 0%
# PROP Use_Debug_Libraries 0%
# PROP Output_Dir "Release"%
# PROP Intermediate_Dir "Release"%
# PROP Target_Dir ""%
# ADD BASE CPP %
# ADD CPP -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -DOSG_BUILD_DLL -GX -Gi- -FD -GR -Zm1200 -O2 -Ob1 -MD -DOSG_WITH_GLUT -DOSG_WITH_GIF -DOSG_WITH_TIF -DOSG_WITH_JPG -DOSG_WITH_STLPORT -I../include -I../lib/glut_3.7/include -I../lib/jpg6b/include -I../lib/tiff-3.5.4/include -I../include/stlport /FD /c %
# SUBTRACT CPP %
# ADD BASE RSC /l 0x409 /d "NDEBUG"%
# ADD RSC /l 0x409 /d "NDEBUG"%
BSC32=bscmake.exe%
# ADD BASE BSC32 /nologo%
# ADD BSC32 /nologo%
LINK32=link.exe%
# ADD BASE LINK32 %
# ADD LINK32 user32.lib kernel32.lib MSVCPRT.lib MSVCRT.lib winmm.lib wsock32.lib OSGBase.lib OSGSystem.lib OSGWindowGLUT.lib glut32.lib glu32.lib opengl32.lib tif32.lib libjpeg.lib stlport_vc71.lib -NODEFAULTLIB /LIBPATH:"..\lib" /LIBPATH:"..\lib\glut_3.7\lib" /LIBPATH:"../lib/jpg6b/lib" /LIBPATH:"../lib/tiff-3.5.4/lib" %
%
!ELSEIF  "$(CFG)" == "##NAME## - Win32 Debug"%
%
# PROP BASE Use_MFC 0%
# PROP BASE Use_Debug_Libraries 1%
# PROP BASE Output_Dir "Debug"%
# PROP BASE Intermediate_Dir "Debug"%
# PROP BASE Target_Dir ""%
# PROP Use_MFC 0%
# PROP Use_Debug_Libraries 1%
# PROP Output_Dir "Debug"%
# PROP Intermediate_Dir "Debug"%
# PROP Ignore_Export_Lib 0%
# PROP Target_Dir ""%
# ADD BASE CPP %
# ADD CPP -DWIN32 -D_WINDOWS -DWINVER=0x0400 -D_WIN32_WINDOWS=0x0410 -D_WIN32_WINNT=0x0400 -D_OSG_HAVE_CONFIGURED_H_ -DOSG_BUILD_DLL -GX -Gi- -FD -GR -Zm400 -ZI -Od -GZ -D_DEBUG -DOSG_DEBUG -MDd -DOSG_WITH_GLUT -DOSG_WITH_GIF -DOSG_WITH_TIF -DOSG_WITH_JPG -I../include -I../lib/glut_3.7/include -I../lib/jpg6b/include -I../lib/tiff-3.5.4/include -I../include/stlport /FD /c %
# SUBTRACT CPP %
# ADD BASE RSC /l 0x409 /d "_DEBUG"%
# ADD RSC /l 0x409 /d "_DEBUG"%
BSC32=bscmake.exe%
# ADD BASE BSC32 /nologo%
# ADD BSC32 /nologo%
LINK32=link.exe%
# ADD BASE LINK32 %
# ADD LINK32 user32.lib kernel32.lib MSVCPRTD.lib MSVCRTD.lib winmm.lib wsock32.lib OSGBaseD.lib OSGSystemD.lib OSGWindowGLUTD.lib glut32.lib glu32.lib opengl32.lib tif32.lib libjpeg.lib stlport_vc7.lib -NODEFAULTLIB -Debug /LIBPATH:"..\lib" /LIBPATH:"..\lib\glut_3.7\lib" /LIBPATH:"../lib/jpg6b/lib" /LIBPATH:"../lib/tiff-3.5.4/lib" %
# SUBTRACT LINK32 %
%
!ENDIF %
%
# Begin Target%
%
# Name "##NAME## - Win32 Release"%
# Name "##NAME## - Win32 Debug"%
# Begin Group "Source Files"%
%
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"%
##DEPS##%
# End Group%
# Begin Group "Header Files"%
%
# PROP Default_Filter "h;hpp;hxx;hm;inl"%
# End Group%
# Begin Group "Resource Files"%
%
# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"%
# End Group%
# End Target%
# End Project%
