
Candas
======

WIP proof of concept for low-cost static dataframes.

How to build
------------

### Requirements

 * **Compiler**: `clang >= 4` or `gcc >= 7`.
 * **CMake**: `CMake-3.5`. (Older versions may work, but have not been tested.)

### Build

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

