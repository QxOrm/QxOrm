#!/bin/sh

# Copyright 2024 Khalifah K. Shabazz
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the “Software”),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

set -e

usage="
This script downloads a tar of VS Code Server/CLI, then extracts it to a
location expected by tunnels made by VS Code clients.

download-vs-code.sh [options] <PLATFORM> [<ARCH>]

Example:
  download-vs-code.sh \"linux\" \"x64\" --alpine

Options

--insider
    Switches to the pre-released version of the binary chosen (server or
    CLI).

--dump-sha
    Will print the latest commit sha for VS Code (server and CLI are current
    synced and always the same).

--cli
    Switches the binary download VS Code CLI.

--alpine
    Only works when downloading VS Code Server, it will force PLATFORM=linux and
    ARCH=alpine, as the developers deviated from the standard format used for
    all others.

--extensions
    specify which extensions to install. expects a string of full extension names seperated by a space,
    e.g \"ms-vscode.PowerShell redhat.ansible ms-python.vscode-pylance\"

-h, --help
    Print this usage info.
"

# Get the latest VS Code commit sha.
get_latest_release() {
    platform=${1}
    arch=${2}
    bin_type="${3}"

    # Grab the first commit SHA since as this script assumes it will be the
    # latest.
    commit_id=$(curl --silent "https://update.code.visualstudio.com/api/commits/${bin_type}/${platform}-${arch}" | sed s'/^\["\([^"]*\).*$/\1/')

    # These work:
    # https://update.code.visualstudio.com/api/commits/stable/win32-x64
    # https://update.code.visualstudio.com/api/commits/stable/linux-x64
    # https://update.code.visualstudio.com/api/commits/insider/linux-x64

    # these do not work:
    # https://update.code.visualstudio.com/api/commits/stable/darwin-x64
    # https://update.code.visualstudio.com/api/commits/stable/linux-alpine
    printf "%s" "${commit_id}"
}

# You can test the code binary is installed in the correct location by
# making a tunnel to vscode.dev with:
# ~/.vscode-server/code tunnel --accept-server-license-terms
install_cli() {
    echo "setup directories:"
    # Make the directories where the VS Code will search. There may be others not
    # listed here.
    # NOTE: VS Code will runas the logged in user, so ensure they have
    #       read/write to the following directories
    mkdir -vp ~/.vscode-server
    echo "done"

    # Extract the tarball to the right location.
    printf "%s" "extracting ${archive}..."
    tar -xz -C ~/.vscode-server --no-same-owner -f "/tmp/${archive}"
    echo "done"

    # Add symlinks
    printf "%s" "setup symlinks..."
    ln -s ~/.vscode-server/code ~/.vscode-server/code-"${commit_sha}"
    ln -s "${HOME}"/.vscode-server/code ~/code
    echo "done"
}

install_server() {
    echo "setup directories:"
    # Make the directories where the VS Code will search. There may be others not
    # listed here.
    # NOTE: VS Code will runas the logged in user, so ensure they have
    #       read/write to the following directories
    mkdir -vp ~/.vscode-server/bin/"${commit_sha}"
    # VSCode Requirements for pre-installing extensions
    mkdir -vp ~/.vscode-server/extensions
    # found this in the VSCode remote extension output when connecting to an existing container
    mkdir -vp ~/.vscode-server/extensionsCache
    # This should handle installs for https://vscode.dev/
    mkdir -vp ~/.vscode/cli/servers/Stable-"${commit_sha}"
    mkdir -vp ~/.vscode-server/cli/servers/Stable-"${commit_sha}"
    echo "done"

    # Extract the tarball to the right location.
    printf "%s" "extracting ${archive}..."
    tar -xz -C ~/.vscode-server/bin/"${commit_sha}" --strip-components=1 --no-same-owner -f "/tmp/${archive}"
    echo "done"

    # Add symlinks
    printf "%s" "setup symlinks..."
    ln -s ~/.vscode-server/bin/"${commit_sha}" ~/.vscode-server/bin/default_version
    ln -s ~/.vscode-server/bin/"${commit_sha}" ~/.vscode/cli/servers/Stable-"${commit_sha}"/server
    ln -s ~/.vscode-server/bin/"${commit_sha}" ~/.vscode-server/cli/servers/Stable-"${commit_sha}"/server
    ln -s ~/.vscode-server/bin/"${commit_sha}"/bin/code-server ~/code-server
    echo "done"
}

