qmake & nmake release
cd "./release/"
copy "QxOrm.lib" "../lib/"
if exist "QxOrm.dll" ( copy "QxOrm.dll" "../lib/" )
copy "QxOrm.lib" "../test/_bin/"
if exist "QxOrm.dll" ( copy "QxOrm.dll" "../test/_bin/" )
