
FROM candas/core:latest
LABEL maintainer="eivind@xal.no"

# build arguments
ARG  cmake_ver
ARG  gcc_ver

# build
ADD  build-steps-cmake.sh \
     build-steps-gcc.sh  /
RUN  bash build-steps-cmake.sh ${cmake_ver} \
 &&  bash build-steps-gcc.sh ${gcc_ver} \
 &&  rm build-steps-cmake.sh build-steps-gcc.sh

# set variables
ENV  CMAKE_VERSION=${cmake_ver} \
     GCC_VERSION=${gcc_ver} \
     CC=gcc \
     CXX=g++

