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
[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/rhalbersma/tabula/badge)](https://scorecard.dev/viewer/?uri=github.com/rhalbersma/tabula)

tabula is a header-only C++23 library for representing board-game grids, squares, and board embeddings. It aims to provide portable, compile-time building blocks for board representations and common chess, draughts, and Stratego layouts without requiring experimental language features.

## Using tabula

tabula is consumed through [CMake](https://cmake.org/), which is the build system it supports: it exports a `tabula::tabula` interface target, ships a package config for `find_package`, and needs CMake 3.28 or later. All three integration paths below hand you that same target.

tabula isn't published to a package registry, so the default way to add it is `FetchContent`, which needs no separate install step:

```cmake
include(FetchContent)
FetchContent_Declare(
    tabula
    GIT_REPOSITORY https://github.com/rhalbersma/tabula.git
    GIT_TAG main # or a release tag
)
FetchContent_MakeAvailable(tabula)
target_link_libraries(my_target PRIVATE tabula::tabula)
```

If you've already installed tabula yourself (e.g. `cmake --install`, or your own package manager integration), use `find_package` instead:

```cmake
find_package(tabula 0.1.0 CONFIG REQUIRED)
target_link_libraries(my_target PRIVATE tabula::tabula)
```

If you vendor the source directly (e.g. a git submodule), use `add_subdirectory` (tabula's own tests, and the dependencies they need, are only built when tabula is the top-level project, so nothing needs to be disabled):

```cmake
add_subdirectory(external/tabula)
target_link_libraries(my_target PRIVATE tabula::tabula)
```

The target publishes the public headers and requires C++23. You can include individual headers directly, such as `<tabula/board.hpp>` or `<tabula/games/chess.hpp>`.

None of this needs tabula's own test suite, which only matters when working on the library itself; see [CONTRIBUTING.md](CONTRIBUTING.md) for how to build and run it.

## Requirements

Using tabula requires a conforming [C++23](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) compiler and CMake 3.28 or later. Beyond those, nothing: the library is header-only, depends on no third-party code, and links against nothing, so adding it to a project adds no transitive requirements of its own. It is expected to work with any compiler that implements the C++23 features it uses.

Running tabula's own test suite does have dependencies, which consumers never build. They are listed in [CONTRIBUTING.md](CONTRIBUTING.md).

### Continuously tested toolchains

tabula is continuously tested with the following conforming C++23 compilers, against all three mainstream standard libraries (libstdc++, the MSVC STL, and libc++). Following the model of [apt.llvm.org](https://apt.llvm.org/), which publishes its packages for a stable, a qualification and a development branch, we track the same three channels for every compiler: the established release, the newest release still being qualified, and the current development branch. Every leg in the table below is required, including every `Development` entry - a break there fails CI the same as a break on a stable release does - except the MSVC 2026 and 2026-Preview legs, which no longer run per push or pull request at all while the runner image lacks the upstream compiler fix.

| Platform | Compiler | Standard Library | Stable | Qualification | Development | CI |
| :------- | :------- | :--------------- | :----- | :------------ | :---------- | :- |
| Linux | GCC | libstdc++ | 15 | 16 | 17-SVN | [![GCC](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/gcc.yml) |
| Windows | MinGW | libstdc++ | 15 | 16 | 17-SVN | [![MinGW](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/mingw.yml) |
| Linux | Clang | libstdc++ | 22 (libstdc++ 15) | 23 (libstdc++ 16) | 24-SVN (libstdc++ 17-SVN) | [![Clang](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang.yml) |
| Linux | Clang | libc++ | 22 | 23 | 24-SVN | [![Clang-libc++](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-libc%2B%2B.yml) |
| macOS | Apple Clang | libc++ | 17.0.0 (Xcode 16.4) | 21.0.0 (Xcode 26.6) | — | [![Apple Clang](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/apple-clang.yml) |
| Windows | Clang-CL | MSVC | 19.1.5 (VS 2022) | 20.1.8 (VS 2026) | 20.1.8 (VS 2026-Preview) | [![Clang-CL](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/clang-cl.yml) |
| Windows | MSVC | MSVC | — | 2026 | 2026-Preview | [![MSVC](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml/badge.svg)](https://github.com/rhalbersma/tabula/actions/workflows/msvc.yml) |

The Clang workflows name their apt.llvm.org suite directly - a versioned `llvm-toolchain-<codename>-<version>` for stable and qualification, the unversioned `llvm-toolchain-<codename>` for development - rather than letting `llvm.sh` derive it. That script resolves a version through a hardcoded table which lags LLVM's annual rollover, so in the weeks around a release it can neither be asked for the new development version nor find the previous one in the unversioned suite it resolves to.

`Apple Clang` has no `Development` entry because Apple doesn't publish Apple Clang dev snapshots the way LLVM does; that leg tests the latest stable Xcode release from each of the two supported series.

MSVC currently fails outright on an ambiguous partial-specialization bug (`basic_compass<chequer{...}>`), [reported fixed upstream in VS 18.7.0](https://developercommunity.visualstudio.com/t/VS-2019-164:-Ambiguous-partial-speciali/865810) per Microsoft's own tracker but not independently verified - Compiler Explorer's msvc-latest is still on the 18.6 line (`_MSC_VER` 1951), so there's no publicly reachable 18.7.0 build to confirm it yet - and not present on GitHub Actions' runner image either ([actions/runner-images#14130](https://github.com/actions/runner-images/issues/14130) tracks a bump to 18.6.x, still short of 18.7.0). MSVC therefore runs on no push and no pull request: `msvc.yml` and `msvc-analyze.yml` are reachable only on demand and, for `msvc.yml`, through the weekly `canary.yml` run. A check that cannot pass teaches you to skip past red, and these could not pass on any commit. The canary is what keeps the day they start passing observable, and [#22](https://github.com/rhalbersma/tabula/issues/22) tracks restoring both stubs to `push` and `pull_request` when it does.

## Acknowledgments

Special thanks to Fabien Letouzey for a very fruitful exchange of ideas.

## License

Copyright Rein Halbersma 2019-2026.
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html).
(See accompanying file LICENSE_1_0.txt or copy at [http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt))
