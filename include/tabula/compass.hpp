#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/concepts.hpp>  // chequered
#include <tabula/vector.hpp>    // basic_vector
#include <array>                // array

namespace tabula {

template<class Grid>
class basic_compass
{
        // unit increment for the cardinal directions (N, E, S, W)
        static constexpr auto c = chequered<Grid> ? 2 : 1;

        using vector = basic_vector<Grid>;
public:
        enum : unsigned { N, NE, E, SE, S, SW, W, NW };

        static constexpr auto points = std::array{
                vector{ 0,  c},  // N
                vector{ 1,  1},  // NE
                vector{ c,  0},  // E
                vector{ 1, -1},  // SE
                vector{ 0, -c},  // S
                vector{-1, -1},  // SW
                vector{-c,  0},  // W
                vector{-1,  1}   // NW
        };
};

}       // namespace tabula
