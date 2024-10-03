#!/bin/bash

echo "--- Install Visual Studio Code Server and extensions ---"
sh $QX_DIR/scripts/download-vs-code.sh "linux" "x64" --extensions "ms-vscode.cpptools ms-vscode.cmake-tools"
cp -R /root/.vscode-server $QX_DIR/.vscode-server/
cp -R /root/.vscode $QX_DIR/.vscode/
chown -R $QX_USER:$QX_USER $QX_DIR/.vscode-server
chown -R $QX_USER:$QX_USER $QX_DIR/.vscode

exit 0
