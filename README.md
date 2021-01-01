# Board game utilities

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-Boost-blue.svg)](https://opensource.org/licenses/BSL-1.0)
[![Lines of Code](https://tokei.rs/b1/github/rhalbersma/tabula?category=code)](https://github.com/rhalbersma/tabula)

## Requirements

This header-only library only depends on the C++ Standard Library, and is continuously being tested with the following conforming [C++20](http://www.open-std.org/jtc1/sc22/wg21/prot/14882fdis/n4860.pdf) compilers:

| Platform | Compiler | Versions | Build |
| :------- | :------- | :------- | :---- |
| Linux    | GCC            | 10, 11-SVN | [![codecov](https://codecov.io/gh/rhalbersma/tabula/branch/master/graph/badge.svg)](https://codecov.io/gh/rhalbersma/tabula) <br> [![Build Status](https://travis-ci.org/rhalbersma/tabula.svg)](https://travis-ci.org/rhalbersma/tabula) |

Note that this library makes liberal use of C++20 features. Only GCC >= 10 is supported at the moment. Clang and Visual Studio are catching up fast, and will be added as soon as possible.

## Acknowledgments

Special thanks to Fabien Letouzey for a very fruitful exchange of ideas.

## License

Copyright Rein Halbersma 2019-2021.  
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/users/license.html).  
(See accompanying file LICENSE_1_0.txt or copy at [http://www.boost.org/LICENSE_1_0.txt](http://www.boost.org/LICENSE_1_0.txt))
