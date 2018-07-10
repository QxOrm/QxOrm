REM -- BATCH PARAMETERS --
set BATCH_TYPE=full
set MSVC_CONFIG=Debug
set MSVC_PLATFORM=Win32
set LIB_SUFFIX=d
if "%1"=="release" set MSVC_CONFIG=Release
if "%1"=="release" set LIB_SUFFIX=
if "%2"=="x64" set MSVC_PLATFORM=x64
if "%3"=="minimal" set BATCH_TYPE=%3
if "%BATCH_TYPE%"=="full" set QXORM_QMAKE_PARAMS="DEFINES += _QX_ENABLE_BOOST_SERIALIZATION" "DEFINES += _QX_ENABLE_QT_GUI" "DEFINES += _QX_ENABLE_QT_NETWORK" "CONFIG += c++11" "DEFINES += _QX_CPP_11_SMART_PTR" "DEFINES += _QX_CPP_11_CONTAINER" "DEFINES += _QX_CPP_11_TUPLE"

REM -- QT ENVIRONMENT VARIABLES --
set QT_DIR=%QT5_MSVC2012_32B%
if "%2"=="x64" set QT_DIR=%QT5_MSVC2012_64B%
set PATH=%QT_DIR%\bin;%PATH%

REM -- BOOST ENVIRONMENT VARIABLES --
set BOOST_INCLUDE=%BOOST_DIR%\include
set BOOST_LIB=%BOOST_DIR%\lib_shared
if "%2"=="x64" set BOOST_LIB=%BOOST_DIR%\lib_shared_64b
set BOOST_LIB_SERIALIZATION_DEBUG=boost_serialization-vc110-mt-gd-1_57
set BOOST_LIB_SERIALIZATION_RELEASE=boost_serialization-vc110-mt-1_57
set BOOST_LIB_WIDE_SERIALIZATION_DEBUG=boost_wserialization-vc110-mt-gd-1_57
set BOOST_LIB_WIDE_SERIALIZATION_RELEASE=boost_wserialization-vc110-mt-1_57

REM -- LOAD MSVC ENVIRONMENT VARIABLES --
IF EXIST "%PROGRAMFILES(X86)%" SET PROGFILES32=%PROGRAMFILES(X86)%
IF NOT EXIST "%PROGRAMFILES(X86)%" SET PROGFILES32=%PROGRAMFILES%
CALL "%PROGFILES32%\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86
SET CL=/MP
CD "..\"

REM -- BUILD QXORM LIBRARY --
msbuild ".\QxOrm.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\lib\QxOrm%LIB_SUFFIX%.dll" GOTO END

REM -- BUILD TEST DLL SAMPLE --
msbuild ".\test\qxDllSample\test.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\exe%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG --
msbuild ".\test\qxBlog\qxBlog.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlog%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG COMPOSITE KEY --
msbuild ".\test\qxBlogCompositeKey\qxBlog.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogCompositeKey%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXBLOG MODEL VIEW --
msbuild ".\test\qxBlogModelView\qxBlog.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogModelView%LIB_SUFFIX%.exe" GOTO END

REM -- CHECK BATCH TYPE : FULL OR MINIMAL --
IF "%BATCH_TYPE%"=="minimal" GOTO END

REM -- BUILD TEST QXBLOG C++11 --
msbuild ".\test\qxBlogCpp11\qxBlog.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxBlogCpp11%LIB_SUFFIX%.exe" GOTO END

REM -- BUILD TEST QXCLIENTSERVER --
msbuild ".\test\qxClientServer\qxClient\qxClient.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxClient%LIB_SUFFIX%.exe" GOTO END
msbuild ".\test\qxClientServer\qxServer\qxServer.sln" /p:Configuration="%MSVC_CONFIG%" /p:Platform="%MSVC_PLATFORM%" /t:build /nologo /v:detailed
IF NOT EXIST ".\test\_bin\qxServer%LIB_SUFFIX%.exe" GOTO END

REM -- BATCH FINISHED --
:END
PAUSE
