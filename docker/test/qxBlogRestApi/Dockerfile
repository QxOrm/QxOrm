# -----------------------------------------------------------------------------------
# This Docker file creates a Docker image based on Ubuntu (latest version by default)
# This Docker file installs a C++ development environment with gcc, cmake, Qt and builds QxOrm library (https://www.qxorm.com/) from latest QxOrm source code
# 
# QxOrm is a C++ library based on Qt framework, its main features are : ORM persistence, serialization, reflection, introspection, JSON API, HTTP web server
# QxOrm library supports most common databases like SQLite, MySQL, PostgreSQL, Oracle, MS SQL Server, MongoDB, MariaDB
# QxOrm library documentation : https://www.qxorm.com/qxorm_en/manual.html
# 
# The generated Docker image will execute a container based on a QxOrm library project example
# The QxOrm project example is a simple HTTP web server and uses QxOrm JSON API to send requests to a SQLite database
# More details about the project 'qxBlogRestApi' : https://github.com/QxOrm/QxOrm/tree/master/test/qxBlogRestApi
# 
# The built Docker image can be pulled from Docker Hub :
#    https://hub.docker.com/r/qxorm/ubuntu-with-qxorm-test-qxblogrestapi   (minimal size, just QxOrm library and all dependencies)
#    https://hub.docker.com/r/qxorm/ubuntu-with-qxorm-dev-qxblogrestapi    (full C++ development environment with QxOrm library)
# 
# To test this Docker file and build/run the Docker container, execute the following commands :
#    cd <path_to_this_docker_file>
#    docker build -t qxorm/ubuntu-with-qxorm-test-qxblogrestapi .
#    docker run --rm -itd -p 9642:9642 qxorm/ubuntu-with-qxorm-test-qxblogrestapi
# 
# By default, Docker build generates a minimal image size, with just the QxOrm test application and all dependencies
# If you prefer to generate a Docker image with full C++ development environment, execute the following commands :
#    cd <path_to_this_docker_file>
#    docker build --target dev -t qxorm/ubuntu-with-qxorm-dev-qxblogrestapi .
#    docker run --rm -itd -p 9642:9642 -p 9643:9643 -p 2222:22 qxorm/ubuntu-with-qxorm-dev-qxblogrestapi
# 
# Then access to the remote C++ development environment via Visual Studio Code with the 'Dev Containers' extension or via 'Remote SSH' extension
# Once connected to the remote C++ development environment :
#    Press 'CTRL+SHIFT+B' to build the project in debug mode
#    Press 'F5' to execute the project in debug mode
# 
# To check if the QxOrm test application is running, on your host machine, open a web browser and go to URL :
#    http://localhost:9642/files/test_http_server.html
# -----------------------------------------------------------------------------------

# ----------------------------------------------------------
# Start from Ubuntu Docker image (latest version by default)
ARG UBUNTU_VERSION=latest
FROM ubuntu:${UBUNTU_VERSION} AS base

# -----------------------
# QxOrm library meta-data
LABEL website="https://www.qxorm.com/"
LABEL email="contact@qxorm.com"
LABEL author="Lionel Marty"

# ---------------------------
# Create a 'qxorm' user/group
ENV QX_USER=qxorm
ENV QX_HOME=/home/$QX_USER
ENV QX_DIR=$QX_HOME/src/QxOrm
ENV QX_SCRIPTS=$QX_HOME/scripts
RUN groupadd -g 1987 $QX_USER && \
    useradd -m -u 1987 -g $QX_USER $QX_USER && \
    echo "$QX_USER:$QX_USER" | chpasswd

# -------------------------------------------------------------------
# Start a new Docker image stage to install a development environment
FROM base AS dev

# ---------------------------------------------------------------
# Define environment variable to install by default Qt6 framework
ENV QT_VERSION_MAJOR=6

