//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>             // basic_board
#include <tabula/games.hpp>             // draughts, stratego
#include <tabula/ostream.hpp>           // operator<<, format_square
#include <tabula/tuple.hpp>             // for_each, enumerate
#include <tabula/type_traits.hpp>       // is_chequered
#include <algorithm>                    // copy
#include <iostream>                     // cout
#include <iterator>                     // ostream_iterator
#include <tuple>                        // tuple

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
                draughts::ktar<11, 10>(),
                draughts::ktar<12, 10>(),

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
                std::cout << format_square::padded << b << '\n';
                std::cout << "W = " << b.width << ", H = " << b.height;
                using grid_type = grid_t<decltype(b)>;
                if constexpr (is_chequered<grid_type>) {
                        std::cout << ", C = " << grid_type::coloring;
                }
                std::cout << '\n';
                enumerate(mappings, [&](auto i, auto map)  {
                        std::cout << i << ": " << map(b.embedding_v).valid_padded_size << '\n';
                });
                std::cout << "optimal index = " << b.idx << " with size = " << b.valid_padded_size << '\n';
                std::cout << "embedding W = " << b.image_v.width << ", H = " << b.image_v.height;
                std::cout << ", size = " << b.padded_size << " with a valid range of " << b.valid_padded_size << '\n';
                std::cout << "directional strides: ";
                constexpr auto strides = b.strides;
                std::copy(strides.begin(), strides.end(), std::ostream_iterator<int>(std::cout, ","));
                std::cout << '\n';
                std::cout << "-----------------------------------------------------------\n";
        });
}
