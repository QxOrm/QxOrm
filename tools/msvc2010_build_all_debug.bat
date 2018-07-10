CALL "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
CD "..\"
REM -- BUILD QXORM LIBRARY --
msbuild ".\QxOrm.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\lib\QxOrmd.dll" GOTO END
REM -- BUILD TEST DLL SAMPLE --
msbuild ".\test\qxDllSample\test.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\exed.exe" GOTO END
REM -- BUILD TEST QXBLOG --
msbuild ".\test\qxBlog\qxBlog.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogd.exe" GOTO END
REM -- BUILD TEST QXBLOG COMPOSITE KEY --
msbuild ".\test\qxBlogCompositeKey\qxBlog.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogCompositeKeyd.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER --
msbuild ".\test\qxClientServer\qxClient\qxClient.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxClientd.exe" GOTO END
msbuild ".\test\qxClientServer\qxServer\qxServer.sln" /p:Configuration=Debug /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxServerd.exe" GOTO END
:END
PAUSE
