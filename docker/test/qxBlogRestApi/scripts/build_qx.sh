#!/bin/bash

if [ "$1" == "Debug" ];
then
   QX_DIR_SUFFIX=debug
else
   QX_DIR_SUFFIX=release
fi

if [ -z "${QX_DIR}" ];
then
   QX_USER=qxorm
   QX_DIR=/home/$QX_USER
fi

export CMAKE_CONFIG=$1
export CMAKE_OPTIONS=$2
export CMAKE_BUILD_PARALLEL_LEVEL=2

cd $QX_DIR/test/build/$QX_DIR_SUFFIX/
cmake ../.. $CMAKE_OPTIONS
cmake --build . --config $CMAKE_CONFIG

exit 0
