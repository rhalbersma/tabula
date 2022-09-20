#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <concepts>     // convertible_to, same_as
#include <utility>      // declval, pair

namespace tabula {

template<class Grid>
concept chequered = requires
{
        { Grid::parity                                          } -> std::convertible_to<bool>;
        { Grid::is_colored(std::declval<std::pair<int, int>>()) } -> std::       same_as<bool>;
};

}       // namespace tabula
