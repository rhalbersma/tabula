#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/direction.hpp>         // basic_direction
#include <tabula/type_traits.hpp>       // is_chequered
#include <array>                        // array

namespace tabula {

template<class Shape>
class basic_compass
{
        // unit increment for the cardinal directions (N, E, S, W)
        constexpr static auto c = is_chequered<Shape> ? 2 : 1;

        using direction_type = basic_direction<Shape>;
public:
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        constexpr static auto points = std::array
        {
                direction_type{ 0, c},  // N
                direction_type{ 1, 1},  // NE
                direction_type{ c, 0},  // E
                direction_type{ 1,-1},  // SE
                direction_type{ 0,-c},  // S
                direction_type{-1,-1},  // SW
                direction_type{-c, 0},  // W
                direction_type{-1, 1}   // NW
        };
};

}       // namespace tabula

