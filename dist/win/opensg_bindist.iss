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
Name: "{group}\OpenSG Scene Viewer"; Filename: "{app}\osgSceneViewer.exe"; Parameters: "{app}\bin"
Name: "{group}\OpenSG Home Page"; Filename: "{app}\OpenSG Web.url"
Name: "{group}\OpenSG"; Filename: "explorer.exe"; Parameters: "{app}"
Name: "{group}\OpenSG\Tutorials\Hello OpenSG"; Filename: "{app}\Tutorials\01hello.exe"
Name: "{group}\OpenSG\Tutorials\Move"; Filename: "{app}\Tutorials\02move.exe"
Name: "{group}\OpenSG\Tutorials\Sharing"; Filename: "{app}\Tutorials\03share.exe"
Name: "{group}\OpenSG\Tutorials\Hierarchical Transforms"; Filename: "{app}\Tutorials\04hiertransform.exe"
Name: "{group}\OpenSG\Tutorials\Geometry"; Filename: "{app}\Tutorials\05geometry.exe"
Name: "{group}\OpenSG\Tutorials\Indexed Geometry"; Filename: "{app}\Tutorials\06indexgeometry.exe"
Name: "{group}\OpenSG\Tutorials\Multi-Indexed Geometry"; Filename: "{app}\Tutorials\07multiindexgeometry.exe"
Name: "{group}\OpenSG\Tutorials\Materials"; Filename: "{app}\Tutorials\08materials.exe"
Name: "{group}\OpenSG\Tutorials\Traverse"; Filename: "{app}\Tutorials\09traverse.exe"
Name: "{group}\OpenSG\Tutorials\Loading"; Filename: "{app}\Tutorials\10loading.exe"
Name: "{group}\OpenSG\Tutorials\Picking"; Filename: "{app}\Tutorials\1picking.exe"
Name: "{group}\OpenSG\Tutorials\Cluster Server"; Filename: "{app}\Tutorials\12ClusterServer.exe"; Parameters: "-m server1"
Name: "{group}\OpenSG\Tutorials\Cluster Client"; Filename: "{app}\Tutorials\13ClusterClient.exe"; Parameters: "-m -f{app}\Tutorials\Data\tie.wrl server1"
Name: "{group}\OpenSG\Tutorials\Switch"; Filename: "{app}\Tutorials\14switch.exe"
Name: "{group}\OpenSG\Tutorials\Attachements"; Filename: "{app}\Tutorials\15attachments.exe"
Name: "{group}\OpenSG\Tutorials\Lights"; Filename: "{app}\Tutorials\16lights.exe"

Name: "{group}\Uninstall"; Filename: "{app}\unins000.exe"

