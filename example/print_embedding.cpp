//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/board.hpp>             // basic_board
#include <tabula/games.hpp>             // draughts, stratego
#include <tabula/ostream.hpp>           // operator<<, format_square
#include <tabula/type_traits.hpp>       // is_chequered
#include <boost/hana/for_each.hpp>      // for_each
#include <boost/hana/tuple.hpp>         // make_tuple
#include <algorithm>                    // copy
#include <iostream>                     // cout
#include <experimental/iterator>        // ostream_joiner

int main()
{
        using namespace tabula;
        constexpr auto boards = boost::hana::make_tuple(
                // draughts variants played on chequered boards
                draughts::board<2, 5, 1>{},
                draughts::board<2, 5, 0>{},
                draughts::nano{},
                draughts::micro{},
                draughts::checkers{},
                draughts::latin{},
                draughts::international{},
                draughts::frisian{},
                draughts::canadian{},
                draughts::sri_lankan{},
                draughts::dumm{},
                draughts::spantsiretti{},
                draughts::ktar<10, 11>{},
                draughts::ktar<10, 12>{},

                // chequered boards with lakes
                draughts::mertens_cut_j10{},
                draughts::mertens_add_k9{},

                // draughts variant played on a non-chequered board
                draughts::turkish{},

                // 10x10 draughts with 11x12 mailbox representation
                basic_board<chequered_rectangle<10, 10>, basic_padding<1, 1, 1, 0>>{},

                // stratego variants
                stratego::l_attaque{},
                stratego::classic{},
                stratego::quick_arena{},

                // 8x8 chess board representations
                chess::mailbox_10x12{},
                chess::board_0x88{},
                chess::vector_15x12{},
                chess::vector_16x12{},
                chess::vector_16x16{}
        );

        boost::hana::for_each(boards, [](auto b) {
                std::cout << format_square::padded << b << '\n';
                std::cout << "W = " << b.width << ", H = " << b.height;
                using shape_type = shape_t<decltype(b)>;
                if constexpr (is_chequered<shape_type>) {
                        std::cout << ", C = " << shape_type::coloring;
                }
                std::cout << '\n';
                std::cout << b.size << " external squares padded to " << b.padded_size << " internal squares, " << b.valid_padded_size << " of which are valid" << '\n';
                std::cout << "directional strides: ";
                constexpr auto strides = b.strides;
                std::copy(strides.begin(), strides.end(), std::experimental::ostream_joiner(std::cout, ','));
                std::cout << '\n';
                std::cout << "-----------------------------------------------------------\n";
        });
}
