
Candas
======

[![CircleCI tests](https://circleci.com/gh/expertanalytics/candas.png?style=shield&circle-token=:circle-token)](https://circleci.com/gh/expertanalytics/candas/tree/master)

WIP proof of concept for low-cost static dataframes.

How to build
------------

### Requirements

 * **Compiler**: `clang >= 4` or `gcc >= 7`.
 * **CMake**: `CMake-3.5`. (Older versions may work, but have not been tested.)

### Build

To change the compiler used by CMake and make, define the `CXX` variable prior to running
the cmake command. This is only of interst when building the tests as the Candas library is
header only. E.g. do `CXX=clang++ cmake ..` to configure using the clang C++ compiler.

The change the build type for the tests add `-DCMAKE_BUILD_TYPE=<...>` to the cmake command.
The valid build types are: `Debug`, `Release`, and `RelWithDebInfo`.

``` bash
# setup
cd path/to/candas
mkdir build
cd build
cmake ..

# build & run tests
cd path/to/candas/build
make check
# - alternativly
make test-candas
make test  # or execute 'tests/test-candas'
```

License
-------

This project is licensed under the terms of the MIT license.

See the [LICENSE.txt](LICENSE.txt) file at the package root.

Contributors
------------

 * [Eivind Aarnæs](https://github.com/eistaa)
 * [Ola Skavhaug](https://github.com/skavhaug)

