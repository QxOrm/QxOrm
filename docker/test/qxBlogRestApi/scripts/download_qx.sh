#!/bin/bash

echo "--- Download QxOrm library source code from GitHub ---"

mkdir -vp $QX_DIR
cd $QX_DIR
wget "$QX_URL_DOWNLOAD"
unzip -d . ./master.zip
mv ./QxOrm-master/* .
rmdir ./QxOrm-master
rm -f ./master.zip

exit 0
