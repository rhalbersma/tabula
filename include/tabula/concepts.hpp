#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <concepts>     // convertible_to

namespace tabula {

template<class Grid>
concept chequered = requires
{
        { Grid::parity } -> std::convertible_to<bool>;
};

}       // namespace tabula
