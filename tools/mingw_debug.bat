@ECHO OFF
REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
mingw32-make debug
IF NOT EXIST "./debug/QxOrmd.dll" GOTO END
cd "./debug/"
copy "QxOrmd.lib" "../lib/"
copy "QxOrmd.dll" "../lib/"
copy "QxOrmd.lib" "../test/_bin/"
copy "QxOrmd.dll" "../test/_bin/"
cd "../"
REM -- BUILD TEST DLL1 --
cd "./test/dll1/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/dll1d.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/dll2d.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/exed.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../qxBlog/"
qmake
mingw32-make debug
IF NOT EXIST "../_bin/qxBlogd.exe" GOTO END
copy "qxBlog.sqlite" "../_bin/"
:END
pause
