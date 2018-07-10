qmake & nmake debug
cd "./debug/"
copy "QxOrmd.lib" "../lib/"
if exist "QxOrmd.dll" ( copy "QxOrmd.dll" "../lib/" )
copy "QxOrmd.lib" "../test/_bin/"
if exist "QxOrmd.dll" ( copy "QxOrmd.dll" "../test/_bin/" )
