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

if [[ $2 == "full" ]] || [ -z "$2" ];
then
	QMAKEPARAMS="\"DEFINES += _QX_ENABLE_BOOST_SERIALIZATION\" \"DEFINES += _QX_ENABLE_QT_GUI\" \"DEFINES += _QX_ENABLE_QT_NETWORK\""
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

echo "-- BOOST ENVIRONMENT VARIABLES --"
export BOOST_INCLUDE=/usr/include
export BOOST_LIB=/usr/lib
export BOOST_LIB_SERIALIZATION_DEBUG=boost_serialization-mt-d
export BOOST_LIB_SERIALIZATION_RELEASE=boost_serialization-mt
export BOOST_LIB_WIDE_SERIALIZATION_DEBUG=boost_wserialization-mt-d
export BOOST_LIB_WIDE_SERIALIZATION_RELEASE=boost_wserialization-mt

echo "-- MAKE OPTIONS : USE 8 CORE CPU TO REDUCE BUILD TIMES --"
MAKEOPT=-j8

echo "-- BUILD QXORM LIBRARY --"
eval qmake $QMAKEPARAMS QxOrm.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ./lib/libQxOrm$SUFFIX.*
cp -R -v ./lib/libQxOrm$SUFFIX.* ./test/_bin/
cp -R -v ./lib/$LIBBOOSTSERIALIZATION ./test/_bin/
install_name_tool -id @executable_path/libQxOrm$SUFFIX.dylib ./test/_bin/libQxOrm$SUFFIX.dylib
install_name_tool -id @executable_path/$LIBBOOSTSERIALIZATION ./test/_bin/$LIBBOOSTSERIALIZATION
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./test/_bin/libQxOrm$SUFFIX.dylib

cd ./test/

echo "-- BUILD DLLSAMPLE --"
cd ./qxDllSample/dll1/
eval qmake $QMAKEPARAMS dll1.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../../_bin/libdll1$SUFFIX.*
cd ../../
install_name_tool -id @executable_path/libdll1$SUFFIX.dylib ./_bin/libdll1$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/libdll1$SUFFIX.dylib
cd ./qxDllSample/dll2/
eval qmake $QMAKEPARAMS dll2.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../../_bin/libdll2$SUFFIX.*
cd ../../
install_name_tool -id @executable_path/libdll2$SUFFIX.dylib ./_bin/libdll2$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/libdll2$SUFFIX.dylib
#install_name_tool -change libdll1$SUFFIX.1.dylib @executable_path/libdll1$SUFFIX.dylib ./_bin/libdll2$SUFFIX.dylib
cd ./qxDllSample/exe/
eval qmake $QMAKEPARAMS exe.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../../_bin/exe$SUFFIX
cd ../../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/exe$SUFFIX

echo "-- BUILD TEST QXBLOG --"
cd ./qxBlog/
eval qmake $QMAKEPARAMS qxBlog.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../_bin/qxBlog$SUFFIX
cd ../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/qxBlog$SUFFIX

echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd ./qxBlogCompositeKey/
eval qmake $QMAKEPARAMS qxBlog.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../_bin/qxBlogCompositeKey$SUFFIX
cd ../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/qxBlogCompositeKey$SUFFIX

echo "-- BUILD TEST QXBLOG MODEL VIEW --"
cd ./qxBlogModelView/
eval qmake $QMAKEPARAMS qxBlog.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../_bin/qxBlogModelView$SUFFIX
cd ../
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/$LIBBOOSTSERIALIZATION ./_bin/qxBlogModelView$SUFFIX

echo "-- CHECK BATCH TYPE : FULL OR MINIMAL --"
if [[ $2 == "minimal" ]];
then
   exit 0
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd ./qxClientServer/qxService
eval qmake $QMAKEPARAMS qxServiceServer.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../../_bin/libqxServiceServer$SUFFIX.*
install_name_tool -id @executable_path/../Frameworks/libqxServiceServer$SUFFIX.dylib ../../_bin/libqxServiceServer$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ../../_bin/libqxServiceServer$SUFFIX.dylib
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ../../_bin/libqxServiceServer$SUFFIX.dylib
eval qmake $QMAKEPARAMS qxServiceClient.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
testFile -f ../../_bin/libqxServiceClient$SUFFIX.*
install_name_tool -id @executable_path/../Frameworks/libqxServiceClient$SUFFIX.dylib ../../_bin/libqxServiceClient$SUFFIX.dylib
install_name_tool -change $LIBBOOSTSERIALIZATION @executable_path/../Frameworks/$LIBBOOSTSERIALIZATION ../../_bin/libqxServiceClient$SUFFIX.dylib
install_name_tool -change @executable_path/libQxOrm$SUFFIX.dylib @executable_path/../Frameworks/libQxOrm$SUFFIX.dylib ../../_bin/libqxServiceClient$SUFFIX.dylib
cd ../../

echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd ./qxClientServer/qxServer/
eval qmake $QMAKEPARAMS qxServer.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
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
eval qmake $QMAKEPARAMS qxClient.pro -r -spec macx-g++
make -w $CONFIG $MAKEOPT
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
