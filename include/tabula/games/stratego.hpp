#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>                     // basic_board
#include <tabula/lakes.hpp>                     // basic_lakes, cut
#include <tabula/padding.hpp>                   // right_padding
#include <tabula/shapes/basic_rectangle.hpp>    // basic_rectangle

namespace tabula::stratego {

template<class Shape>
using board = basic_board<Shape, basic_padding<1>>;

// A precursor to classic Stratego is the game L'Attaque played on a 9x10 board
// with three 1x2 lakes on the 5th and 6th rows of the c, e and g files.
using l_attaque = board<basic_rectangle<9, 10, basic_lakes<
        cut<'c',6>,     cut<'e',6>,     cut<'g',6>,
        cut<'c',5>,     cut<'e',5>,     cut<'g',5>
>>>;

// Classic Stratego is played on a 10x10 board
// with two 2x2 lakes on the 5th and 6th rows of the c/d and g/h files.
using classic = board<basic_rectangle<10, 10, basic_lakes<
        cut<'c',6>,cut<'d',6>,  cut<'g',6>,cut<'h',6>,
        cut<'c',5>,cut<'d',5>,  cut<'g',5>,cut<'h',5>
>>>;

// Quick Arena is a variation from stratego.com and is played on an 8x8 board
// with two 1x2 lakes on the 4th and 5th rows of the c and f files.
using quick_arena = board<basic_rectangle<8, 8, basic_lakes<
        cut<'c',5>,     cut<'f',5>,
        cut<'c',4>,     cut<'f',4>
>>>;

}       // namespace tabula::stratego
