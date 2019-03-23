#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/lakes.hpp>     // basic_lakes, cut
#include <tabula/shapes.hpp>    // basic_rectangle, chequered_rectangle

namespace tabula::draughts {

using checkers          = chequered_rectangle< 8,  8>;
using american          = checkers;
using english           = checkers;
using czech             = checkers;
using russian           = checkers;
using shashki           = russian;
using thai              = checkers;

using latin             = chequered_rectangle< 8,  8, 0>;
using italian           = latin;
using spanish           = latin;

using international     = chequered_rectangle<10, 10>;
using frisian           = chequered_rectangle<10, 10, 1, 1>;
using canadian          = chequered_rectangle<12, 12>;
using sri_lankan        = chequered_rectangle<12, 12, 0>;
using dumm              = chequered_rectangle<14, 14>;

using nano              = chequered_rectangle< 4,  4>;
using micro             = chequered_rectangle< 6,  6>;

// Rectangular boards with W = H +/- 1 or W = H +/- 2
// yield a winning endgame of 3 kings vs 1 king
using spantsiretti      = chequered_rectangle<10,  8>;

template<int Width, int Height>
using ktar              = chequered_rectangle<Width, Height, 0>;

// Removing square j10 or adding square k9 to the 10x10 board
// yields a winning endgame of 3 kings vs 1 king
using mertens_cut_j10   = chequered_rectangle<10, 10, 1, 0, basic_lakes<cut<'j',10>>>;
using mertens_add_k9    = chequered_rectangle<11, 10, 1, 0, basic_lakes<cut<'k',7>, cut<'k',5>, cut<'k',3>, cut<'k',1>>>;

using turkish           = basic_rectangle< 8, 8>;
using dameo             = turkish;

}       // namespace tabula::draughts
