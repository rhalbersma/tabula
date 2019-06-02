#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/direction.hpp>         // basic_direction
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // flip_t, flop_t, swap_t, padded_t
#include <optional>                     // optional

namespace tabula {

template<class Shape, class Padding>
struct basic_embedding
{
        using shape_type = Shape;
        using padding_type = Padding;
        using padded_type = padded_t<Shape, Padding>;

        using square_type = basic_square<Shape>;
        using padded_square_type = basic_square<padded_type>;
        using padded_direction_type = basic_direction<padded_type>;

        static constexpr auto first_valid = []() -> std::optional<square_type> {
                for (auto r = 0; r < Shape::height; ++r) {
                        for (auto f = 0; f < Shape::width; ++f) {
                                if (auto const sq = square_type{f, r}; sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(first_valid && first_valid->is_valid());

        static constexpr auto last_valid = []() -> std::optional<square_type> {
                for (auto r = Shape::height - 1; r >= 0; --r) {
                        for (auto f = Shape::width - 1; f >= 0; --f) {
                                if (auto const sq = square_type{f, r}; sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(last_valid && last_valid->is_valid());

        static constexpr auto size = Shape::size;
        static constexpr auto padded_size = padded_type::size;

        static constexpr auto to_padded(square_type const& sq)
                -> padded_square_type
        {
                return { sq.file() + Padding::left, sq.rank() + Padding::bottom };
        }
        static constexpr auto valid_padded_size = to_padded(*last_valid).index() - to_padded(*first_valid).index() + 1;

        using flip_type = basic_embedding<flip_t<Shape>, Padding>;
        using flop_type = basic_embedding<flop_t<Shape>, Padding>;
        using swap_type = basic_embedding<swap_t<Shape>, Padding>;

        constexpr auto flip() const noexcept -> flip_type { return {}; }
        constexpr auto flop() const noexcept -> flop_type { return {}; }
        constexpr auto swap() const noexcept -> swap_type { return {}; }
};

}   // namespace tabula
