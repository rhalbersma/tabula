#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t, add_padding
#include <tabula/valid.hpp>             // first_valid_square, last_valid_square

namespace tabula {

template<class Grid, class Padding>
struct basic_embedding
{
        using    grid_type = Grid;
        using padding_type = Padding;

        using flipped_type = basic_embedding<flipped_t<Grid>, Padding>;
        using flopped_type = basic_embedding<flopped_t<Grid>, Padding>;
        using swapped_type = basic_embedding<swapped_t<Grid>, Padding>;

        using padded_type = add_padding<Grid, Padding>;

        [[nodiscard]] static constexpr auto flip() noexcept
                -> flipped_type
        {
                return {};
        }

        [[nodiscard]] static constexpr auto flop() noexcept
                -> flopped_type
        {
                return {};
        }

        [[nodiscard]] static constexpr auto swap() noexcept
                -> swapped_type
        {
                return {};
        }

        [[nodiscard]] static constexpr auto pad(auto const& arg) noexcept
        {
                return arg.template pad<Padding>();
        }

        static constexpr auto valid_size = []() {
                constexpr auto first = first_valid_square<Grid>();
                constexpr auto last = last_valid_square<Grid>();
                if constexpr (first && last) {
                        return last->index() - first->index() + 1;
                } else {
                        0;
                }
        }();
};

}   // namespace tabula
