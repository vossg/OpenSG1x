; OpenSG Windows Binary Distribution Script

; created with InnoSetup v. 3.0.6
; http://www.jrsoftware.org/isinfo.php

; This is a template that is converted to the real .iss by make_bindist

[Setup]
OutputBaseFilename=OpenSG-%VERSION%-%COMPILER%%SUFFIX%
OutputDir=.
AllowNoIcons=yes
AllowRootDirectory=yes
AppName=OpenSG
AppPublisher=OpenSG Forum
AppPublisherURL=http://www.opensg.org
AppSupportURL=http://www.opensg.org
AppUpdatesURL=http://www.opensg.org
AppVersion=%VERSION%
AppVerName=OpenSG %VERSION%
DefaultDirName={pf}\OpenSG
DefaultGroupName=OpenSG
LicenseFile=OpenSG-%VERSION%-%DISTNAME%-%COMPILER%%SUFFIX%\COPYING.txt
InfoAfterFile=OpenSG-%VERSION%-%DISTNAME%-%COMPILER%%SUFFIX%\README.txt
SourceDir=.


[Files]
;root directory docs
Source: "OpenSG-%VERSION%-%DISTNAME%-%COMPILER%%SUFFIX%\*"; DestDir: "{app}";  Flags: recursesubdirs

[INI]
Filename: "{app}\OpenSG Web.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://www.opensg.org"

[Registry]
; Prefer the pathappend.vbs, it's a little niver concerning changes
; Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "Path"; ValueData: "{olddata};{app}\lib"

[Run]
Filename: "{app}\pathappend.vbs"; WorkingDir: "{app}"; Flags: shellexec

[UninstallRun]
Filename: "{app}\pathremove.vbs"; WorkingDir: "{app}"; Flags: shellexec

[Icons]
Name: "{group}\OpenSG Scene Viewer"; Filename: "{app}\osgSceneViewer.exe";
Name: "{group}\OpenSG Field Container Editor"; Filename: "{app}\fcdEdit.exe";
Name: "{group}\OpenSG Home Page"; Filename: "{app}\OpenSG Web.url"
Name: "{group}\OpenSG Directory"; Filename: "explorer.exe"; Parameters: "{app}"
Name: "{group}\Tutorials\01 Hello OpenSG"; Filename: "{app}\Tutorials\01hello.exe"
Name: "{group}\Tutorials\02 Move"; Filename: "{app}\Tutorials\02move.exe"
Name: "{group}\Tutorials\03 Sharing"; Filename: "{app}\Tutorials\03share.exe"
Name: "{group}\Tutorials\04 Hierarchical Transforms"; Filename: "{app}\Tutorials\04hiertransform.exe"
Name: "{group}\Tutorials\05 Geometry"; Filename: "{app}\Tutorials\05geometry.exe"
Name: "{group}\Tutorials\06 Indexed Geometry"; Filename: "{app}\Tutorials\06indexgeometry.exe"
Name: "{group}\Tutorials\07 Multi-Indexed Geometry"; Filename: "{app}\Tutorials\07multiindexgeometry.exe"
Name: "{group}\Tutorials\08 Materials"; Filename: "{app}\Tutorials\08materials.exe"
Name: "{group}\Tutorials\09 Traverse"; Filename: "{app}\Tutorials\09traverse.exe"
Name: "{group}\Tutorials\10 Loading"; Filename: "{app}\Tutorials\10loading.exe"
Name: "{group}\Tutorials\11 Picking"; Filename: "{app}\Tutorials\1picking.exe"
Name: "{group}\Tutorials\12 Cluster Server"; Filename: "{app}\Tutorials\12ClusterServer.exe"; Parameters: "-m server1"
Name: "{group}\Tutorials\13 Cluster Client"; Filename: "{app}\Tutorials\13ClusterClient.exe"; Parameters: "-m -f{app}\Tutorials\Data\tie.wrl server1"
Name: "{group}\Tutorials\14 Switch"; Filename: "{app}\Tutorials\14switch.exe"
Name: "{group}\Tutorials\15 Attachements"; Filename: "{app}\Tutorials\15attachments.exe"
Name: "{group}\Tutorials\16 Lights"; Filename: "{app}\Tutorials\16lights.exe"
Name: "{group}\Tutorials\17 Deep Clone"; Filename: "{app}\Tutorials\17deepClone.exe"
Name: "{group}\Tutorials\18 OpenGL Slave"; Filename: "{app}\Tutorials\18opengl_slave.exe"
Name: "{group}\Tutorials\19 Local Lights"; Filename: "{app}\Tutorials\19LocalLights.exe"
Name: "{group}\Tutorials\20 Material Sort"; Filename: "{app}\Tutorials\20MaterialSort.exe"
Name: "{group}\Tutorials\21 Shadows"; Filename: "{app}\Tutorials\21Shadows.exe"
Name: "{group}\Tutorials\22 Shader"; Filename: "{app}\Tutorials\22Shader.exe"
Name: "{group}\Tutorials\23 Video Texture Background"; Filename: "{app}\Tutorials\23videotexturebackground.exe"
Name: "{group}\Tutorials\24 Advanced Shadows"; Filename: "{app}\Tutorials\24Shadows.exe"
Name: "{group}\Tutorials\25 Occlusion Culling"; Filename: "{app}\Tutorials\25OcclusionCulling.exe"
Name: "{group}\Tutorials\26 Geometry Shader"; Filename: "{app}\Tutorials\26GeometryShader.exe"
Name: "{group}\Tutorials\27 Nurbs"; Filename: "{app}\Tutorials\27RationalSurface.exe"

Name: "{group}\Uninstall"; Filename: "{app}\unins000.exe"

