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
cd "../"
qmake
make $CONFIG $MAKEOPT
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
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libdll1$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST DLL2 --"
cd "../dll2/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libdll2$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST EXE --"
cd "../exe/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/exe$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG --"
cd "../../qxBlog/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../_bin/qxBlog$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd "../qxBlogCompositeKey/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../_bin/qxBlogCompositeKey$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libqxServiceServer$SUFFIX.so ];
then
   exit 1
fi
qmake qxServiceClient.pro
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libqxServiceClient$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd "../qxServer/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/qxServer$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd "../qxClient/"
qmake
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/qxClient$SUFFIX ];
then
   exit 1
fi

exit 0
