#pragma once

//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // chequer, rectangle
#include <tabula/lake.hpp>      // basic_lake, algebraic_
#include <tabula/padding.hpp>   // padding, pad_right

namespace tabula {

template<int Width, int Height, bool Parity = false, class Lake = basic_lake<>, padding Padding = pad_right(1)>
using basic_draughts = basic_board<chequer{Width, Height, Parity}, Lake, Padding>;

namespace draughts {

using nano              = basic_draughts< 4,  4>;
using micro             = basic_draughts< 6,  6>;

using checkers          = basic_draughts< 8,  8>;
using american          = checkers;
using english           = checkers;
using czech             = checkers;
using russian           = checkers;
using shashki           = russian;
using thai              = checkers;

using latin             = basic_draughts< 8,  8, 1>;
using italian           = latin;
using spanish           = latin;

using international     = basic_draughts<10, 10>;
using frisian           = basic_draughts<10, 10, 0, basic_lake<>, pad_right(2)>;
using canadian          = basic_draughts<12, 12>;
using sri_lankan        = basic_draughts<12, 12, 1>;
using dumm              = basic_draughts<14, 14>;

// Rectangular boards with W = H +/- 1 or W = H +/- 2
// yield a winning endgame of 3 kings vs 1 king.
using spantsiretti      = basic_draughts<10,  8>;

template<int Width, int Height>
using ktar              = basic_draughts<Width, Height, 1>;

// Removing square j10 or adding square k9 to the 10x10 board
// yields a winning endgame of 3 kings vs 1 king.
using namespace tabula::square_literals;
using mertens_cut_j10   = basic_draughts<10, 10, 0, basic_lake<"j10"_sq>>;
using mertens_add_k9    = basic_draughts<11, 10, 0, basic_lake<"k7"_sq, "k5"_sq, "k3"_sq, "k1"_sq>>;

using turkish           = basic_board<rectangle{8, 8}, basic_lake<>, pad_right(1)>;
using dameo             = turkish;

}       // namespace draughts
}       // namespace tabula
