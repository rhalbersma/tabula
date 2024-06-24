#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // id, flip, flop, swap
#include <tabula/tuple.hpp>             // all_of
#include <tuple>                        // get, tuple

namespace tabula {

inline constexpr auto dihedral = std::tuple
(
        id,                     // origin bottom-left, numbering left-to-right, bottom-to-top
        flip,                   // mirror vertically
        flop,                   // mirror horizontally
        swap,                   // mirror diagonally
        swap * flop * flip,     // mirror counterdiagonally
        flop * flip,            // rotate 180 degrees 
        swap * flip,            // rotate 90 degrees counterclockwise
        swap * flop             // rotate 90 degrees clockwise
);

[[nodiscard]] constexpr auto is_identity(auto group, auto element) noexcept
{
        return std::get<0>(group)(element) == element;
}

[[nodiscard]] constexpr auto is_compatibility(auto group, auto element) noexcept
{
        return all_of(group, [=](auto a) {
                return all_of(group, [=](auto b){
                        return (a * b)(element) == a(b(element));
                });
        });
}

[[nodiscard]] constexpr auto is_realized(auto group, auto element) noexcept
{
        return is_identity(group, element) && is_compatibility(group, element);
}

}       // tabula
