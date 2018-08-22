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

# what version of GCC to build
# - must match a version found on `ftp://ftp.gnu.org/gnu/gcc`
GCC_VERSION="$1"

# define paths
DOWN_DIR=$HOME/down
GCC_SRC_DIR=$HOME/gcc-src
GCC_BUILD_DIR=$HOME/build-gcc

# build in a shell procedure to use the same subshell for the entire build
build_steps () {

    # get prerequisites
    echo_run  apt-get --yes update
    echo_run  apt-get --yes install \
                libc6-dev
    echo_run  apt-get --yes clean

    # download
    echo_run  mkdir -p $DOWN_DIR && cd $DOWN_DIR
    echo_run  curl  -O ftp://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
    echo_run  tar --gzip -xf gcc-$GCC_VERSION.tar.gz
    echo_run  mv gcc-$GCC_VERSION $GCC_SRC_DIR

    # build
    echo_run  cd $GCC_SRC_DIR
    echo_run  ./contrib/download_prerequisites
    echo_run  mkdir -p $GCC_BUILD_DIR && cd $GCC_BUILD_DIR
    echo_run  $GCC_SRC_DIR/configure --enable-languages=all \
                                     --enable-shared \
                                     --enable-threads=posix \
                                     --enable-_cxa_atexit \
                                     --enable-clocale=gnu \
                                     --disable-multilib
    echo_run  make -j$(nproc)
    echo_run  make install
    echo_run  ldconfig /usr/local/lib

    # cleanup
    echo_run  cd $HOME
    echo_run  rm -rf $DOWN_DIR $GCC_SRC_DIR $GCC_BUILD_DIR
    echo_run  apt-get --yes clean

}
build_steps

