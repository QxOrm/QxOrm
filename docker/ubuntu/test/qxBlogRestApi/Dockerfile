# ----------------------------------------------------------------------
# This Docker file creates a Docker image based on latest Ubuntu version
# This Docker file installs a C++ development environment with gcc, cmake, Qt and builds QxOrm library (https://www.qxorm.com/) from latest QxOrm source code
# 
# QxOrm is a C++ library based on Qt framework, its main features are : ORM persistence, serialization, reflection, introspection, JSON API, HTTP web server
# QxOrm library supports most common databases like SQLite, MySQL, PostgreSQL, Oracle, MS SQL Server, MongoDB, MariaDB
# QxOrm library documentation : https://www.qxorm.com/qxorm_en/manual.html
# 
# The generated Docker image will execute an example project based on QxOrm library
# The QxOrm example project is a simple HTTP web server and uses QxOrm JSON API to send requests to a SQLite database
# More details about the example project 'qxBlogRestApi' : https://github.com/QxOrm/QxOrm/tree/master/test/qxBlogRestApi
# 
# To test this Docker file and build/run the Docker container, execute the following commands :
#    cd <path_to_this_docker_file>
#    docker build -t qxorm/ubuntu-with-qxorm-test-qxblogrestapi .
#    docker run --rm -itd -p 9642:9642 qxorm/ubuntu-with-qxorm-test-qxblogrestapi
# 
# Then, on your host machine, open a web browser and go to URL :
#    http://localhost:9642/files/test_http_server.html
# ----------------------------------------------------------------------

# ------------------------------------------------
# Start with latest version of Ubuntu Docker image
FROM ubuntu:latest AS base

# -----------------------
# QxOrm library meta-data
LABEL website="https://www.qxorm.com/"
LABEL email="contact@qxorm.com"
LABEL author="Lionel Marty"

# ---------------------------
# Create a 'qxorm' user/group
RUN groupadd -g 1987 qxorm && \
    useradd -m -u 1987 -g qxorm qxorm && \
    echo "qxorm:qxorm" | chpasswd

# ----------------------------------------------------------
# Start a new Docker image stage to install all requirements
FROM base AS builder

# ---------------------------------------------------------------
# Define environment variable to install by default Qt6 framework
ENV QT_VERSION_MAJOR=6

# -----------------------------
# Install on the Docker image :
# - 'build-essential' to get gcc compiler
# - 'qtX-base-dev' to install Qt framework (by default Qt6, but you can install Qt5 overriding environment variable 'QT_VERSION_MAJOR')
# - 'wget' and 'unzip' to download and extract QxOrm package
# - 'openssh-server' to connect via SSH, useful to debug
# - 'cmake' to build QxOrm library
RUN apt update -y \
    && apt upgrade -y \
    && apt install -y \
      wget \
      unzip \
      openssh-server \
      build-essential \
      qt$QT_VERSION_MAJOR-base-dev \
      cmake \
    && apt clean -y \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------
# Download QxOrm library source code from GitHub
USER qxorm
WORKDIR /home/qxorm/src/
ENV QXORM_URL_DOWNLOAD="https://github.com/QxOrm/QxOrm/archive/refs/heads/master.zip"
RUN wget "$QXORM_URL_DOWNLOAD"
RUN unzip -d . ./master.zip
RUN mv ./QxOrm-master/* .
RUN rmdir ./QxOrm-master
RUN rm -f ./master.zip

# --------------------------------------
# Define environment variables for cmake
ENV CMAKE_OPTIONS="-DCMAKE_INSTALL_PREFIX=/usr -D_QX_ENABLE_QT_NETWORK=1 -D_QX_UNITY_BUILD=1 -D_QX_NO_GUI=1"
ENV CMAKE_CONFIG="Release"

# -------------------------------
# Build QxOrm library using cmake
WORKDIR /home/qxorm/src/build/
RUN cmake .. $CMAKE_OPTIONS
RUN cmake --build . --config $CMAKE_CONFIG

USER root
RUN cmake --install . --config $CMAKE_CONFIG
USER qxorm

# -------------------------------------------------------------------------------
# Build QxOrm library example project with 'QxHttpServer' and 'QxRestApi' modules
# Documentation about 'QxHttpServer' module : https://www.qxorm.com/qxorm_en/manual.html#manual_96
# Documentation about 'QxRestApi' module : https://www.qxorm.com/qxorm_en/manual.html#manual_97
WORKDIR /home/qxorm/src/test/qxBlogRestApi/build/
RUN cmake .. $CMAKE_OPTIONS
RUN cmake --build . --config $CMAKE_CONFIG

# ---------------------------------------------------------
# Find all QxOrm project example dependencies and copy them
WORKDIR /home/qxorm/src/test/_bin/libs
WORKDIR /home/qxorm/src/test/_bin/sqldrivers
WORKDIR /home/qxorm/src/test/_bin/tls
WORKDIR /home/qxorm/src/test/_bin
RUN cp /usr/lib/x86_64-linux-gnu/qt6/plugins/sqldrivers/libqsqlite.so /home/qxorm/src/test/_bin/sqldrivers/
RUN cp /usr/lib/x86_64-linux-gnu/qt6/plugins/tls/* /home/qxorm/src/test/_bin/tls/
RUN ldd qxBlogRestApi | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' /home/qxorm/src/test/_bin/libs
RUN ldd sqldrivers/libqsqlite.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' /home/qxorm/src/test/_bin/libs
RUN ldd tls/libqcertonlybackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' /home/qxorm/src/test/_bin/libs
RUN ldd tls/libqopensslbackend.so | awk '/=>/ {print $3}' | xargs -I '{}' cp -v '{}' /home/qxorm/src/test/_bin/libs

# ------------------------------------------
# Start SSH server service (useful to debug)
# To connect via SSH : ssh qxorm@localhost -p <port_bound_to_22>
USER root
EXPOSE 22
RUN service ssh start

# --------------------------------------------
# Execute QxOrm simple HTTP web server example
# On your host machine, open a web browser and go to URL : http://localhost:9642/files/test_http_server.html
EXPOSE 9642
WORKDIR /home/qxorm/src/test/_bin
COPY entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
CMD [ "ssh" ]

# --------------------------------------------------------------------------------------------------------
# Start a new stage to create a minimal Docker image with just QxOrm library and its dependencies binaries
# To stop the image generation here : docker build --target builder -t qxorm/ubuntu-with-qxorm-test-qxblogrestapi .
FROM base AS exec

# -------------------------
# Install SSL/TLS libraries
RUN apt update -y \
    && apt upgrade -y \
    && apt install -y \
      libssl-dev \
    && apt clean -y \
    && rm -rf /var/lib/apt/lists/*

# ---------------------------------------
# Copy QxOrm library and its dependencies
WORKDIR /home/qxorm/test
COPY --from=builder /home/qxorm/src/test/_bin/ /home/qxorm/test/

# --------------------------------------------
# Execute QxOrm simple HTTP web server example
# On your host machine, open a web browser and go to URL : http://localhost:9642/files/test_http_server.html
ENV LD_LIBRARY_PATH=/home/qxorm/test/libs:$LD_LIBRARY_PATH
EXPOSE 9642
COPY entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
