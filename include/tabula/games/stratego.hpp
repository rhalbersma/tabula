#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // basic_rectangle
#include <tabula/lakes.hpp>     // basic_lakes, cut
#include <tabula/padding.hpp>   // right_padding

namespace tabula::stratego {

template<int Width, int Height, class... Cuts>
using basic_stratego = basic_board<
        basic_rectangle<Width, Height, basic_lakes<Cuts...>>, 
        right_padding<1>
>;

// A precursor to classic Stratego is the game L'Attaque played on a 9x10 board
// with three 1x2 lakes on the 5th and 6th rows of the c, e and g files.
using l_attaque = basic_stratego<
        9, 10,
        cut<'c',6>, cut<'e',6>, cut<'g',6>,
        cut<'c',5>, cut<'e',5>, cut<'g',5>
>;

// Classic Stratego is played on a 10x10 board
// with two 2x2 lakes on the 5th and 6th rows of the c, d, g and h files.
using classic = basic_stratego<
        10, 10,
        cut<'c',6>, cut<'d',6>, cut<'g',6>, cut<'h',6>,
        cut<'c',5>, cut<'d',5>, cut<'g',5>, cut<'h',5>
>;

// Quick Arena is a variation from stratego.com and is played on an 8x8 board
// with two 1x2 lakes on the 4th and 5th rows of the c and f files.
using quick_arena = basic_stratego<
        8, 8,
        cut<'c',5>, cut<'f',5>,
        cut<'c',4>, cut<'f',4>
>;

}       // namespace tabula::stratego
