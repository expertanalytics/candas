
FROM candas/core:latest
LABEL maintainer="eivind@xal.no"

# build arguments
ARG  gcc_ver

# build
ADD  build-steps-gcc.sh .
RUN  bash build-steps-gcc.sh ${gcc_ver} \
 &&  rm build-steps-gcc.sh

# set variables
ENV  GCC_VERSION=${gcc_ver} \
     CC=gcc \
     CXX=g++

