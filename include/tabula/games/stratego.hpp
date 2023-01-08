#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // basic_rectangle
#include <tabula/lake.hpp>      // lake_, algebraic_
#include <tabula/padding.hpp>   // right_padding

namespace tabula::stratego {

template<int Width, int Height, class Lake, padding Padding = right_padding(1)>
using basic_stratego = basic_board<
        basic_rectangle<Width, Height, Lake>,
        Padding
>;

// A precursor to classic Stratego is the game L'Attaque played on a 9x10 board
// with three 1x2 lakes on the 5th and 6th rows of the c, e and g files.
using l_attaque = basic_stratego<
        9, 10, lake_<
                algebraic('c',6), algebraic('e',6), algebraic('g',6),
                algebraic('c',5), algebraic('e',5), algebraic('g',5)
        >
>;

// Classic Stratego is played on a 10x10 board
// with two 2x2 lakes on the 5th and 6th rows of the c, d, g and h files.
using classic = basic_stratego<
        10, 10, lake_<
                algebraic('c',6), algebraic('d',6), algebraic('g',6), algebraic('h',6),
                algebraic('c',5), algebraic('d',5), algebraic('g',5), algebraic('h',5)
        >
>;

// Quick Arena is a variation from stratego.com and is played on an 8x8 board
// with two 1x2 lakes on the 4th and 5th rows of the c and f files.
using quick_arena = basic_stratego<
        8, 8, lake_<
                algebraic('c',5), algebraic('f',5),
                algebraic('c',4), algebraic('f',4)
        >
>;

}       // namespace tabula::stratego
