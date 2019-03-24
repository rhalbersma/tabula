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
                basic_board<draughts::nano>{},
                basic_board<draughts::micro>{},
                basic_board<draughts::checkers>{},
                basic_board<draughts::latin>{},
                basic_board<draughts::international>{},
                basic_board<draughts::frisian>{},
                basic_board<draughts::canadian>{},
                basic_board<draughts::sri_lankan>{},
                basic_board<draughts::dumm>{},
                basic_board<draughts::spantsiretti>{},
                basic_board<draughts::ktar<10, 11>>{},
                basic_board<draughts::ktar<10, 12>>{},

                // chequered boards with lakes
                basic_board<draughts::mertens_cut_j10>{},
                basic_board<draughts::mertens_add_k9>{},

                // draughts variant played on a non-chequered board
                basic_board<draughts::turkish>{},

                // stratego variants
                basic_board<stratego::l_attaque>{},
                basic_board<stratego::classic>{},
                basic_board<stratego::quick_arena>{}
        );

        boost::hana::for_each(boards, [](auto b) {
                std::cout << format_square::algebraic << b << '\n';
                std::cout << "W = " << b.width << ", H = " << b.height;
                using shape_type = shape_t<decltype(b)>;
                if constexpr (is_chequered<shape_type>) {
                        std::cout << ", C = " << shape_type::coloring << ", J = " << shape_type::is_orthogonal_jumps;
                }
                std::cout << '\n';
                std::cout << "embedding " << b.size << " external squares in " << b.embedding_size << " internal squares " << '\n';
                std::cout << "directional strides: ";
                constexpr auto strides = b.strides;
                std::copy(strides.begin(), strides.end(), std::experimental::ostream_joiner(std::cout, ','));
                std::cout << '\n';
                std::cout << "-----------------------------------------------------------\n";
        });
}
