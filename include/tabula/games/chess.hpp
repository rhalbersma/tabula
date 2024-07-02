#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // rectangle
#include <tabula/lake.hpp>      // basic_lake
#include <tabula/padding.hpp>   // padding, pad_boxed, pad_right

namespace tabula {

template<int Width, int Height, class Lake = basic_lake<>, padding Padding = padding{}>
using basic_chess = basic_board<rectangle{Width, Height}, Lake, Padding>;

namespace chess {

// https://www.chessprogramming.org/8x8_Board
using board_08x08    = basic_chess< 8,  8>;
using board          = board_08x08;

// https://www.chessprogramming.org/10x12_Board
using board_10x12    = basic_chess< 8,  8, basic_lake<>, pad_boxed(2, 1)>;

// https://www.chessprogramming.org/0x88
using board_16x08    = basic_chess< 8,  8, basic_lake<>, pad_right(8)>;
using board_0x88     = board_16x08;

// https://www.chessprogramming.org/Vector_Attacks
using board_15x12_33 = basic_chess< 8,  8, basic_lake<>, padding{2, 4, 2, 3}>;
using board_15x12_34 = basic_chess< 8,  8, basic_lake<>, padding{2, 3, 2, 4}>;
using board_15x15    = basic_chess< 8,  8, basic_lake<>, padding{4, 4, 3, 3}>;
using board_16x12    = basic_chess< 8,  8, basic_lake<>, pad_boxed(2, 4)>;
using board_16x16    = basic_chess< 8,  8, basic_lake<>, pad_boxed(4, 4)>;

// https://en.wikipedia.org/wiki/Capablanca_chess
using capablanca     = basic_chess<10,  8, basic_lake<>, pad_boxed(2, 1)>;

// https://en.wikipedia.org/wiki/Grand_chess
using grand          = basic_chess<10, 10, basic_lake<>, pad_boxed(2, 1)>;

}       // namespace chess
}       // namespace tabula
