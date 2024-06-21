#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>           // padding
#include <tabula/type_traits.hpp>       // flipped_t, flopped_t, swapped_t, padded_t
#include <optional>                     // nullopt, optional
#include <ranges>                       // iota, reverse

namespace tabula {

template<class Grid, padding Padding>
class basic_embedding
{
        [[nodiscard]] static constexpr auto first_valid_index() noexcept
                -> std::optional<int>
        {
                for (auto index : std::views::iota(0, Grid::size)) {
                        if (auto const square = Grid::square(index); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

        [[nodiscard]] static constexpr auto last_valid_index() noexcept
                -> std::optional<int>
        {
                for (auto index : std::views::iota(0, Grid::size) | std::views::reverse) {
                        if (auto const square = Grid::square(index); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

public:
        using   grid_type = Grid;
        using padded_type = padded_t<Grid, Padding>;

        [[nodiscard]] static constexpr auto flip() noexcept -> basic_embedding<flipped_t<Grid>, Padding> { return {}; }
        [[nodiscard]] static constexpr auto flop() noexcept -> basic_embedding<flopped_t<Grid>, Padding> { return {}; }
        [[nodiscard]] static constexpr auto swap() noexcept -> basic_embedding<swapped_t<Grid>, Padding> { return {}; }

        [[nodiscard]] static constexpr auto pad(auto coordinates) noexcept
        {
                return coordinates.template pad<Padding>();
        }

        static constexpr auto valid_range = []() {
                constexpr auto first = first_valid_index();
                constexpr auto last = last_valid_index();
                return first && last ? *last - *first + 1 : 0;
        }();
};

}   // namespace tabula
