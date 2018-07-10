#!/bin/bash
clear
pwd
echo "-- BUILD QXORM LIBRARY --"
cd "../"
qmake
make release
if [ ! -f "./lib/libQxOrm.so" ];
then
   exit 1
fi
cd "./lib/"
cp "libQxOrm.so" "../test/_bin/"
cp "libQxOrm.so.1" "../test/_bin/"
cp "libQxOrm.so.1.0" "../test/_bin/"
cp "libQxOrm.so.1.0.0" "../test/_bin/"
cd "../"
echo "-- BUILD TEST DLL1 --"
cd "./test/qxDllSample/dll1/"
qmake
make release
if [ ! -f "../../_bin/libdll1.so" ];
then
   exit 1
fi
echo "-- BUILD TEST DLL2 --"
cd "../dll2/"
qmake
make release
if [ ! -f "../../_bin/libdll2.so" ];
then
   exit 1
fi
echo "-- BUILD TEST EXE --"
cd "../exe/"
qmake
make release
if [ ! -f "../../_bin/exe" ];
then
   exit 1
fi
echo "-- BUILD TEST QXBLOG --"
cd "../../qxBlog/"
qmake
make release
if [ ! -f "../_bin/qxBlog" ];
then
   exit 1
fi
echo "-- BUILD TEST QXBLOG COMPOSITE KEY --"
cd "../qxBlogCompositeKey/"
qmake
make release
if [ ! -f "../_bin/qxBlogCompositeKey" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXSERVICE --"
cd "../qxClientServer/qxService"
qmake qxServiceServer.pro
make release
if [ ! -f "../../_bin/libqxServiceServer.so" ];
then
   exit 1
fi
qmake qxServiceClient.pro
make release
if [ ! -f "../../_bin/libqxServiceClient.so" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXSERVER --"
cd "../qxServer/"
qmake
make release
if [ ! -f "../../_bin/qxServer" ];
then
   exit 1
fi
echo "-- BUILD TEST QXCLIENTSERVER QXCLIENT --"
cd "../qxClient/"
qmake
make release
if [ ! -f "../../_bin/qxClient" ];
then
   exit 1
fi
exit 0
