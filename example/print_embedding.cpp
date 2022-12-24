//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <tabula/board.hpp>     // basic_board
#include <tabula/format.hpp>    // print
#include <tabula/games.hpp>     // draughts, stratego
#include <tabula/tuple.hpp>     // for_each, enumerate
#include <tuple>                // tuple

int main()
{
        using namespace tabula;
        constexpr auto boards = std::tuple(
                // draughts variants played on chequered boards
                draughts::nano(),
                draughts::micro(),
                draughts::checkers(),
                draughts::latin(),
                draughts::international(),
                draughts::frisian(),
                draughts::canadian(),
                draughts::sri_lankan(),
                draughts::dumm(),
                draughts::spantsiretti(),
                draughts::ktar<10, 11>(),
                draughts::ktar<10, 12>(),
                draughts::basic_draughts<19, 10>(),
                draughts::basic_draughts<10, 10, 0, right_padding<9>>(),

                // chequered boards with irregular shapes
                draughts::mertens_cut_j10(),
                draughts::mertens_add_k9(),

                // draughts variant played on a non-chequered board
                draughts::turkish(),

                // 10x10 draughts with 11x12 mailbox representation
                basic_board<chequered_rectangle<10, 10>, basic_padding<1, 1, 1, 0>>(),

                // 10x10 draughts with 19x10 vector representation
                basic_board<chequered_rectangle<10, 10>, right_padding<9>>(),

                // stratego variants
                stratego::l_attaque(),
                stratego::classic(),
                stratego::quick_arena(),

                // chess board representations
                chess::board(),
                chess::board_10x12(),
                chess::board_15x12_33(),
                chess::board_15x12_34(),
                chess::board_15x15(),
                chess::board_16x08(),
                chess::board_16x12(),
                chess::board_16x16(),
                chess::capablanca(),
                chess::grand()
        );

        for_each(boards, [](auto b) {
                fmt::print("{}\n", b);
                fmt::print("config: W = {}, H = {}", b.width, b.height);
                if constexpr (b.is_chequered) {
                        fmt::print(", P = {}", b.parity());
                }
                fmt::print(", size = {}\n", b.size);
                fmt::print("padded: W = {}, H = {}", b.padded_width, b.padded_height);
                if constexpr (b.is_chequered) {
                        fmt::print(", P = {}", b.padded_parity());
                }
                fmt::print(", size = {} ({})\n", b.padded_size, b.valid_range);
                fmt::print("directional strides: {}\n", b.strides);
                fmt::print("{:->40}\n", "");
        });
}
