#!/bin/bash

echo "--- Install Visual Studio Code Server and extensions ---"
sh $QX_SCRIPTS/download-vs-code.sh "linux" "x64" --extensions "ms-vscode.cpptools ms-vscode.cmake-tools"

mkdir -vp $QX_HOME/.vscode-server
mkdir -vp $QX_HOME/.vscode

mv /root/.vscode-server/* $QX_HOME/.vscode-server/
mv /root/.vscode/* $QX_HOME/.vscode/
mv /root/code-server $QX_HOME/

for symLinkName in $(find $QX_HOME/.vscode* -type l); do
   ln -sfn "$(readlink $symLinkName | sed 's/\/root/\/home\/'"$QX_USER"'/')" "$symLinkName"
done
ln -sfn "$(readlink $QX_HOME/code-server | sed 's/\/root/\/home\/'"$QX_USER"'/')" "$QX_HOME/code-server"

chown -R $QX_USER:$QX_USER $QX_HOME/.vscode-server
chown -R $QX_USER:$QX_USER $QX_HOME/.vscode
chown -R $QX_USER:$QX_USER $QX_HOME/code-server

rm -rfv /tmp/*

exit 0
