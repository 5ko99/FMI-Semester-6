# CMake Build Steps

```bash

cmake -S . -B build
cmake --build build

```

Main app executable is in build/apps/ directory on Linux or build/apps/Debug/ directory on Windows.

Test executables are in build/tests/ directory on Linux or build/tests/Debug/ directory on Windows.

If FetchContent does not work and Catch2 cannot be used, please add the catch.hpp header file in the tests folder.
