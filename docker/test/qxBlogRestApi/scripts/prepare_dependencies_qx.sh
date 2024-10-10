#!/bin/bash

echo "--- Find all QxOrm project example dependencies and copy them ---"

QX_BIN_DIR=$QX_DIR/test/_bin
cd $QX_BIN_DIR

mkdir -vp $QX_BIN_DIR/libs
mkdir -vp $QX_BIN_DIR/sqldrivers
mkdir -vp $QX_BIN_DIR/tls

cp /usr/lib/x86_64-linux-gnu/qt6/plugins/sqldrivers/libqsqlite.so $QX_BIN_DIR/sqldrivers/
cp /usr/lib/x86_64-linux-gnu/qt6/plugins/tls/* $QX_BIN_DIR/tls/

ldd qxBlogRestApi | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_BIN_DIR/libs
ldd sqldrivers/libqsqlite.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_BIN_DIR/libs
ldd tls/libqcertonlybackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_BIN_DIR/libs
ldd tls/libqopensslbackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' $QX_BIN_DIR/libs

exit 0
