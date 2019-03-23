#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/direction.hpp>         // basic_direction
#include <tabula/square.hpp>            // basic_square
#include <tabula/type_traits.hpp>       // wrap_t, flip_t, flop_t, swap_t
#include <optional>                     // optional

namespace tabula {

template<class Shape>
class basic_embedding
{
        using embedded_square_type = basic_square<Shape>;
        constexpr static auto last_valid_square = []() -> std::optional<embedded_square_type> {
                for (auto r = Shape::height - 1; r >= 0; --r) {
                        for (auto f = Shape::width - 1; f >= 0; --f) {
                                if (auto const sq = embedded_square_type{f, r}; sq.is_valid()) {
                                        return sq;
                                }
                        }
                }
                return {};
        }();
        static_assert(last_valid_square && last_valid_square->is_valid());
public:
        using    square_type = basic_square   <wrap_t<Shape>>;
        using direction_type = basic_direction<wrap_t<Shape>>;

        constexpr static auto embedded_size = Shape::size;
        constexpr static auto size = square_type{*last_valid_square}.index() + 1;

        using flip_type = basic_embedding<flip_t<Shape>>;
        using flop_type = basic_embedding<flop_t<Shape>>;
        using swap_type = basic_embedding<swap_t<Shape>>;

        constexpr auto flip() const noexcept
                -> flip_type
        {
                return {};
        }

        constexpr auto flop() const noexcept
                -> flop_type
        {
                return {};
        }

        constexpr auto swap() const noexcept
                -> swap_type
        {
                return {};
        }
};

}   // namespace tabula
