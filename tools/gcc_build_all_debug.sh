#!/bin/bash

if [[ $1 == "release" ]];
then
	CONFIG=release
else
	CONFIG=debug
	SUFFIX=d
fi

clear
pwd

echo "-- BUILD QXORM LIBRARY --"
cd "../"
qmake
make $CONFIG
if [ ! -f ./lib/libQxOrm$SUFFIX.so ];
then
   exit 1
fi
cd "./lib/"
cp libQxOrm$SUFFIX.* "../test/_bin/"
cd "../"

echo "-- BUILD TEST DLL1 --"
cd "./test/qxDllSample/dll1/"
qmake
make $CONFIG
if [ ! -f ../../_bin/libdll1$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST DLL2 --"
cd "../dll2/"
qmake
make $CONFIG
if [ ! -f ../../_bin/libdll2$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST EXE --"
cd "../exe/"
qmake
make $CONFIG
if [ ! -f ../../_bin/exe$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG --"
cd "../../qxBlog/"
qmake
make $CONFIG
if [ ! -f ../_bin/qxBlog$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd "../qxBlogCompositeKey/"
qmake
make $CONFIG
if [ ! -f ../_bin/qxBlogCompositeKey$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make $CONFIG
if [ ! -f ../../_bin/libqxServiceServer$SUFFIX.so ];
then
   exit 1
fi
qmake qxServiceClient.pro
make $CONFIG
if [ ! -f ../../_bin/libqxServiceClient$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd "../qxServer/"
qmake
make $CONFIG
if [ ! -f ../../_bin/qxServer$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd "../qxClient/"
qmake
make $CONFIG
if [ ! -f ../../_bin/qxClient$SUFFIX ];
then
   exit 1
fi

exit 0
