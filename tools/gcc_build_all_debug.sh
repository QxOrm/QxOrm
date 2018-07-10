#!/bin/bash
clear
pwd
echo "-- BUILD QXORM LIBRARY --"
cd "../"
qmake
make debug
if [ ! -f "./lib/libQxOrmd.so" ];
then
   exit 1
fi
cd "./lib/"
cp "libQxOrmd.so" "../test/_bin/"
cp "libQxOrmd.so.1" "../test/_bin/"
cp "libQxOrmd.so.1.0" "../test/_bin/"
cp "libQxOrmd.so.1.0.0" "../test/_bin/"
cd "../"
echo "-- BUILD TEST DLL1 --"
cd "./test/qxDllSample/dll1/"
qmake
make debug
if [ ! -f "../../_bin/libdll1d.so" ];
then
   exit 1
fi
echo "-- BUILD TEST DLL2 --"
cd "../dll2/"
qmake
make debug
if [ ! -f "../../_bin/libdll2d.so" ];
then
   exit 1
fi
echo "-- BUILD TEST EXE --"
cd "../exe/"
qmake
make debug
if [ ! -f "../../_bin/exed" ];
then
   exit 1
fi
echo "-- BUILD TEST QXBLOG --"
cd "../../qxBlog/"
qmake
make debug
if [ ! -f "../_bin/qxBlogd" ];
then
   exit 1
fi
echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd "../qxBlogCompositeKey/"
qmake
make debug
if [ ! -f "../_bin/qxBlogCompositeKeyd" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make debug
if [ ! -f "../../_bin/libqxServiceServerd.so" ];
then
   exit 1
fi
qmake qxServiceClient.pro
make debug
if [ ! -f "../../_bin/libqxServiceClientd.so" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd "../qxServer/"
qmake
make debug
if [ ! -f "../../_bin/qxServerd" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd "../qxClient/"
qmake
make debug
if [ ! -f "../../_bin/qxClientd" ];
then
   exit 1
fi
exit 0
