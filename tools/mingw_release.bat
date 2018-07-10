@ECHO OFF
REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
mingw32-make release
IF NOT EXIST "./release/QxOrm.dll" GOTO END
cd "./release/"
copy "QxOrm.lib" "../lib/"
copy "QxOrm.dll" "../lib/"
copy "QxOrm.lib" "../test/_bin/"
copy "QxOrm.dll" "../test/_bin/"
cd "../"
REM -- BUILD TEST DLL1 --
cd "./test/dll1/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/dll1.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/dll2.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/exe.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../qxBlog/"
qmake
mingw32-make release
IF NOT EXIST "../_bin/qxBlog.exe" GOTO END
copy "qxBlog.sqlite" "../_bin/"
:END
pause
