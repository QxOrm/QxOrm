REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
mingw32-make release
IF NOT EXIST "./release/QxOrm.dll" GOTO END
cd "./release/"
copy "libQxOrm.a" "../lib/"
if exist "QxOrm.dll" ( copy "QxOrm.dll" "../lib/" )
copy "libQxOrm.a" "../test/_bin/"
if exist "QxOrm.dll" ( copy "QxOrm.dll" "../test/_bin/" )
cd "../"
REM -- BUILD TEST DLL1 --
cd "./test/qxDllSample/dll1/"
qmake
mingw32-make release
IF NOT EXIST "../../_bin/dll1.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
mingw32-make release
IF NOT EXIST "../../_bin/dll2.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
mingw32-make release
IF NOT EXIST "../../_bin/exe.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../../qxBlog/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/qxBlog.exe" GOTO END
REM -- BUILD TEST QXBLOG COMPOSITE KEY --
cd "../qxBlogCompositeKey/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/qxBlogCompositeKey.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVICE --
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
mingw32-make release
IF NOT EXIST "../../_bin/qxServiceServer.dll" GOTO END
qmake qxServiceClient.pro
mingw32-make release
IF NOT EXIST "../../_bin/qxServiceClient.dll" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVER --
cd "../qxServer/"
qmake
mingw32-make release
IF NOT EXIST "../../_bin/qxServer.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXCLIENT --
cd "../qxClient/"
qmake
mingw32-make release
IF NOT EXIST "../../_bin/qxClient.exe" GOTO END
:END
pause
