#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/compass.hpp>           // basic_compass
#include <tabula/direction.hpp>         // basic_direction
#include <tabula/embedding.hpp>         // basic_embedding
#include <tabula/functional.hpp>        // flip_fn, flop_fn, swap_fn
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/point.hpp>             // basic_point
#include <tabula/type_traits.hpp>       // is_chequered, square_t, direction_t, flip_t
#include <array>                        // array
#include <cstddef>                      // size_t
#include <optional>                     // optional
#include <tuple>                        // get, make_tuple

namespace tabula {

inline constexpr auto transforms = std::make_tuple(
        keep_arg,                               // origin at lower-left, left-to-right, bottom-to-top
        swap_arg,                               // origin at lower-left, bottom-to-top, left-to-right
        flip_arg,                               // origin at upper-left, left-to-right, top-to-bottom
        compose(swap_arg, flip_arg),            // origin at upper-left, top-to-bottom, left-to-right
        flop_arg,                               // origin at lower-right, right-to-left, bottom-to-top
        compose(swap_arg, flop_arg),            // origin at lower-right, bottom-to-top, right-to-left
        compose(flop_arg, flip_arg),            // origin at upper-right, right-to-left, top-to-bottom
        compose(swap_arg, flop_arg, flip_arg)   // origin at upper-right, top-to-bottom, right-to-left
);

template<class Shape, class Padding>
struct basic_board
{
        static constexpr auto embedding_v = basic_embedding<Shape, Padding>{};
        static constexpr auto idx = min_element_by(transforms, [](auto fun) {
                return fun(embedding_v).valid_padded_size;
        });
        static constexpr auto transform_v = std::get<idx>(transforms);
        static constexpr auto image_v = transform_v(embedding_v);

        using square_type = basic_point<Shape>;
        using direction_type = basic_direction<Shape>;
        using padded_square_type = typename decltype(image_v)::padded_square_type;
        using padded_direction_type = typename decltype(image_v)::padded_direction_type;

        static constexpr auto to_sequential(square_type const& sq) noexcept
        {
                return sq.flip();
        }

        static constexpr auto to_padded(square_type const& sq) noexcept
        {
                return image_v.to_padded(transform_v(sq));
        }

        static constexpr auto to_padded(direction_type const& dir) noexcept
                -> padded_direction_type
        {
                auto const t = transform_v(dir);
                return { t.delta_file(), t.delta_rank() };
        }

        static constexpr auto padded2sequential_table = []() {
                std::array<std::optional<int>, image_v.padded_size> table{};
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = square_type{f, r}; sq.is_valid()) {
                                        table[static_cast<std::size_t>(to_padded(sq).index())] = to_sequential(sq).index();
                                }
                        }
                }
                return table;
        }();

        static constexpr auto sequential2padded_table = []() {
                std::array<std::optional<int>, image_v.size> table{};
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = square_type{f, r}; sq.is_valid()) {
                                        table[static_cast<std::size_t>(to_sequential(sq).index())] = to_padded(sq).index();
                                }
                        }
                }
                return table;
        }();
public:
        static constexpr auto width = Shape::width;
        static constexpr auto height = Shape::height;
        using shape_type = Shape;
        using padding_type = Padding;

        static constexpr auto size = image_v.size;
        static constexpr auto padded_size = image_v.padded_size;
        static constexpr auto valid_padded_size = image_v.valid_padded_size;

        static constexpr auto square(int f, int r) // Throws: Nothing.
                -> square_type
        {
                return { f, r };
        }

        static constexpr auto sequential0(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < padded_size);
                auto const t = padded2sequential_table[static_cast<std::size_t>(i)];
                assert(t);
                return *t;
        }

        static constexpr auto sequential1(int i) // Throws: Nothing.
        {
                assert(0 <= i && i < padded_size);
                return sequential0(i) + 1;
        }

        static constexpr auto sequential0(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential0(to_padded(sq).index());
        }

        static constexpr auto sequential1(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return sequential1(to_padded(sq).index());
        }

        static constexpr auto padded0(int n0) // Throws: Nothing.
        {
                assert(0 <= n0 && n0 < size);
                auto const t = sequential2padded_table[static_cast<std::size_t>(n0)];
                assert(t);
                return *t;
        }

        static constexpr auto padded1(int n1) // Throws: Nothing.
        {
                assert(1 <= n1 && n1 <= size);
                return padded0(n1 - 1);
        }

        static constexpr auto padded(square_type const& sq) // Throws: Nothing.
        {
                assert(sq.is_valid());
                return padded0(to_sequential(sq).index());
        }

        static constexpr auto strides = []() {
                constexpr auto points = basic_compass<Shape>{}.points;
                std::array<int, points.size()> table{};
                auto i = std::size_t{0};
                for (auto p : points) {
                        table[i++] = to_padded(p).stride();
                }
                return table;
        }();
};

}   // namespace tabula
