
FROM ubuntu:18.04
LABEL maintainer="eivind@xal.no"

# build arguments
ARG  cmake_ver

# setup & build
ADD  build-steps-cmake.sh .
RUN  apt-get --yes update \
 &&  apt-get --yes install \
        build-essential \
        curl \
        git \
        python \
        wget \
 &&  apt-get --yes clean \
 &&  bash build-steps-cmake.sh ${cmake_ver} \
 &&  rm build-steps-cmake.sh

# set variables
ENV  CMAKE_VERSION=${cmake_ver}

