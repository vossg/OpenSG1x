' Append the OSGPath to the PATH,
' based on regread.vbs (even though not much is left ;),
' downloaded from the Windows Scripting Guide
' http://www.winguides.com/scripting/

Option Explicit

Dim WSHShell, script, path, osgpath, pos, bpos, epos, oldpath, newpath
script=WScript.ScriptFullName 
osgpath=replace( script, "pathappend.vbs", "lib" )
'WScript.echo osgpath
Set WSHShell = CreateObject("WScript.Shell")
Path = WSHShell.Environment("USER").Item("PATH")
'WScript.echo Path
pos=InStr(Path,"OpenSG")
'WScript.echo pos
If pos = 0 Then
	Path = Path & ";" & osgpath
	WScript.echo "Added " & osgpath & " to your PATH environment."
	'WScript.echo Path
	WSHShell.Environment("USER").Item("PATH") = Path
Else
	bpos=InStrRev(Path,";",pos)+1
	epos=InStr(pos,Path,";")
	If epos = 0 Then
		epos = Len(Path)+1
	End If
	'WScript.echo bpos, epos
	oldpath=Mid(Path,bpos,epos-bpos)
	'WScript.echo oldpath
	If oldpath=osgpath Then
		WScript.echo "OpenSG path already current, not changed."	
	Else
		WScript.echo "Replaced OpenSG path " & oldpath & " with " & osgpath & "."
		newpath = Replace(Path,oldpath,osgpath)
		WSHShell.Environment("USER").Item("PATH") = newpath
	End If
End If
