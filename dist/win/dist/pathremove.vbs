' Append the OSGPath to the PATH,
' based on regread.vbs (even though not much is left ;),
' downloaded from the Windows Scripting Guide
' http://www.winguides.com/scripting/

Option Explicit

Dim WSHShell, script, path, osgpath, pos, bpos, epos, oldpath, newpath
script=WScript.ScriptFullName 
osgpath=replace( script, "pathremove.vbs", "lib" )
'WScript.echo osgpath
Set WSHShell = CreateObject("WScript.Shell")
Path = WSHShell.Environment("USER").Item("PATH")
'WScript.echo Path
pos=InStr(Path,osgpath)
'WScript.echo pos
If pos <> 0 Then
	bpos=InStrRev(Path,";",pos)+1
	epos=InStr(pos,Path,";")
	If epos = 0 Then
		epos = Len(Path)+1
	Else
		osgpath = osgpath & ";"
	End If
	'WScript.echo bpos, epos
	'WScript.echo osgpath
	WScript.echo "Removed OpenSG path " & osgpath & " from your PATH environment."
	newpath = Replace(Path,osgpath,"")
	If Right(newpath,1) = ";" Then
		newpath = Left(newpath, Len(newpath)-1)
	End If
	'WScript.echo newpath
	WSHShell.Environment("USER").Item("PATH") = newpath
Else
	'WScript.echo Path
End If
