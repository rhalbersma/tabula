//          Copyright Rein Halbersma 2019-2026.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef TABULA_FORMAT_HPP
#define TABULA_FORMAT_HPP

#include <tabula/board.hpp>     // basic_board
#include <tabula/padding.hpp>   // padding
#include <format>               // formatter, format_to
#include <ranges>               // iota, reverse

// A basic_board renders as its embedded squares, rank by rank from the top.
// Specializing std::formatter on a program-defined type is the only mechanism
// the standard offers for that, and [namespace.std]/2 expressly permits it.
template<auto Grid, class Lake, tabula::padding Padding>
// NOLINTNEXTLINE(bugprone-std-namespace-modification): permitted by [namespace.std]/2, see above
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

#endif // TABULA_FORMAT_HPP
