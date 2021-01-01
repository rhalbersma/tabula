#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // basic_rectangle
#include <tabula/padding.hpp>   // basic_padding, right_padding

namespace tabula::chess {

template<int Width, int Height, class Padding>
using basic_chess    = basic_board<basic_rectangle<Width, Height>, Padding>;

// https://www.chessprogramming.org/8x8_Board
using board_08x08    = basic_chess< 8,  8, basic_padding<0>>;
using board          = board_08x08;

// https://www.chessprogramming.org/10x12_Board
using board_10x12    = basic_chess< 8,  8, basic_padding<2, 1>>;
using mailbox        = board_10x12;

// https://www.chessprogramming.org/0x88
using board_16x08    = basic_chess< 8,  8, right_padding<8>>;
using board_0x88     = board_16x08;

// https://www.chessprogramming.org/Vector_Attacks
using board_15x12_33 = basic_chess< 8,  8, basic_padding<2, 4, 2, 3>>;
using board_15x12_34 = basic_chess< 8,  8, basic_padding<2, 3, 2, 4>>;
using board_15x15    = basic_chess< 8,  8, basic_padding<4, 4, 3, 3>>;
using board_16x12    = basic_chess< 8,  8, basic_padding<2, 4>>;
using board_16x16    = basic_chess< 8,  8, basic_padding<4>>;

// https://en.wikipedia.org/wiki/Capablanca_chess
using capablanca     = basic_chess<10,  8, basic_padding<2, 1>>;

// https://en.wikipedia.org/wiki/Grand_chess
using grand          = basic_chess<10, 10, basic_padding<2, 1>>;

}       // namespace tabula::chess
