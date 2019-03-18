#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>                   // basic_compass
#include <tabula/direction.hpp>                 // basic_direction
#include <tabula/embedding.hpp>                 // basic_embedding
#include <tabula/functional.hpp>                // flip_fn, flop_fn, swap_fn
#include <tabula/lakes.hpp>                     // basic_lakes
#include <tabula/square.hpp>                    // basic_square
#include <tabula/type_traits.hpp>               // is_chequered, square_t, direction_t, flip_t
#include <boost/hana/functional/compose.hpp>    // compose
#include <boost/hana/functional/id.hpp>         // id
#include <boost/hana/integral_constant.hpp>     // int_c
#include <boost/hana/minimum.hpp>               // minimum.by
#include <boost/hana/ordering.hpp>              // ordering
#include <boost/hana/reverse.hpp>               // reverse
#include <boost/hana/tuple.hpp>                 // make_tuple
#include <array>                                // array
#include <cstddef>                              // size_t
#include <optional>                             // optional

namespace tabula {

inline constexpr auto transforms = boost::hana::reverse(boost::hana::make_tuple(
        boost::hana::id,                                // origin at lower-left, left-to-right, bottom-to-top
        swap_fn,                                        // origin at lower-left, bottom-to-top, left-to-right
        flip_fn,                                        // origin at upper-left, left-to-right, top-to-bottom
        boost::hana::compose(swap_fn, flip_fn),         // origin at upper-left, top-to-bottom, left-to-right
        flop_fn,                                        // origin at lower-right, right-to-left, bottom-to-top
        boost::hana::compose(swap_fn, flop_fn),         // origin at lower-right, bottom-to-top, right-to-left
        boost::hana::compose(flop_fn, flip_fn),         // origin at upper-right, right-to-left, top-to-bottom
        boost::hana::compose(swap_fn, flop_fn, flip_fn) // origin at upper-right, top-to-bottom, right-to-left
));

template<class Shape>
class basic_board
{
        constexpr static auto embedding_v = basic_embedding<Shape>{};
        constexpr static auto transform_v = boost::hana::minimum.by(boost::hana::ordering([](auto fun) {
                return boost::hana::int_c<fun(embedding_v).size>;
        }), transforms);
        constexpr static auto embedding_image_v = transform_v(embedding_v);

        using direction_type = basic_direction<Shape>;
        using embedding_direction_type = direction_t<decltype(embedding_image_v)>;

        using algebraic_square_type = basic_square<Shape>;
        using   numeric_square_type = flip_t<algebraic_square_type>;
        using embedding_square_type = square_t<decltype(embedding_image_v)>;

        constexpr static auto numeric_square(algebraic_square_type const& sq) // Throws: Nothing.
        {
                return sq.flip();
        }

        constexpr static auto embedding_square(algebraic_square_type const& sq) // Throws: Nothing.
                -> embedding_square_type
        {
                return transform_v(sq);
        }

        inline const static auto algebraic_table = []() {
                std::array<std::optional<algebraic_square_type>, embedding_image_v.size> table{};
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = algebraic_square_type{f, r}; sq.is_valid()) {
                                        table[static_cast<std::size_t>(embedding_square(sq).index())] = sq;
                                }
                        }
                }
                return table;
        }();

        constexpr static auto numeric_table = []() {
                std::array<std::optional<int>, embedding_image_v.size> table{};
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = algebraic_square_type{f, r}; sq.is_valid()) {
                                        table[static_cast<std::size_t>(embedding_square(sq).index())] = numeric_square(sq).index();
                                }
                        }
                }
                return table;
        }();

        constexpr static auto embedding_table = []() {
                std::array<std::optional<int>, embedding_image_v.embedded_size> table{};
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = algebraic_square_type{f, r}; sq.is_valid()) {
                                        table[static_cast<std::size_t>(numeric_square(sq).index())] = embedding_square(sq).index();
                                }
                        }
                }
                return table;
        }();
public:
        constexpr static auto width = Shape::width;
        constexpr static auto height = Shape::height;
        using shape_type = Shape;

        constexpr static auto size = embedding_image_v.embedded_size;
        constexpr static auto embedding_size = embedding_image_v.size;

        using square_type = algebraic_square_type;

        constexpr static auto square(int f, int r) // Throws: Nothing.
                -> square_type
        {
                return { f, r };
        }

        static auto algebraic(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < embedding_size);
                auto const t = algebraic_table[static_cast<std::size_t>(i)];
                assert(t);
                return *t;
        }

        static auto algebraic(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return algebraic(embedding_square(sq).index());
        }

        constexpr static auto numeric0(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < embedding_size);
                auto const t = numeric_table[static_cast<std::size_t>(i)];
                assert(t);
                return *t;
        }

        constexpr static auto numeric1(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < embedding_size);
                return numeric0(i) + 1;
        }

        constexpr static auto numeric0(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return numeric0(embedding_square(sq).index());
        }

        constexpr static auto numeric1(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return numeric1(embedding_square(sq).index());
        }

        constexpr static auto embedding0(int n0) // Throws: Nothing.
        {
                assert(0 <= n0 && n0 < size);
                auto const t = embedding_table[static_cast<std::size_t>(n0)];
                assert(t);
                return *t;
        }

        constexpr static auto embedding1(int n1) // Throws: Nothing.
        {
                assert(1 <= n1 && n1 <= size);
                return embedding0(n1 - 1);
        }

        constexpr static auto embedding(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return embedding0(numeric_square(sq).index());
        }

        constexpr static auto strides = []() {
                constexpr auto points = basic_compass<Shape>{}.points;
                std::array<int, points.size()> table{};
                auto i = std::size_t{0};
                for (auto p : points) {
                        table[i++] = embedding_direction_type{transform_v(p)}.stride();
                }
                return table;
        }();
};

}   // namespace tabula

