#!/bin/bash

echo "--- Copy environment variables ---"

mkdir -vp $QX_SCRIPTS

export -p | grep -e "QX_" -e "CMAKE_" | sed "s/declare -x/export/g" > $QX_SCRIPTS/env_var_qx.sh
export -p | grep -e "QX_" -e "CMAKE_" | sed "s/declare -x/export/g" >> $QX_HOME/.profile
export -p | grep -e "QX_" -e "CMAKE_" | sed "s/declare -x/export/g" >> /root/.profile

if [ -f $QX_DIR/.vscode/launch.json ]; then
   sed -i 's~%%QX_DIR%%~'"$QX_DIR"'~g' $QX_DIR/.vscode/launch.json
   sed -i 's~%%QX_PORT_DEBUG%%~'"$QX_PORT_DEBUG"'~g' $QX_DIR/.vscode/launch.json
fi

if [ -f $QX_DIR/.vscode/tasks.json ]; then
   sed -i 's~%%QX_CMAKE_OPTIONS_DEBUG%%~'"$QX_CMAKE_OPTIONS_DEBUG"'~g' $QX_DIR/.vscode/tasks.json
fi

exit 0
