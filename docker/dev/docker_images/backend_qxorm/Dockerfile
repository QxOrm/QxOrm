# -----------------------------------------------------------------------------------
# TODO...
# -----------------------------------------------------------------------------------

# -------------------------------------------------------------------
# Start from QxOrm Docker image with full C++ development environment
FROM qxorm/ubuntu-with-qxorm-dev-qxblogrestapi AS dev

# --------------------------
# Clear previous cmake build
RUN rm -rfv $QX_DIR/test/build/debug/*
RUN rm -rfv $QX_DIR/test/build/release/*
RUN rm -rfv $QX_DIR/test/_bin/*
RUN rm -rfv $QX_DIR/lib/*

# --------------------------------------------------------------------
# The environment variable 'QX_DB' defines which database to connect :
# - if empty : SQLite database
# - 'MongoDB' : MongoDB database (default value in this script)
# - 'PostgreSQL' : PostgreSQL database
# - 'MySQL' or 'MariaDB' : MySQL or MariaDB database
ENV QX_DB=MongoDB

# -----------------------------
# Install on the Docker image :
# - 'libmongoc' and 'libbson' : MongoDB C Driver and BSON library
# - 'libqtXsqlX-psql' : Qt SQL driver for PostgreSQL database
# - 'libqtXsqlX-mysql' : Qt SQL driver for MySQL and MariaDB database
RUN apt update -y \
    && apt upgrade -y \
    && apt install -y \
      libmongoc-dev \
      libqt${QT_VERSION_MAJOR}sql${QT_VERSION_MAJOR}-psql \
      libqt${QT_VERSION_MAJOR}sql${QT_VERSION_MAJOR}-mysql \
    && apt clean -y \
    && rm -rf /var/lib/apt/lists/*

# --------------------------------------
# Define environment variables for cmake
ENV CMAKE_OPTIONS="${CMAKE_OPTIONS} -D_QX_ENABLE_MONGODB=1"

# -----------------------------------------------------------------------------------
# Build QxOrm library and example project with 'QxHttpServer' and 'QxRestApi' modules
# Documentation about 'QxHttpServer' module : https://www.qxorm.com/qxorm_en/manual.html#manual_96
# Documentation about 'QxRestApi' module : https://www.qxorm.com/qxorm_en/manual.html#manual_97
USER $QX_USER
WORKDIR $QX_DIR/test/build/debug/
WORKDIR $QX_DIR/test/build/release/
RUN cmake ../.. $CMAKE_OPTIONS
RUN cmake --build . --config $CMAKE_CONFIG






# TODO...
# supprimer fichiers build cmake
# définir d'autres options de compilation
# apt install libmongoc-dev
# apt install Qt SQL drivers
# etc...
