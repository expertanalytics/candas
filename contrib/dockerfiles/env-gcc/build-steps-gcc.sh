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

    # get public keys
    # - 1024D/745C015A 1999-11-09 Gerald Pfeifer <gerald@pfeifer.com>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key B215C1633BCA0477615F1B35A5B3A004745C015A
    # - 1024D/B75C61B8 2003-04-10 Mark Mitchell <mark@codesourcery.com>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key B3C42148A44E6983B3E4CC0793FA9B1AB75C61B8
    # - 1024D/902C9419 2004-12-06 Gabriel Dos Reis <gdr@acm.org>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key 90AA470469D3965A87A5DCB494D03953902C9419
    # - 1024D/F71EDF1C 2000-02-13 Joseph Samuel Myers <jsm@polyomino.org.uk>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key 80F98B2E0DAB6C8281BDF541A7C8C3B2F71EDF1C
    # - 2048R/FC26A641 2005-09-13 Richard Guenther <richard.guenther@gmail.com>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key 7F74F97C103468EE5D750B583AB00996FC26A641
    # - 1024D/C3C45C06 2004-04-21 Jakub Jelinek <jakub@redhat.com>
    echo_run  gpg --batch --keyserver pgp.key-server.io --recv-key 33C235A34C46AA3FFB293709A328C3A2C3C45C06

    # download and check sources
    echo_run  mkdir -p $DOWN_DIR && cd $DOWN_DIR
    echo_run  curl  -O ftp://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz \
                    -O ftp://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz.sig
    echo_run  gpg --batch --verify gcc-$GCC_VERSION.tar.gz.sig gcc-$GCC_VERSION.tar.gz
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
    echo_run  gpg --batch --delete-keys B215C1633BCA0477615F1B35A5B3A004745C015A \
                                        B3C42148A44E6983B3E4CC0793FA9B1AB75C61B8 \
                                        90AA470469D3965A87A5DCB494D03953902C9419 \
                                        80F98B2E0DAB6C8281BDF541A7C8C3B2F71EDF1C \
                                        7F74F97C103468EE5D750B583AB00996FC26A641 \
                                        33C235A34C46AA3FFB293709A328C3A2C3C45C06

}
build_steps

