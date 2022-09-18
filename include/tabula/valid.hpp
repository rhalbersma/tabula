#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // square_t
#include <optional>                     // nullopt, optional

namespace tabula {

template<class Grid, class Square = square_t<Grid>>
[[nodiscard]] constexpr auto first_valid_square() noexcept
        -> std::optional<Square>
{
        for (auto rank = 0; rank < Grid::height; ++rank) {
                for (auto file = 0; file < Grid::width; ++file) {
                        if (auto const square = Square(file, rank); square.is_valid()) {
                                return square;
                        }
                }
        }
        return std::nullopt;
}

template<class Grid, class Square = square_t<Grid>>
[[nodiscard]] constexpr auto last_valid_square() noexcept
        -> std::optional<Square>
{
        for (auto rank = Grid::height - 1; rank >= 0; --rank) {
                for (auto file = Grid::width - 1; file >= 0; --file) {
                        if (auto const square = Square(file, rank); square.is_valid()) {
                                return square;
                        }
                }
        }
        return std::nullopt;
}

}       // namespace tabula
