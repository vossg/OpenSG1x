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

Name: "{group}\Uninstall"; Filename: "{app}\unins000.exe"

