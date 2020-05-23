#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // basic_rectangle
#include <tabula/padding.hpp>   // basic_padding, right_padding

namespace tabula::chess {

template<int Width, int Height, class Padding = basic_padding<0>>
using board = basic_board<basic_rectangle<Width, Height>, Padding>;

// https://www.chessprogramming.org/8x8_Board
using board_08x08    = board<8, 8>;

// https://www.chessprogramming.org/10x12_Board
using board_10x12    = board<8, 8, basic_padding<2, 1>>;

// https://www.chessprogramming.org/0x88
using board_16x08    = board<8, 8, right_padding<8>>;

// https://www.chessprogramming.org/Vector_Attacks
using board_15x12_33 = board<8, 8, basic_padding<2, 4, 2, 3>>;
using board_15x12_34 = board<8, 8, basic_padding<2, 3, 2, 4>>;
using board_15x15    = board<8, 8, basic_padding<4, 4, 3, 3>>;
using board_16x12    = board<8, 8, basic_padding<2, 4>>;
using board_16x16    = board<8, 8, basic_padding<4>>;

}       // namespace tabula::chess
