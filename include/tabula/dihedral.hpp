#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // operator*, keep, flip, flop, swap
#include <tabula/tuple.hpp>             // all_of
#include <tuple>                        // get, tuple

namespace tabula::group {

// Symmetry group of squares (N x N) or odd-sized chequered squares (2N+1 x 2N+1).
inline constexpr auto d4 = std::tuple
{
        idem,                   // e
        swap * flip,            // a   : rotate 90 degrees anticlockwise
        flop * flip,            // a^2 : rotate 180 degrees 
        swap * flop,            // a^3 : rotate 90 degrees clockwise        
        swap,                   // b   : mirror diagonally
        flip,                   // ba  : mirror vertically
        swap * flop * flip,     // ba^2: mirror antidiagonally
        flop,                    // ba^3: mirror horizontally
};

inline constexpr auto z4 = std::tuple
{
        idem,                   // e
        swap * flip,            // a   : rotate 90 degrees anticlockwise
        flop * flip,            // a^2 : rotate 180 degrees 
        swap * flop             // a^3 : rotate 90 degrees clockwise   
};

// Symmetry group of even-sized chequered squares (2N x 2N).
inline constexpr auto d2o = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
        swap,                   // b   : mirror diagonally
        swap * flop * flip,     // ba^2: mirror antidiagonally
};

// Symmetry group of rectangles (W x H) or odd-sized chequered rectangles (2W+1 x 2H+1).
inline constexpr auto d2c = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
        flip,                   // ba  : mirror vertically
        flop,                   // ba^3: mirror horizontally
};

inline constexpr auto z2d = std::tuple
{
        idem,                   // e
        swap,                   // b   : mirror diagonally
};

inline constexpr auto z2a = std::tuple
{
        idem,                   // e
        swap * flop * flip,     // ba^2: mirror antidiagonally
};

// Symmetry grouop of even-sized chequered rectangles (2W x 2H).
inline constexpr auto d1r = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
};

// Symmetry group of chequered rectangles with even width and odd height (2W x 2H+1).
inline constexpr auto d1v = std::tuple
{
        idem,                   // e
        flip,                   // ba  : mirror vertically
};

// Symmetry group of chequered rectangles with odd width and even height (2W+1 x 2H).
inline constexpr auto d1h = std::tuple
{
        idem,                   // e
        flop,                   // ba^3: mirror horizontally
};

[[nodiscard]] constexpr auto is_invariant(auto X, auto G) noexcept
{
        return all_of(G, [=](auto g) {
                return g(X) == X;
        });
}

}       // tabula::group
