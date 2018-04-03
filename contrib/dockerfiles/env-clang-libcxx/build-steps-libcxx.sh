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
LIBCXX_VERSION="$1"

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
    echo_run  curl  -O https://releases.llvm.org/$LIBCXX_VERSION/llvm-$LIBCXX_VERSION.src.tar.xz \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/llvm-$LIBCXX_VERSION.src.tar.xz.sig \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libcxx-$LIBCXX_VERSION.src.tar.xz \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libcxx-$LIBCXX_VERSION.src.tar.xz.sig \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libcxxabi-$LIBCXX_VERSION.src.tar.xz \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libcxxabi-$LIBCXX_VERSION.src.tar.xz.sig \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libunwind-$LIBCXX_VERSION.src.tar.xz \
                    -O https://releases.llvm.org/$LIBCXX_VERSION/libunwind-$LIBCXX_VERSION.src.tar.xz.sig
    echo_run  gpg --no-options --verify llvm-$LIBCXX_VERSION.src.tar.xz.sig       llvm-$LIBCXX_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify libcxx-$LIBCXX_VERSION.src.tar.xz.sig     libcxx-$LIBCXX_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify libcxxabi-$LIBCXX_VERSION.src.tar.xz.sig  libcxxabi-$LIBCXX_VERSION.src.tar.xz
    echo_run  gpg --no-options --verify libunwind-$LIBCXX_VERSION.src.tar.xz.sig  libunwind-$LIBCXX_VERSION.src.tar.xz

    # setup sources
    echo_run  tar --xz -xf llvm-$LIBCXX_VERSION.src.tar.xz
    echo_run  tar --xz -xf libcxx-$LIBCXX_VERSION.src.tar.xz
    echo_run  tar --xz -xf libcxxabi-$LIBCXX_VERSION.src.tar.xz
    echo_run  tar --xz -xf libunwind-$LIBCXX_VERSION.src.tar.xz
    echo_run  mv llvm-$LIBCXX_VERSION.src $LLVM_SRC_HOME
    echo_run  mv libunwind-$LIBCXX_VERSION.src $LLVM_SRC_HOME/projects/libunwind
    echo_run  mv libcxxabi-$LIBCXX_VERSION.src $LLVM_SRC_HOME/projects/libcxxabi
    echo_run  mv libcxx-$LIBCXX_VERSION.src $LLVM_SRC_HOME/projects/libcxx

    # run build
    echo_run  mkdir -p $LLVM_BUILD && cd $LLVM_BUILD
    echo_run  cmake \
                -DCMAKE_BUILD_TYPE=Release \
                -DLIBCXXABI_USE_LLVM_UNWINDER=1 \
                -DLIBCXX_HAS_GCC_S_LIB=0 \
                $LLVM_SRC_HOME
    echo_run  make -j$(nproc)
    echo_run  make install
    echo_run  ldconfig /usr/local/lib

    # cleanup
    echo_run  rm -rf $LLVM_SRC_HOME $LLVM_BUILD $DOWN_DIR
    echo_run  apt-get --yes purge cmake
    echo_run  apt-get --yes clean
    echo_run  gpg --batch --delete-keys B6C8F98282B944E3B0D5C2530FC3042E345AD05D \
                                        11E521D646982372EB577A1F8F0871F202119294

}
build_steps

