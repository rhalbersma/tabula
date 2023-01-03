#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/grids.hpp>     // basic_rectangle, chequered_rectangle
#include <tabula/lake.hpp>      // basic_lake_, algebraic_
#include <tabula/padding.hpp>   // basic_padding, right_padding

namespace tabula::draughts {

template<int Width, int Height, int Parity = 0, class Padding = right_padding<1>, class Lake = basic_lake_<>>
using basic_draughts = basic_board<
        chequered_rectangle<Width, Height, Parity, Lake>,
        Padding
>;

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
using frisian           = basic_draughts<10, 10, 0, right_padding<2>>;
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
using mertens_cut_j10   = basic_draughts<10, 10, 0, right_padding<1>, basic_lake_<algebraic_<'j',10>>>;
using mertens_add_k9    = basic_draughts<11, 10, 0, right_padding<1>, basic_lake_<algebraic_<'k',7>, algebraic_<'k',5>, algebraic_<'k',3>, algebraic_<'k',1>>>;

using turkish           = basic_board<basic_rectangle<8, 8>, right_padding<1>>;
using dameo             = turkish;

}       // namespace tabula::draughts
