#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // rectangle
#include <tabula/lake.hpp>      // basic_lake, algebraic_
#include <tabula/padding.hpp>   // pad_right

namespace tabula {

template<int Width, int Height, class Lake, padding Padding = pad_right(1)>
using basic_stratego = basic_board<rectangle{Width, Height}, Lake, Padding>;

namespace stratego {

using namespace tabula::square_literals;

// A precursor to classic Stratego is the game L'Attaque, which is played on a 9x10 board
// with three 1x2 lakes on the 5th and 6th rows of the c, e and g files.
using l_attaque = basic_stratego<9, 10, basic_lake<
        "c6"_sq,        "e6"_sq,        "g6"_sq,
        "c5"_sq,        "e5"_sq,        "g5"_sq
>>;

// Classic Stratego is played on a 10x10 board
// with two 2x2 lakes on the 5th and 6th rows of the c, d, g and h files.
using classic = basic_stratego<10, 10, basic_lake<
        "c6"_sq, "d6"_sq,       "g6"_sq, "h6"_sq,
        "c5"_sq, "d5"_sq,       "g5"_sq, "h5"_sq
>>;

// Quick Arena is a variation from stratego.com which is played on an 8x8 board
// with two 1x2 lakes on the 4th and 5th rows of the c and f files.
using quick_arena = basic_stratego<8, 8, basic_lake<
        "c5"_sq,        "f5"_sq,
        "c4"_sq,        "f4"_sq
>>;

}       // namespace stratego
}       // namespace tabula
