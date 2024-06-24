#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/padding.hpp>   // padding
#include <fmt/color.h>
#include <fmt/format.h>
#include <format>               // formater, format_to
#include <ranges>               // iota, reverse

template<class Grid, class Lake, tabula::padding Padding>
struct std::formatter<tabula::basic_board<Grid, Lake, Padding>>
{
        constexpr auto parse(auto& ctx)
        {
                return ctx.begin();
        }

        auto format(tabula::basic_board<Grid, Lake, Padding> const& board, auto& ctx) const
        {
                for (auto rank : std::views::iota(0, board.height) | std::views::reverse) {
                        for (auto file : std::views::iota(0, board.width)) {
                                if (auto const square = board.square(file, rank); board.is_valid(square)) {
                                        fmt::format_to(ctx.out(), "{:>4}", board.embedded(square));
                                } else {
                                        fmt::format_to(ctx.out(), "{:>4}", "");
                                }
                                if (file == board.width - 1) {
                                        std::format_to(ctx.out(), "\n");
                                }
                        }
                }
                return ctx.out();
        }
};
