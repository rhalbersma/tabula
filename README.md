# Board game utilities

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-Boost-blue.svg)](https://opensource.org/licenses/BSL-1.0)
[![Lines of Code](https://tokei.rs/b1/github/rhalbersma/tabula?category=code)](https://github.com/rhalbersma/tabula)

## Requirements

This single-header library has no other dependencies than the C++ Standard Library and is continuously being tested with the following conforming [C++23](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) compilers:

| Platform | Compiler   | Versions     | Build |
| :------- | :-------   | :-------     | :---- |
| Linux    | GCC        | $\geq$ 14    | CI currently being ported to GitHub Actions |
| Linux    | Clang      | $\geq$ 17    | CI currently being ported to GitHub Actions |
| Windows  | Visual C++ | $\geq$ 17.10 | CI currently being ported to GitHub Actions |

Note that the unit tests depend on [Boost](https://www.boost.io/).

## Acknowledgments

Special thanks to Fabien Letouzey for a very fruitful exchange of ideas.

## License

Copyright Rein Halbersma 2019-2023.
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html).
(See accompanying file LICENSE_1_0.txt or copy at [http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt))
