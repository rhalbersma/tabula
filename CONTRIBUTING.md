# Contributing to tabula

## Workflow

When adding or changing a public utility:

1. Add or update the relevant header under `include/tabula/`.
2. Add or update matching tests under `test/src/`; CMake creates one test executable per `.cpp` file in that directory.
3. Build and test locally (see below).
4. Update the feature table and examples in [README.md](README.md) when the public API changes.

## What a PR must satisfy before it can merge

This repository enforces its quality bar through CI rather than through review discretion. A PR is mergeable once every required check below is green:

- **The supported compiler/platform legs pass.** The [README's compiler table](README.md) is the current matrix: GCC, Clang with libstdc++, Clang with libc++, MinGW, Apple Clang, and Clang-CL. Each includes every listed `Stable`, `Qualification` and `Development` leg (`17-SVN`, `24-SVN`, and Clang-CL's `2026-Preview`): tabula tracks the development channel deliberately and none of those legs are advisory. The MSVC 2026 and MSVC 2026-Preview jobs also run, but are not required PR checks while the GitHub runner image lacks the upstream compiler fix documented in the README.
- **`clang-tidy` is clean.** The [Clang-Tidy workflow](.github/workflows/clang-tidy.yml) runs the checks in [`.clang-tidy`](.clang-tidy) with `WarningsAsErrors: '*'` over the public headers, so any finding fails the job outright.
- **Coverage does not regress.** The [Coverage workflow](.github/workflows/coverage.yml) reports line and branch coverage with gcovr and uses a 100% line/branch target. Its gcovr and Codecov checks are currently informational while tabula's existing coverage is brought up to that target; new code should nonetheless include tests for every line and meaningful branch it adds. The report excludes `assert(...)` contract checks, compiler-synthesized `= default;` members, exception-unwinding branches, and unreachable branches, none of which are meaningful coverage requirements for correct tests.
- **No sanitizer failures.** The [Sanitizers workflow](.github/workflows/sanitizers.yml) runs AddressSanitizer and UndefinedBehaviorSanitizer; both jobs must stay green.
- **The public headers stay self-sufficient.** Each header is compiled as its own translation unit (see `test/CMakeLists.txt`); don't rely on include order from another header.
- **Workflow files pass `actionlint`.** The [Actionlint workflow](.github/workflows/actionlint.yml) validates GitHub Actions syntax and expressions.
- **The documented consumption methods work.** The [Consumption workflow](.github/workflows/consumption.yml) builds a consumer using `find_package`, `add_subdirectory`, and `FetchContent`.
- **CodeQL analysis is clean.** The [CodeQL workflow](.github/workflows/codeql.yml) runs the C/C++ `security-extended` query suite.

The scheduled Toolchain Canary re-runs the compiler workflows weekly, and Scorecard runs on pushes and its own schedule; neither is a pull-request job. Match the surrounding code's style by eye, including the Boost Software License header comment at the top of every source and workflow file. Public headers use include guards rather than `#pragma once`, named for the header's path under `include/` in upper case with separators replaced by underscores - `include/tabula/games/chess.hpp` gets `TABULA_GAMES_CHESS_HPP` - opened after the license comment and closed with `#endif // TABULA_GAMES_CHESS_HPP`.

## Test suite requirements

The library itself has no dependencies - see [README.md](README.md). Its test suite does, and none of them are needed to *use* tabula:

| Tool | Needed for | Notes |
| :--- | :--------- | :---- |
| A conforming C++23 compiler | everything | Same requirement as the library; see the table in [README.md](README.md) for the versions under CI |
| [CMake](https://cmake.org/) 3.28+ | configuring and building | `cmake_minimum_required` in [`CMakeLists.txt`](CMakeLists.txt); CTest ships with it |
| [Boost.Test](https://www.boost.io/) | the unit tests under `test/src/` | Declared in the checked-in [`vcpkg.json`](vcpkg.json) manifest; the `*-vcpkg` presets pick it up from a `VCPKG_ROOT`-configured vcpkg, or install it with your system package manager |
| [gcovr](https://gcovr.com/) | reproducing the coverage gate | Only for the workflow below; `pip install gcovr` |
| `clang-tidy` and `run-clang-tidy` | reproducing the clang-tidy gate | Only for the workflow below |

## Building and testing locally

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The repository also provides CMake presets for common local configurations:

```sh
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

The `*-vcpkg` presets additionally resolve Boost.Test through vcpkg, using the toolchain at `VCPKG_ROOT`:

```sh
cmake --preset dev-vcpkg
cmake --build --preset dev-vcpkg
ctest --preset dev-vcpkg
```

### Reproducing the coverage report

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=g++-15 \
  -DCMAKE_CXX_FLAGS="--coverage -O0 -g" -DCMAKE_EXE_LINKER_FLAGS="--coverage"
cmake --build build
ctest --test-dir build --output-on-failure
gcovr --root . --gcov-executable gcov-15 \
  --exclude 'test/.*' --exclude 'example/.*' --exclude 'build/.*' \
  --exclude-lines-by-pattern '^\s*assert\(' \
  --exclude-lines-by-pattern '=\s*default;' \
  --exclude-branches-by-pattern '^\s*assert\(' \
  --exclude-branches-by-pattern '^\s*.*=\s*default;' \
  --exclude-throw-branches --exclude-unreachable-branches \
  --print-summary --fail-under-line 100 --fail-under-branch 100
```

### Reproducing the clang-tidy gate

```sh
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
run-clang-tidy-22 -quiet -p build "$PWD/build/test/header_self_sufficiency/.*"
```

## License

By contributing, you agree that your contributions will be licensed under the [Boost Software License, Version 1.0](LICENSE_1_0.txt), the same license that covers the rest of this repository.
