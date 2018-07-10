#!/bin/bash

if [[ $1 == "release" ]];
then
	CONFIG=release
	LIBBOOSTSERIALIZATION=libboost_serialization-mt.dylib
else
	CONFIG=debug
	SUFFIX=d
	LIBBOOSTSERIALIZATION=libboost_serialization-mt-d.dylib
fi

if [ ! -f ../lib/$LIBBOOSTSERIALIZATION ]
then
   echo "You must copy '$LIBBOOSTSERIALIZATION' in 'QxOrm/lib/' before launching this script."
   exit 0
fi

function testFile {
if [ ! $1 $2 ]
then
   echo "$2 Error."
   exit 1
  else 
    echo "$2 OK."
fi
}
           
clear
pwd
cd ..

echo "-- BUILD QXORM LIBRARY --"
qmake QxOrm.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ./lib/libQxOrm$SUFFIX.*
cp -R -v ./lib/libQxOrm$SUFFIX.* ./test/_bin/
cp -R -v ./lib/$LIBBOOSTSERIALIZATION ./test/_bin/
install_name_tool -id @executable_path/libQxOrm$SUFFIX.dylib ./test/_bin/libQxOrm$SUFFIX.dylib
install_name_tool -id @executable_path/$LIBBOOSTSERIALIZATION ./test/_bin/$LIBBOOSTSERIALIZATION
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./test/_bin/libQxOrm$SUFFIX.dylib

cd ./test/

echo "-- BUILD DLLSAMPLE --"
cd ./qxDllSample/dll1/
qmake dll1.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../../_bin/libdll1$SUFFIX.*
cd ../../
install_name_tool -id @executable_path/libdll1$SUFFIX.dylib ./_bin/libdll1$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/libdll1$SUFFIX.dylib
cd ./qxDllSample/dll2/
qmake dll2.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../../_bin/libdll2$SUFFIX.*
cd ../../
install_name_tool -id @executable_path/libdll2$SUFFIX.dylib ./_bin/libdll2$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/libdll2$SUFFIX.dylib
#install_name_tool -change libdll1$SUFFIX.1.dylib @executable_path/libdll1$SUFFIX.dylib ./_bin/libdll2$SUFFIX.dylib
cd ./qxDllSample/exe/
qmake exe.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../../_bin/exe$SUFFIX
cd ../../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/exe$SUFFIX


echo "-- BUILD TEST QXBLOG --"
cd ./qxBlog/
qmake qxBlog.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../_bin/qxBlog$SUFFIX
cd ../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/qxBlog$SUFFIX

echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd ./qxBlogCompositeKey/
qmake qxBlog.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../_bin/qxBlogCompositeKey$SUFFIX
cd ../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/qxBlogCompositeKey$SUFFIX

echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd ./qxClientServer/qxService
qmake qxServiceServer.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../../_bin/libqxServiceServer$SUFFIX.*
install_name_tool -id @executable_path/../Frameworks/libqxServiceServer$SUFFIX.dylib ../../_bin/libqxServiceServer$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ../../_bin/libqxServiceServer$SUFFIX.dylib
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ../../_bin/libqxServiceServer$SUFFIX.dylib
qmake qxServiceClient.pro -r -spec macx-g++
make -w $CONFIG
testFile -f ../../_bin/libqxServiceClient$SUFFIX.*
install_name_tool -id @executable_path/../Frameworks/libqxServiceClient$SUFFIX.dylib ../../_bin/libqxServiceClient$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ../../_bin/libqxServiceClient$SUFFIX.dylib
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ../../_bin/libqxServiceClient$SUFFIX.dylib
cd ../../

echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd ./qxClientServer/qxServer/
qmake qxServer.pro -r -spec macx-g++
make -w $CONFIG
testFile -d ../../_bin/qxServer$SUFFIX.app
cd ../../
mkdir -p ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/
cp -R -v ./_bin/libQxOrm$SUFFIX.* ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/
install_name_tool -id @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/libQxOrm$SUFFIX.dylib
install_name_tool -change @executable_path/$LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/libQxOrm$SUFFIX.dylib
cp -R -v ./_bin/$LIBBOOSTSERIALIZATION ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/
install_name_tool -id @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/$LIBBOOSTSERIALIZATION
mv -v ./_bin/libqxServiceServer$SUFFIX.* ./_bin/qxServer$SUFFIX.app/Contents/Frameworks/
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxServer$SUFFIX.app/Contents/MacOS/qxServer$SUFFIX
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ./_bin/qxServer$SUFFIX.app/Contents/MacOS/qxServer$SUFFIX

echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd ./qxClientServer/qxClient/
qmake qxClient.pro -r -spec macx-g++
make -w $CONFIG
testFile -d ../../_bin/qxClient$SUFFIX.app
cd ../../
mkdir -p ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/
cp -R -v ./_bin/libQxOrm$SUFFIX.* ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/
install_name_tool -id @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/libQxOrm$SUFFIX.dylib
install_name_tool -change @executable_path/$LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/libQxOrm$SUFFIX.dylib
cp -R -v ./_bin/$LIBBOOSTSERIALIZATION ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/
install_name_tool -id @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/$LIBBOOSTSERIALIZATION
mv -v ./_bin/libqxServiceClient$SUFFIX.* ./_bin/qxClient$SUFFIX.app/Contents/Frameworks/
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ./_bin/qxClient$SUFFIX.app/Contents/MacOS/qxClient$SUFFIX
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ./_bin/qxClient$SUFFIX.app/Contents/MacOS/qxClient$SUFFIX
cd ../

echo "Success !"
