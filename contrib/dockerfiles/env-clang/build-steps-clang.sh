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
CLANG_VERSION="$1"

# define paths
DOWN_DIR=$HOME/down
LLVM_SRC_HOME=$HOME/llvm-src
LLVM_BUILD=$HOME/llvm-build

# build in a shell procedure to use the same subshell for the entire build
build_steps () {

    # get prerequisites
    echo_run  apt-get --yes update
    echo_run  apt-get --yes install \
                zlib1g-dev
    echo_run  apt-get --yes clean

    # download and check sources
    echo_run  mkdir -p $DOWN_DIR && cd $DOWN_DIR
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key B6C8F98282B944E3B0D5C2530FC3042E345AD05D
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key 11E521D646982372EB577A1F8F0871F202119294
    echo_run  curl -O https://releases.llvm.org/$CLANG_VERSION/llvm-$CLANG_VERSION.src.tar.xz \
                -O https://releases.llvm.org/$CLANG_VERSION/llvm-$CLANG_VERSION.src.tar.xz.sig \
                -O https://releases.llvm.org/$CLANG_VERSION/cfe-$CLANG_VERSION.src.tar.xz \
                -O https://releases.llvm.org/$CLANG_VERSION/cfe-$CLANG_VERSION.src.tar.xz.sig \
                -O https://releases.llvm.org/$CLANG_VERSION/clang-tools-extra-$CLANG_VERSION.src.tar.xz \
                -O https://releases.llvm.org/$CLANG_VERSION/clang-tools-extra-$CLANG_VERSION.src.tar.xz.sig \
                -O https://releases.llvm.org/$CLANG_VERSION/compiler-rt-$CLANG_VERSION.src.tar.xz \
                -O https://releases.llvm.org/$CLANG_VERSION/compiler-rt-$CLANG_VERSION.src.tar.xz.sig
    echo_run  gpg --no-options --verify llvm-$CLANG_VERSION.src.tar.xz.sig              llvm-$CLANG_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify cfe-$CLANG_VERSION.src.tar.xz.sig               cfe-$CLANG_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify clang-tools-extra-$CLANG_VERSION.src.tar.xz.sig clang-tools-extra-$CLANG_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify compiler-rt-$CLANG_VERSION.src.tar.xz.sig       compiler-rt-$CLANG_VERSION.src.tar.xz

    # setup sources
    echo_run  tar --xz -xf llvm-$CLANG_VERSION.src.tar.xz
    echo_run  tar --xz -xf cfe-$CLANG_VERSION.src.tar.xz
    echo_run  tar --xz -xf clang-tools-extra-$CLANG_VERSION.src.tar.xz
    echo_run  tar --xz -xf compiler-rt-$CLANG_VERSION.src.tar.xz
    echo_run  mv llvm-$CLANG_VERSION.src $LLVM_SRC_HOME
    echo_run  mv cfe-$CLANG_VERSION.src $LLVM_SRC_HOME/tools/clang
    echo_run  mv clang-tools-extra-$CLANG_VERSION.src $LLVM_SRC_HOME/tools/clang/tools
    echo_run  mv compiler-rt-$CLANG_VERSION.src $LLVM_SRC_HOME/projects/compiler-rt

    # run build
    echo_run  mkdir -p $LLVM_BUILD && cd $LLVM_BUILD
    echo_run  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release $LLVM_SRC_HOME
    echo_run  make -j $(nproc)
    echo_run  make install
    echo_run  ldconfig /usr/local/lib

    # cleanup
    echo_run  rm -rf $LLVM_SRC_HOME $LLVM_BUILD $DOWN_DIR
    echo_run  apt-get --yes purge cmake python
    echo_run  apt-get --yes clean
    echo_run  gpg --batch --delete-keys B6C8F98282B944E3B0D5C2530FC3042E345AD05D \
                                        11E521D646982372EB577A1F8F0871F202119294

}
build_steps

