#!/bin/bash

# Execute SSH server (useful to debug)
if [ "$1" == "ssh" ]; then
   echo "--- Start SSH server ---"
   /usr/sbin/sshd
fi

# Build QxOrm library and simple HTTP web server project example
# This is useful if you mount '/home/qxorm/' as a volume and make some changes in the source code
# So the container will always execute up-to-date release version
if [ "$2" == "build" ]; then
   echo "--- Build QxOrm library and simple HTTP web server ---"
   su $QX_USER -c "$QX_DIR/scripts/build_qx.sh $CMAKE_CONFIG $CMAKE_OPTIONS"
fi

# Execute QxOrm simple HTTP web server example
# URL : http://localhost:9642/files/test_http_server.html
echo "--- Start QxOrm simple HTTP web server ---"
./qxBlogRestApi

exit 0
