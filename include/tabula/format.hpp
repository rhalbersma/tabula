#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <tabula/board.hpp>
#include <tabula/square.hpp>

template<class Grid, class Padding>
struct fmt::formatter<tabula::basic_board<Grid, Padding>> 
{
        // Presentation format: 'f' - fixed, 'e' - exponential.
        char presentation = 'f';

        // Parses format specifications of the form ['f' | 'e'].
        constexpr auto parse(format_parse_context& ctx) 
        {
                // auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) // c++11
                // [ctx.begin(), ctx.end()) is a character range that contains a part of
                // the format string starting from the format specifications to be parsed,
                // e.g. in
                //
                //   fmt::format("{:f} - point of interest", point{1, 2});
                //
                // the range will contain "f} - point of interest". The formatter should
                // parse specifiers until '}' or the end of the range. In this example
                // the formatter should parse the 'f' specifier and return an iterator
                // pointing to '}'.

                // Return an iterator past the end of the parsed range:
                // TODO!!
                return ctx.end();
        }

        // Formats the point p using the parsed format specification (presentation)
        // stored in this formatter.
        template<typename FormatContext>
        auto format(tabula::basic_board<Grid, Padding> const& b, FormatContext& ctx) 
        {
                for (auto r = b.height - 1; r >= 0; --r) {
                        for (auto f = 0; f < b.width; ++f) {
                                if (auto const sq = b.square(f, r); sq.is_valid()) {
                                        format_to(ctx.out(), "{:>4}", b.padded(sq));
                                } else {
                                        format_to(ctx.out(), "{:>4}", "");
                                }
                                if (f == b.width - 1) {
                                        format_to(ctx.out(), "\n");
                                }
                        }
                }
                return ctx.out();
        }
};
