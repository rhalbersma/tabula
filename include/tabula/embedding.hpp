#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>   // padding
#include <optional>             // nullopt, optional
#include <ranges>               // iota, reverse

namespace tabula {

template<class Grid, padding Padding>
class basic_embedding
{
        [[nodiscard]] static constexpr auto first_valid() noexcept
                -> std::optional<int>
        {
                for (auto index : std::views::iota(0, Grid::size)) {
                        if (auto const square = Grid::square(index); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

        [[nodiscard]] static constexpr auto last_valid() noexcept
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
        using grid_type = Grid;

        [[nodiscard]] static constexpr auto pad(auto coordinates) noexcept
        {
                return coordinates.template pad<Padding>();
        }

        static constexpr auto valid_size = []() {
                constexpr auto first = first_valid();
                constexpr auto last = last_valid();
                return first && last ? *last - *first + 1 : 0;
        }();
};

}   // namespace tabula
