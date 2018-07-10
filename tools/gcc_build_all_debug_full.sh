#!/bin/bash

if [[ $1 == "release" ]];
then
	CONFIG=release
else
	CONFIG=debug
	SUFFIX=d
fi

if [[ $2 == "full" ]] || [ -z "$2" ];
then
	QMAKEPARAMS="\"DEFINES += _QX_ENABLE_BOOST_SERIALIZATION\" \"DEFINES += _QX_ENABLE_QT_GUI\" \"DEFINES += _QX_ENABLE_QT_NETWORK\""
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
eval qmake $QMAKEPARAMS
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
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libdll1$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST DLL2 --"
cd "../dll2/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libdll2$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST EXE --"
cd "../exe/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/exe$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG --"
cd "../../qxBlog/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../_bin/qxBlog$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd "../qxBlogCompositeKey/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../_bin/qxBlogCompositeKey$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXBLOG MODEL VIEW --"
cd "../qxBlogModelView/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../_bin/qxBlogModelView$SUFFIX ];
then
   exit 1
fi

echo "-- CHECK BATCH TYPE : FULL OR MINIMAL --"
if [[ $2 == "minimal" ]];
then
   exit 0
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd "../qxClientServer/qxService"
eval qmake $QMAKEPARAMS qxServiceServer.pro
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libqxServiceServer$SUFFIX.so ];
then
   exit 1
fi
eval qmake $QMAKEPARAMS qxServiceClient.pro
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/libqxServiceClient$SUFFIX.so ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd "../qxServer/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/qxServer$SUFFIX ];
then
   exit 1
fi

echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd "../qxClient/"
eval qmake $QMAKEPARAMS
make $CONFIG $MAKEOPT
if [ ! -f ../../_bin/qxClient$SUFFIX ];
then
   exit 1
fi

exit 0
