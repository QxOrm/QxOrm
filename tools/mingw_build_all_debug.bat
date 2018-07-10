REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
mingw32-make debug
IF NOT EXIST "./debug/QxOrmd.dll" GOTO END
cd "./debug/"
copy "libQxOrmd.a" "../lib/"
if exist "QxOrmd.dll" ( copy "QxOrmd.dll" "../lib/" )
copy "libQxOrmd.a" "../test/_bin/"
if exist "QxOrmd.dll" ( copy "QxOrmd.dll" "../test/_bin/" )
cd "../"
REM -- BUILD TEST DLL1 --
cd "./test/qxDllSample/dll1/"
qmake
mingw32-make debug
IF NOT EXIST "../../_bin/dll1d.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
mingw32-make debug
IF NOT EXIST "../../_bin/dll2d.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
mingw32-make debug
IF NOT EXIST "../../_bin/exed.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../../qxBlog/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/qxBlogd.exe" GOTO END
REM -- BUILD TEST QXBLOG COMPOSITE KEY --
cd "../qxBlogCompositeKey/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/qxBlogCompositeKeyd.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVICE --
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
mingw32-make debug
IF NOT EXIST "../../_bin/qxServiceServerd.dll" GOTO END
qmake qxServiceClient.pro
mingw32-make debug
IF NOT EXIST "../../_bin/qxServiceClientd.dll" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVER --
cd "../qxServer/"
qmake
mingw32-make debug
IF NOT EXIST "../../_bin/qxServerd.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXCLIENT --
cd "../qxClient/"
qmake
mingw32-make debug
IF NOT EXIST "../../_bin/qxClientd.exe" GOTO END
:END
pause