## Parse command line options, proper
getopt --test > /dev/null && true
if [ $? -ne 4 ]; then
    echo 'sorry, getopts --test` failed in this environment'
    exit 1
fi

LONG_OPTS=help,insider,dump-sha,cli,alpine,extensions:
OPTIONS=h

PARSED=$(getopt --options=${OPTIONS} --longoptions=${LONG_OPTS} --name "$0" -- "${@}") || exit 1
eval set -- "${PARSED}"

PLATFORM=""
ARCH=""
BUILD="stable"
BIN_TYPE="server"
DUMP_COMMIT_SHA=""
IS_ALPINE=0

while [ true ]; do
    case ${1} in
        --insider)
            BUILD="insider"
            shift
            ;;
        --dump-sha)
            DUMP_COMMIT_SHA="yes"
            shift
            ;;
        --cli)
            BIN_TYPE="cli"
            shift
            ;;
        --alpine)
            IS_ALPINE=1
            shift
            ;;
        --extensions)
            EXTENSIONS="${2}"
            shift 2
            ;;
        -h|--help)
            echo "${usage}"
            exit 0
            ;;
        --) shift; break;;
        *) echo "unknown option '${1}'"; exit 1;;
    esac
done

# Platform is required.
if [ "$#" -lt 1 ]; then
    echo "please specify which platform version of VS Code to install\nacceptable values are linux, alpine, win32, or darwin"
    exit 1
fi

if [ "$#" -lt 2 ]; then
    echo "missing required architecture argument <ARCH> (arm64|armhf|x64)"
    exit 1
fi

case ${1} in
    # When downloading code server for Alpine, you must pass PLATFORM=linux and ARCH=alpine.
    # Setting PLATFORM=alpine is OK here for downloading code CLI.
    alpine|darwin|linux|win32)
      PLATFORM="${1}"
      ;;
esac

case ${2} in
    arm64|armhf|x64)
      ARCH="${2}"
      ;;
esac

# When non specified, then pull from the OS.
if [ -z "${ARCH}" ]; then
    U_NAME=$(uname -m)

    if [ "${U_NAME}" = "aarch64" ]; then
        ARCH="arm64"
    elif [ "${U_NAME}" = "x86_64" ]; then
        ARCH="x64"
    elif [ "${U_NAME}" = "armv7l" ]; then
        ARCH="armhf"
    fi
fi

# Patch things when downloading VS Code Server for Alpine.
if [ "${BIN_TYPE}" = "server" -a ${IS_ALPINE} -eq 1 ]; then
    echo "we need to hard set PLATFORM and ARCH for Alpine Musl"
    PLATFORM="linux"
    ARCH="alpine" # Alpine is NOT an Arch but a flavor of Linux, oh well.
fi

# We hard-code this because all but a few options returns a 404.
commit_sha=$(get_latest_release "win32" "x64" "${BUILD}")

if [ -z "${commit_sha}" ]; then
    echo "could not get the VS Code latest commit sha, exiting"
    exit 1
fi

if [ "${DUMP_COMMIT_SHA}" = "yes" ]; then
    echo "${commit_sha}"
    exit 0
fi

echo "attempting to download and pre-install VS Code ${BIN_TYPE} version '${commit_sha}'"

options="${BIN_TYPE}-${PLATFORM}-${ARCH}"
archive="vscode-${options}.tar.gz"

# Download VS Code tarball to the current directory.
url="https://update.code.visualstudio.com/commit:${commit_sha}/${options}/${BUILD}"
printf "%s" "downloading ${url} to ${archive} "
curl -s --fail -L "${url}" -o "/tmp/${archive}"
echo "done"

# Based on the binary type chosen, perform the installation.
if [ "${BIN_TYPE}" = "cli" ]; then
    install_cli
else
    install_server
fi

echo "VS Code server pre-install completed"
echo "downloading extensions..."

if [ -n "${EXTENSIONS}" ]; then
    ## Auto-accept license terms and then install the extensions, by force if they already exist.
    for extension in ${EXTENSIONS}; do
        ~/code-server --accept-server-license-terms --force --install-extension "${extension}"
    done
fi

echo "extensions installation complete"
