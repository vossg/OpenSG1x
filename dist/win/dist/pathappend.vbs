' Append the OSGPath to the PATH,
' based on regread.vbs (even though not much is left ;),
' downloaded from the Windows Scripting Guide
' http://www.winguides.com/scripting/

Option Explicit

Dim WSHShell, script, path, osgpath
script=WScript.ScriptFullName 
osgpath=replace( script, "pathappend.vbs", "lib" )
Set WSHShell = CreateObject("WScript.Shell")
Path = GetEnv("PATH")
Path = Path & ";" & osgpath
'WScript.echo Path
WSHShell.Environment("USER").Item("PATH") = Path

public Function GetEnv(Var) 
'On Error GoTo CheckError
    GetEnv = WSHShell.Environment("USER").Item(Var)
    Exit Function
'CheckError:
GetEnv=""
End Function
