#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/padding.hpp>   // padding
#include <format>               // formater, format_to
#include <ranges>               // iota, reverse

template<class Grid, tabula::padding Padding>
struct std::formatter<tabula::basic_board<Grid, Padding>>
{
        constexpr auto parse(auto& ctx)
        {
                return ctx.begin();
        }

        auto format(tabula::basic_board<Grid, Padding> const& board, auto& ctx) const
        {
                for (auto rank : std::views::iota(0, board.height) | std::views::reverse) {
                        for (auto file : std::views::iota(0, board.width)) {
                                if (auto const square = board.square(file, rank); square.is_valid()) {
                                        std::format_to(ctx.out(), "{:>4}", board.embedded(square));
                                } else {
                                        std::format_to(ctx.out(), "{:>4}", "");
                                }
                                if (file == board.width - 1) {
                                        std::format_to(ctx.out(), "\n");
                                }
                        }
                }
                return ctx.out();
        }
};
