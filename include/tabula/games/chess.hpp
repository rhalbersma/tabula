#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>                     // basic_board
#include <tabula/padding.hpp>                   // basic_padding, right_padding
#include <tabula/shapes/basic_rectangle.hpp>    // basic_rectangle

namespace tabula::chess {

template<int Width, int Height, class Padding>
using board = basic_board<basic_rectangle<Width, Height>, Padding>;

// https://www.chessprogramming.org/10x12_Board
using mailbox_10x12 = board<8, 8, basic_padding<2, 1>>;

// https://www.chessprogramming.org/0x88
using board_0x88 = board<8, 8, right_padding<8>>;

// https://www.chessprogramming.org/Vector_Attacks
using vector_15x12 = board<8, 8, basic_padding<2, 4, 2, 3>>;
using vector_16x12 = board<8, 8, basic_padding<2, 4>>;
using vector_16x16 = board<8, 8, basic_padding<4>>;

}       // namespace tabula::chess
