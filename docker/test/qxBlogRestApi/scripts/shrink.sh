#!/bin/bash

echo "--- Remove duplicate files ---"

for f in $QX_HOME/app/libs/*.*; do
   f=$(basename ${f})
   if [[ -n "$(find /usr/* -name $f)" ]]; then
      echo "Remove file $QX_HOME/app/libs/$f"
      rm -f $QX_HOME/app/libs/$f
   fi
done

exit 0
