#!/bin/bash

# Execute SSH server (useful to debug)
if [ "$1" == "ssh" ]; then
   echo "--- Start SSH server ---"
   /usr/sbin/sshd
fi

# Execute QxOrm simple HTTP web server example
# URL : http://localhost:9642/files/test_http_server.html
echo "--- Start QxOrm simple HTTP web server ---"
./qxBlogRestApi

exit 0
