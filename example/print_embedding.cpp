//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>     // basic_board
#include <tabula/format.hpp>    // print
#include <tabula/games.hpp>     // chess, draughts, stratego
#include <tabula/padding.hpp>   // padding, pad_right
#include <tabula/tuple.hpp>     // for_each
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <print>                // print, println
#include <tuple>                // tuple

int main()
{
        using namespace tabula;
        constexpr auto boards = std::tuple
        {       draughts::nano{}
        ,       draughts::micro{}
        ,       draughts::checkers{}
        ,       draughts::latin{}
        ,       draughts::international{}
        ,       draughts::frisian{}
        ,       draughts::canadian{}
        ,       draughts::sri_lankan{}
        ,       draughts::dumm{}
        ,       draughts::spantsiretti{}
        ,       draughts::ktar<10, 11>{}
        ,       draughts::ktar<10, 12>{}
        ,       basic_draughts<19, 10>{}
        ,       basic_draughts<10, 10, 0, basic_lake<>, pad_right(9)>{}
        ,       draughts::mertens_cut_j10{}
        ,       draughts::mertens_add_k9{}
        ,       draughts::turkish{}
        ,       basic_draughts<10, 10, 0, basic_lake<>, padding{1, 1, 1, 0}>{}
        ,       basic_draughts<10, 10, 0, basic_lake<>, pad_right(9)>{}

        ,       stratego::l_attaque{}
        ,       stratego::classic{}
        ,       stratego::quick_arena{}

        ,       chess::board{}
        ,       chess::board_10x12{}
        ,       chess::board_15x12_33{}
        ,       chess::board_15x12_34{}
        ,       chess::board_15x15{}
        ,       chess::board_16x08{}
        ,       chess::board_16x12{}
        ,       chess::board_16x16{}
        ,       chess::capablanca{}
        ,       chess::grand{}
        };

        for_each(boards, [](auto b) {
                std::println("{}\n", b);
                std::print("config: W = {}, H = {}", b.width, b.height);
                if constexpr (b.is_chequered) {
                        std::print(", P = {}", b.parity());
                }
                std::println(", size = {}", b.size);
                std::print("padded: W = {}, H = {}", b.padded_width, b.padded_height);
                if constexpr (b.is_chequered) {
                        std::print(", P = {}", b.padded_parity());
                }
                std::println(", size = {} ({})", b.padded_size, b.valid_size);
                fmt::println("directional strides: {}", b.strides);     // std::println for libstdc++ does not yet support printing ranges
                std::println("{:->40}", "");
        });
}
