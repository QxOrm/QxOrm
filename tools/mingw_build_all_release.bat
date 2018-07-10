REM -- QT ENVIRONMENT VARIABLES --
set QT_DIR=%QT4_MINGW%
set PATH=%QT_DIR%\bin;%PATH%
REM -- BOOST ENVIRONMENT VARIABLES --
set BOOST_INCLUDE=D:\Dvlp\_Libs\Boost\1_57\include
set BOOST_LIB=D:\Dvlp\_Libs\Boost\1_57\lib_shared
set BOOST_LIB_SERIALIZATION_DEBUG=libboost_serialization-mgw45-mt-d-1_57
set BOOST_LIB_SERIALIZATION_RELEASE=libboost_serialization-mgw45-mt-1_57
set BOOST_LIB_WIDE_SERIALIZATION_DEBUG=libboost_wserialization-mgw45-mt-d-1_57
set BOOST_LIB_WIDE_SERIALIZATION_RELEASE=libboost_wserialization-mgw45-mt-1_57
REM -- MAKE OPTIONS : USE 8 CORE CPU TO REDUCE BUILD TIMES --
set MAKE_COMMAND=make -j8
REM -- BUILD QXORM LIBRARY --
cd "../"
qmake
make release
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
make release
IF NOT EXIST "../../_bin/dll1.dll" GOTO END
REM -- BUILD TEST DLL2 --
cd "../dll2/"
qmake
make release
IF NOT EXIST "../../_bin/dll2.dll" GOTO END
REM -- BUILD TEST EXE --
cd "../exe/"
qmake
make release
IF NOT EXIST "../../_bin/exe.exe" GOTO END
REM -- BUILD TEST QXBLOG --
cd "../../qxBlog/"
qmake
make release
IF NOT EXIST "../_bin/qxBlog.exe" GOTO END
REM -- BUILD TEST QXBLOG COMPOSITE KEY --
cd "../qxBlogCompositeKey/"
qmake
make release
IF NOT EXIST "../_bin/qxBlogCompositeKey.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVICE --
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make release
IF NOT EXIST "../../_bin/qxServiceServer.dll" GOTO END
qmake qxServiceClient.pro
make release
IF NOT EXIST "../../_bin/qxServiceClient.dll" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXSERVER --
cd "../qxServer/"
qmake
make release
IF NOT EXIST "../../_bin/qxServer.exe" GOTO END
REM -- BUILD TEST QXCLIENTSERVER QXCLIENT --
cd "../qxClient/"
qmake
make release
IF NOT EXIST "../../_bin/qxClient.exe" GOTO END
:END
pause
