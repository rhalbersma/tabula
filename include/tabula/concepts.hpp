#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <concepts>     // convertible_to, same_as

namespace tabula {

template<class Grid>
concept chequered = requires
{
        { Grid::parity } -> std::convertible_to<bool>;
};

template<class Coordinates>
concept transformable = requires(Coordinates&& coordinates)
{
        { coordinates.flip() };
        { coordinates.flop() };
        { coordinates.swap() };
};

}       // namespace tabula
