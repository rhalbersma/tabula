# Contributing to tabula

## Workflow

When adding or changing a public utility:

1. Add or update the relevant header under `include/tabula/`.
2. Add or update matching tests under `test/src/`; CMake creates one test executable per `.cpp` file in that directory.
3. Build and test locally (see below).
4. Update the feature table and examples in [README.md](README.md) when the public API changes.

## What a PR must satisfy before it can merge

This repository enforces its quality bar through CI rather than through review discretion. A PR is mergeable once every required check below is green:

- **The supported compiler/platform legs pass.** The [README's compiler table](README.md) is the current matrix: GCC, Clang with libstdc++, Clang with libc++, MinGW, Apple Clang, and Clang-CL. Each includes every listed stable and trunk/preview leg. The MSVC 2026 and MSVC 2026-Preview jobs also run, but are not required PR checks while the GitHub runner image lacks the upstream compiler fix documented in the README.
- **`clang-tidy` is clean.** The [Clang-Tidy workflow](.github/workflows/clang-tidy.yml) runs the checks in [`.clang-tidy`](.clang-tidy) with `WarningsAsErrors: '*'` over the public headers, so any finding fails the job outright.
- **Coverage does not regress.** The [Coverage workflow](.github/workflows/coverage.yml) reports line and branch coverage with gcovr and uses a 100% line/branch target. Its gcovr and Codecov checks are currently informational while tabula's existing coverage is brought up to that target; new code should nonetheless include tests for every line and meaningful branch it adds. The report excludes `assert(...)` contract checks, compiler-synthesized `= default;` members, exception-unwinding branches, and unreachable branches, none of which are meaningful coverage requirements for correct tests.
- **No sanitizer failures.** The [Sanitizers workflow](.github/workflows/sanitizers.yml) runs AddressSanitizer and UndefinedBehaviorSanitizer; both jobs must stay green.
- **The public headers stay self-sufficient.** Each header is compiled as its own translation unit (see `test/CMakeLists.txt`); don't rely on include order from another header.
- **Workflow files pass `actionlint`.** The [Actionlint workflow](.github/workflows/actionlint.yml) validates GitHub Actions syntax and expressions.
- **The documented consumption methods work.** The [Consumption workflow](.github/workflows/consumption.yml) builds a consumer using `find_package`, `add_subdirectory`, and `FetchContent`.
- **CodeQL analysis is clean.** The [CodeQL workflow](.github/workflows/codeql.yml) runs the C/C++ `security-extended` query suite.

The scheduled Toolchain Canary re-runs the compiler workflows weekly, and Scorecard runs on pushes and its own schedule; neither is a pull-request job. Match the surrounding code's style by eye, including the Boost Software License header comment at the top of every source and workflow file.

## Building and testing locally

With Boost.Test available to CMake:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Or with the checked-in CMake presets, which pick up Boost.Test from a `VCPKG_ROOT`-configured vcpkg toolchain:

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
