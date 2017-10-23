
Dockerfiles
===========

The subdirectories fo this directory contains the dockerfiles to build the test environments for
Candas.

 * `env-clang`: An environment with clang as the selected compiler.
 * `env-clang-libcxx`: An environment with Clang as the compiler, where libc++ is available as
    the standard library.
 * `env-gcc`: An environment where gcc is the default compiler.

Tests are run against the tags `clang`, `clang-libcxx`, and `gcc` on the dockerhub repository
`candas/test-env`.

## Build

*Warning:* It takes a long time to build a images.

*NB:* `env-clang` must be built before `env-clang-libcxx` as the latter depends upon the former.

**Configuration:**

 * `cmake_version`, `llvm_version`, and `gcc_version`: These variables determine the versions to
    build.  The versions must match versions found on the respective download pages.
 * `docker_build_cmd`: Change this the your favored docker build command. The most usefull change
    is to change the number of CPUs used for the builds. E.g.: `--cpuset-cpus 1,2,3,4` wil build
    using four cores.

``` bash
cmake_version=3.9.2
llvm_version=5.0.0
gcc_version=7.2.0

docker_build_cmd="docker build --cpuset-cpus 1"

# build core
$docker_build_cmd \
        -t candas/core:latest  core

# build the clang testing environment
$docker_build_cmd \
        --build-arg cmake_ver=$cmake_version \
        --build-arg clang_ver=$llvm_version \
        -t candas/test-env:clang  env-clang

# build the clang with libc++ testing environment
$docker_build_cmd \
        -t candas/test-env:clang-libcxx  env-clang-libcxx

# build the gcc testing environment
$docker_build_cmd \
        --build-arg cmake_ver=$cmake_version \
        --build-arg gcc_ver=$gcc_version \
        -t candas/test-env:gcc  env-gcc
```

