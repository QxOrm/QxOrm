gitRepoFolder = "../"
gitIgnoreFile = "./gitignore_recursive.file"

Set fso = CreateObject("Scripting.FileSystemObject")
Call checkFolder(fso.GetFolder(gitRepoFolder), 999)

Sub checkFolder(folder, depth)
   If (depth > 0) Then
      For Each subFolder In folder.SubFolders
         Call checkFolder(subFolder, (depth - 1))
      Next
   End If

   folderPath = Replace(folder.Path, "\", "/")
   If (Right(folderPath, 1) <> "/") Then folderPath = (folderPath + "/")
   If (InStr(folderPath, ".git") > 0) Then Exit Sub

   If (((folder.Files.Count <= 0) And (folder.SubFolders.Count <= 0)) Or (Right(folderPath, 17) = "doc/doxygen/html/")) Then
      Call Wscript.Echo("add '.gitignore' file to folder : " + folderPath)
      Call fso.CopyFile(gitIgnoreFile, (folderPath + ".gitignore"))
   End If
End Sub
