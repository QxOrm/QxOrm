REM -- BATCH PARAMETERS --
set BATCH_TYPE=full
set MSVC_CONFIG=Debug
set LIB_SUFFIX=d
if "%1"=="release" set MSVC_CONFIG=Release
if "%1"=="release" set LIB_SUFFIX=
if "%2"=="minimal" set BATCH_TYPE=%2
if "%BATCH_TYPE%"=="full" set QXORM_QMAKE_PARAMS="DEFINES += _QX_ENABLE_BOOST_SERIALIZATION" "DEFINES += _QX_ENABLE_QT_GUI" "DEFINES += _QX_ENABLE_QT_NETWORK"

REM -- QT ENVIRONMENT VARIABLES --
set QT_DIR=%QT4_MSVC2008%
set PATH=%QT_DIR%\bin;%PATH%

REM -- BOOST ENVIRONMENT VARIABLES --
set BOOST_INCLUDE=%BOOST_DIR%\include
set BOOST_LIB=%BOOST_DIR%\lib_shared
set BOOST_LIB_SERIALIZATION_DEBUG=boost_serialization-vc90-mt-gd-1_57
set BOOST_LIB_SERIALIZATION_RELEASE=boost_serialization-vc90-mt-1_57
set BOOST_LIB_WIDE_SERIALIZATION_DEBUG=boost_wserialization-vc90-mt-gd-1_57
set BOOST_LIB_WIDE_SERIALIZATION_RELEASE=boost_wserialization-vc90-mt-1_57

REM -- LOAD MSVC ENVIRONMENT VARIABLES --
IF EXIST "%PROGRAMFILES(X86)%" SET PROGFILES32=%PROGRAMFILES(X86)%
IF NOT EXIST "%PROGRAMFILES(X86)%" SET PROGFILES32=%PROGRAMFILES%
CALL "%PROGFILES32%\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
SET CL=/MP
CD "..\"

REM -- BUILD QXORM LIBRARY --
msbuild ".\QxOrm.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\lib\QxOrm%LIB_SUFFIX%.dll" GOTO END

REM -- BUILD TEST DLL SAMPLE --
msbuild ".\test\qxDllSample\test.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\exe%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG --
msbuild ".\test\qxBlog\qxBlog.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlog%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG COMPOSITE KEY --
msbuild ".\test\qxBlogCompositeKey\qxBlog.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogCompositeKey%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG MODEL VIEW --
msbuild ".\test\qxBlogModelView\qxBlog.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogModelView%LIB_SUFFIX%.exe" GOTO END

REM -- CHECK BATCH TYPE : FULL OR MINIMAL --
IF "%BATCH_TYPE%"=="minimal" GOTO END

REM -- BUILD TEST QXCLIENTSERVER --
msbuild ".\test\qxClientServer\qxClient\qxClient.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxClient%LIB_SUFFIX%.exe" GOTO END
msbuild ".\test\qxClientServer\qxServer\qxServer.vc9.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="Win32" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxServer%LIB_SUFFIX%.exe" GOTO END

REM -- BATCH FINISHED --
:END
PAUSE
