
FROM candas/test-env:clang
LABEL maintainer="eivind@xal.no"

# build
ADD  build-steps-libcxx.sh .
RUN  bash build-steps-libcxx.sh $CLANG_VERSION \
 &&  rm build-steps-libcxx.sh

# set variables
ENV  LIBCXX_VERSION=$CLANG_VERSION \
     CC=clang \
     CXX=clang++

