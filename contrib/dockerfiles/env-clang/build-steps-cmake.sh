#!/bin/bash

function echo_run {
    echo "EXECUTING :: $@"
    "$@"
    if [ $? != 0 ] ; then
        echo "ERROR :: failed doing '$@'"
        exit 1
    fi
}

# abort if no version is given
if [ -z "$1" ] ; then
    echo "ERROR :: No version given"
    exit 1
fi

# what version of CLANG to build
# - must match a version found on `https://releases.llvm.org/`
CMAKE_VERSION="$1"
PATH_VER="$(echo $CMAKE_VERSION | sed -r s/\\.[0-9]+$//)"

DOWN_DIR=$HOME/down
CMAKE_SRC_DIR=$HOME/cmake-src

# build in a shell procedure to use the same subshell for the entire build
build_steps () {

    # download and check
    echo_run  mkdir -p $DOWN_DIR && cd $DOWN_DIR
    echo_run  curl  -O https://cmake.org/files/v$PATH_VER/cmake-$CMAKE_VERSION.tar.gz \
                    -O https://cmake.org/files/v$PATH_VER/cmake-$CMAKE_VERSION-SHA-256.txt
    echo_run  sha256sum --ignore-missing -c cmake-$CMAKE_VERSION-SHA-256.txt
    echo_run  tar xzf cmake-$CMAKE_VERSION.tar.gz
    echo_run  mv cmake-$CMAKE_VERSION $CMAKE_SRC_DIR

    # build
    echo_run  cd $CMAKE_SRC_DIR
    echo_run  ./bootstrap && make -j$(nproc) && make install

    # cleanup
    echo_run  cd $HOME
    echo_run  rm -rf $DOWN_DIR $CMAKE_SRC_DIR

}
build_steps

