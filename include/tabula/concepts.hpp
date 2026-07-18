#pragma once

//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <concepts>     // convertible_to

namespace tabula {

template<auto Grid>
concept rectangular = requires
{
        { Grid.width  } -> std::convertible_to<int>;
        { Grid.height } -> std::convertible_to<int>;
};

template<auto Grid>
concept chequered = rectangular<Grid> && requires
{
        { Grid.parity } -> std::convertible_to<bool>;
};

}       // namespace tabula
