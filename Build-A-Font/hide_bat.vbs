Set oShell = CreateObject ("Wscript.Shell") 
Dim strArgs
strArgs = "cmd /c conv_script.bat"
oShell.Run strArgs, 2, true