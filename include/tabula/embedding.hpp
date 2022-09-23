#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t, add_padding
#include <optional>                     // nullopt, optional

namespace tabula {

template<class Grid, class Padding>
class basic_embedding
{
        [[nodiscard]] static constexpr auto first_valid_index() noexcept
                -> std::optional<int>
        {
                for (auto index = 0; index < Grid::size; ++index) {
                        if (auto const square = Grid::coordinates(index); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

        [[nodiscard]] static constexpr auto last_valid_index() noexcept
                -> std::optional<int>
        {
                for (auto index = Grid::size - 1; index >= 0; --index) {
                        if (auto const square = Grid::coordinates(index); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

public:
        using    grid_type = Grid;
        using padding_type = Padding;

        using padded_type = add_padding<Grid, Padding>;

        [[nodiscard]] static constexpr auto flip() noexcept -> basic_embedding<flipped_t<Grid>, Padding> { return {}; }
        [[nodiscard]] static constexpr auto flop() noexcept -> basic_embedding<flopped_t<Grid>, Padding> { return {}; }
        [[nodiscard]] static constexpr auto swap() noexcept -> basic_embedding<swapped_t<Grid>, Padding> { return {}; }

        [[nodiscard]] static constexpr auto pad(auto coordinates) noexcept
        {
                return coordinates.template pad<Padding>();
        }

        static constexpr auto min_size = []() {
                constexpr auto first = first_valid_index();
                constexpr auto last = last_valid_index();
                return first && last ? *last - *first + 1 : 0;
        }();
};

}   // namespace tabula