# -----------------------------
# Install on the Docker image :
# - 'build-essential' to get gcc compiler
# - 'qtX-base-dev' to install Qt framework (by default Qt6, but you can install Qt5 overriding environment variable 'QT_VERSION_MAJOR')
# - 'wget', 'curl' and 'unzip' to download and extract QxOrm package
# - 'openssh-server' to connect via SSH, useful to debug
# - 'nano' to have a text editor from terminal
# - 'cmake' to build QxOrm library
# - 'gdb' to debug inside container
RUN apt update -y \
    && apt upgrade -y \
    && apt install -y \
      wget curl \
      unzip \
      nano \
      openssh-server \
      build-essential \
      qt${QT_VERSION_MAJOR}-base-dev \
      cmake \
      gdb \
    && apt clean -y \
    && rm -rf /var/lib/apt/lists/*

# ----------------------------------------------
# Download QxOrm library source code from GitHub
ENV QX_URL_DOWNLOAD="https://github.com/QxOrm/QxOrm/archive/refs/heads/master.zip"
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/download_qx.sh .
USER $QX_USER
RUN ./download_qx.sh

# --------------------------------------
# Define environment variables for cmake
ENV QX_CMAKE_OPTIONS_RELEASE="-DCMAKE_INSTALL_PREFIX=/usr -D_QX_ENABLE_QT_NETWORK=1 -D_QX_UNITY_BUILD=1 -D_QX_NO_GUI=1 -D_QX_TEST_QXBLOGRESTAPI=1"
ENV QX_CMAKE_OPTIONS_DEBUG="-DCMAKE_BUILD_TYPE=Debug -D_QX_ENABLE_QT_NETWORK=1 -D_QX_NO_GUI=1 -D_QX_TEST_QXBLOGRESTAPI=1"
ENV CMAKE_OPTIONS=${QX_CMAKE_OPTIONS_RELEASE}
ENV CMAKE_CONFIG="Release"
ENV CMAKE_BUILD_PARALLEL_LEVEL=2

# -----------------------------------------------------------------------------------
# Build QxOrm library and example project with 'QxHttpServer' and 'QxRestApi' modules
# Documentation about 'QxHttpServer' module : https://www.qxorm.com/qxorm_en/manual.html#manual_96
# Documentation about 'QxRestApi' module : https://www.qxorm.com/qxorm_en/manual.html#manual_97
WORKDIR $QX_DIR/test/build/debug/
WORKDIR $QX_DIR/test/build/release/
RUN cmake ../.. $CMAKE_OPTIONS
RUN cmake --build . --config $CMAKE_CONFIG

# ------------------------------------------
# Start SSH server service (useful to debug)
# To connect via SSH : ssh qxorm@localhost -p <port_bound_to_22>
USER root
EXPOSE 22
RUN service ssh start

#-------------------------------------------------
# Install Visual Studio Code Server and extensions
# https://github.com/b01/dl-vscode-server
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/download-vs-code.sh .
COPY --chmod=+x ./scripts/install-vs-code.sh .
RUN ./install-vs-code.sh

# -----------------------------------------------------
# Copy scripts to build and debug in Visual Studio Code
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/build_qx.sh .

USER $QX_USER
WORKDIR $QX_DIR/.vscode/
COPY ./.vscode/launch.json .
COPY ./.vscode/tasks.json .
USER root

# -------------------------------------------------------------
# Expose port to access to QxOrm simple HTTP web server example
# Port '9642' (by default) to connect to the 'release' version
# Port '9643' (by default) to connect to the 'debug' version
ENV QX_PORT_RELEASE=9642
ENV QX_PORT_DEBUG=9643
EXPOSE ${QX_PORT_RELEASE} ${QX_PORT_DEBUG}

# --------------------------------------------
# Execute QxOrm simple HTTP web server example
# On your host machine, open a web browser and go to URL :
#    http://localhost:9642/files/test_http_server.html
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/copy_env_var_qx.sh .

WORKDIR $QX_DIR/test/_bin
ENV LD_LIBRARY_PATH=$QX_DIR/lib:$LD_LIBRARY_PATH
COPY --chmod=+x ./scripts/entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
CMD [ "ssh", "build" ]

# ----------------------------------------------------------------------
# Start a new Docker image stage to find and copy all QxOrm dependencies
# To stop the image generation here and stay with the development environment :
#    docker build --target dev -t qxorm/ubuntu-with-qxorm-dev-qxblogrestapi .
FROM dev AS prepare_dependencies

# ---------------------------------------------------------
# Find all QxOrm project example dependencies and copy them
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/prepare_dependencies_qx.sh .
RUN ./prepare_dependencies_qx.sh

# -----------------------------------------------------------------------------------------------
# Start a new stage to create a minimal Docker image with just QxOrm library and all dependencies
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
# Copy QxOrm library and all dependencies
WORKDIR $QX_HOME/app
COPY --from=prepare_dependencies $QX_DIR/test/_bin/ $QX_HOME/app/

# --------------------------------------------
# Execute QxOrm simple HTTP web server example
# On your host machine, open a web browser and go to URL :
#    http://localhost:9642/files/test_http_server.html
WORKDIR $QX_SCRIPTS/
COPY --chmod=+x ./scripts/copy_env_var_qx.sh .

WORKDIR $QX_HOME/app
ENV LD_LIBRARY_PATH=$QX_HOME/app/libs:$LD_LIBRARY_PATH
EXPOSE 9642
COPY --chmod=+x ./scripts/entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
