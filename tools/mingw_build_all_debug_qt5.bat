REM -- QT ENVIRONMENT VARIABLES --
set MINGW_DIR=D:\Dvlp\_Libs\Qt\5.4.1_MINGW\Tools\mingw491_32
set QT_DIR=%QT5_MINGW%
set PATH=%MINGW_DIR%\bin;%QT_DIR%\bin;%PATH%
REM -- BOOST ENVIRONMENT VARIABLES --
set BOOST_INCLUDE=D:\Dvlp\_Libs\Boost\1_57\include
set BOOST_LIB=D:\Dvlp\_Libs\Boost\1_57\lib_shared
set BOOST_LIB_SERIALIZATION_DEBUG=libboost_serialization-mgw49-mt-d-1_57
set BOOST_LIB_SERIALIZATION_RELEASE=libboost_serialization-mgw49-mt-1_57
set BOOST_LIB_WIDE_SERIALIZATION_DEBUG=libboost_wserialization-mgw49-mt-d-1_57
set BOOST_LIB_WIDE_SERIALIZATION_RELEASE=libboost_wserialization-mgw49-mt-1_57
REM -- MAKE OPTIONS : USE 8 CORE CPU TO REDUCE BUILD TIMES --
set MAKE_COMMAND=make -j8
REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
make debug
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
make debug
IF NOT EXIST "../../_bin/dll1d.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
make debug
IF NOT EXIST "../../_bin/dll2d.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
make debug
IF NOT EXIST "../../_bin/exed.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../../qxBlog/"
qmake
make debug
IF NOT EXIST "../_bin/qxBlogd.exe" GOTO END
REM -- BUILD TEST QXBLOG COMPOSITE KEY --
cd "../qxBlogCompositeKey/"
qmake
make debug
IF NOT EXIST "../_bin/qxBlogCompositeKeyd.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVICE --
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make debug
IF NOT EXIST "../../_bin/qxServiceServerd.dll" GOTO END
qmake qxServiceClient.pro
make debug
IF NOT EXIST "../../_bin/qxServiceClientd.dll" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVER --
cd "../qxServer/"
qmake
make debug
IF NOT EXIST "../../_bin/qxServerd.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXCLIENT --
cd "../qxClient/"
qmake
make debug
IF NOT EXIST "../../_bin/qxClientd.exe" GOTO END
:END
pause
