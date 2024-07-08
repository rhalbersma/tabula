#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // operator*, keep, flip, flop, swap
#include <tabula/tuple.hpp>             // all_of
#include <tuple>                        // get, tuple

namespace tabula::group {

inline constexpr auto d8 = std::tuple
{
        idem,                   // e
        swap * flip,            // a   : rotate 90 degrees anticlockwise
        flop * flip,            // a^2 : rotate 180 degrees 
        swap * flop,            // a^3 : rotate 90 degrees clockwise        
        swap,                   // b   : mirror diagonally
        flip,                   // ba  : mirror vertically
        swap * flop * flip,     // ba^2: mirror antidiagonally
        flop,                   // ba^3: mirror horizontally
};

inline constexpr auto d4c = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
        flip,                   // ba  : mirror vertically
        flop,                   // ba^3: mirror horizontally
};

inline constexpr auto c4 = std::tuple
{
        idem,                   // e
        swap * flip,            // a   : rotate 90 degrees anticlockwise
        flop * flip,            // a^2 : rotate 180 degrees 
        swap * flop,            // a^3 : rotate 90 degrees clockwise   
};

inline constexpr auto d4o = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
        swap,                   // b   : mirror diagonally
        swap * flop * flip,     // ba^2: mirror antidiagonally
};

inline constexpr auto d2v = std::tuple
{
        idem,                   // e
        flip,                   // ba  : mirror vertically
};

inline constexpr auto d2h = std::tuple
{
        idem,                   // e
        flop,                   // ba^3: mirror horizontally
};

inline constexpr auto d2r = std::tuple
{
        idem,                   // e
        flop * flip,            // a^2 : rotate 180 degrees 
};

inline constexpr auto c2d = std::tuple
{
        idem,                   // e
        swap,                   // b   : mirror diagonally
};

inline constexpr auto c2a = std::tuple
{
        idem,                   // e
        swap * flop * flip,     // ba^2: mirror antidiagonally
};

[[nodiscard]] constexpr auto is_invariant(auto X, auto G) noexcept
{
        return all_of(G, [=](auto g) {
                return g(X) == X;
        });
}

}       // tabula::group
