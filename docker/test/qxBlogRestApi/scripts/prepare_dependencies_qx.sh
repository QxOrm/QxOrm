#!/bin/bash

echo "--- Find all QxOrm project example dependencies and copy them ---"

cd $QX_APP_PATH

mkdir -vp $QX_APP_PATH/libs
mkdir -vp $QX_APP_PATH/sqldrivers
mkdir -vp $QX_APP_PATH/tls

cp /usr/lib/x86_64-linux-gnu/qt6/plugins/sqldrivers/libqsqlite.so $QX_APP_PATH/sqldrivers/
cp /usr/lib/x86_64-linux-gnu/qt6/plugins/tls/* $QX_APP_PATH/tls/

ldd $QX_APP_NAME | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_APP_PATH/libs
ldd sqldrivers/libqsqlite.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_APP_PATH/libs
ldd tls/libqcertonlybackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_APP_PATH/libs
ldd tls/libqopensslbackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_APP_PATH/libs

exit 0
