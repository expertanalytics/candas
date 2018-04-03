
FROM candas/core:latest
LABEL maintainer="eivind@xal.no"

# build arguments
ARG  cmake_ver
ARG  clang_ver

# build
ADD  build-steps-cmake.sh \
     build-steps-clang.sh  /
RUN  bash build-steps-cmake.sh ${cmake_ver} \
 &&  bash build-steps-clang.sh ${clang_ver} \
 &&  rm build-steps-cmake.sh build-steps-clang.sh

# set variables
ENV  CMAKE_VERSION=${cmake_ver} \
     CLANG_VERSION=${clang_ver} \
     CC=clang \
     CXX=clang++

