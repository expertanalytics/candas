
FROM candas/core:latest
LABEL maintainer="eivind@xal.no"

# build arguments
ARG  clang_ver

# build
ADD  build-steps-clang.sh .
RUN  bash build-steps-clang.sh ${clang_ver} \
 &&  rm build-steps-clang.sh

# set variables
ENV  CLANG_VERSION=${clang_ver} \
     CC=clang \
     CXX=clang++

