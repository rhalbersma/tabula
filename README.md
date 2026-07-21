# Board game utilities

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-Boost-blue.svg)](https://opensource.org/licenses/BSL-1.0)
[![GCC](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml)
[![MinGW](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml)
[![Clang](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml)
[![Clang-libc++](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml)
[![Apple Clang](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml)
[![Clang-CL](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml)
[![MSVC](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml)
[![Coverage](https://codecov.io/gh/rhalbersma/tabula/branch/main/graph/badge.svg)](https://codecov.io/gh/rhalbersma/tabula)
[![OpenSSF Scorecard](https://api.securityscorecards.dev/projects/github.com/rhalbersma/tabula/badge)](https://securityscorecards.dev/viewer/?uri=github.com/rhalbersma/tabula)

## Requirements

This single-header library has no other dependencies than the C++ Standard Library and is continuously tested with the following conforming [C++23](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) compilers, against all three mainstream standard libraries (libstdc++, the MSVC STL, and libc++). Following the model of [apt.llvm.org](https://apt.llvm.org/), we support the latest two stable releases of each compiler, plus its current development branch. Every table leg is required except the MSVC 2026 and 2026-Preview legs, which are intentionally allowed to fail while the runner image lacks the upstream compiler fix.

| Platform | Compiler | Standard Library | Older stable | Latest stable | Trunk / Preview | Build |
| :------- | :------- | :--------------- | :------------ | :------------ | :-------------- | :---- |
| Linux | GCC | libstdc++ | 15 | 16 | 17-SVN | [![GCC](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml) |
| Windows | MinGW | libstdc++ | 15 | 16 | 17-SVN | [![MinGW](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml) |
| Linux | Clang | libstdc++ | 21 (libstdc++ 15) | 22 (libstdc++ 16) | 23-SVN (libstdc++ 17-SVN) | [![Clang](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml) |
| Linux | Clang | libc++ | 21 | 22 | 23-SVN | [![Clang-libc++](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml) |
| macOS | Apple Clang | libc++ | 17.0.0 (Xcode 16.4) | 21.0.0 (Xcode 26.6) | — | [![Apple Clang](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml) |
| Windows | Clang-CL | MSVC | 19.1.5 (VS 2022) | 20.1.8 (VS 2026) | 20.1.8 (VS 2026-Preview) | [![Clang-CL](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml) |
| Windows | MSVC | MSVC | — | 2026 | 2026-Preview | [![MSVC](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml) |

MSVC currently fails outright on an ambiguous partial-specialization bug (`basic_compass<chequer{...}>`), [reported fixed upstream in VS 18.7.0](https://developercommunity.visualstudio.com/t/VS-2019-164:-Ambiguous-partial-speciali/865810) per Microsoft's own tracker but not independently verified - Compiler Explorer's msvc-latest is still on the 18.6 line (`_MSC_VER` 1951), so there's no publicly reachable 18.7.0 build to confirm it yet - and not present on GitHub Actions' runner image either ([actions/runner-images#14130](https://github.com/actions/runner-images/issues/14130) tracks a bump to 18.6.x, still short of 18.7.0). MSVC is not a required PR status check, so this failure is visible but doesn't block merging.

Note that the unit tests depend on [Boost](https://www.boost.io/).

## Installation

    # Setup the project
    mkdir projects && cd ~/projects/
    git clone https://github.com/rhalbersma/tabula.git
    cd tabula && mkdir build && cd build

    # Build the project
    cmake .. && cmake --build .
    ctest                       # run the unit tests
    example/print_embeddings    # print out all the predefined boards

## Acknowledgments

Special thanks to Fabien Letouzey for a very fruitful exchange of ideas.

## License

Copyright Rein Halbersma 2019-2025.
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html).
(See accompanying file LICENSE_1_0.txt or copy at [http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt))
