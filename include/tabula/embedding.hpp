#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>   // padding
#include <tabula/square.hpp>
#include <optional>             // nullopt, optional
#include <ranges>               // iota, reverse

namespace tabula {

template<auto Grid, class Lake, padding Padding>
class basic_embedding
{
        [[nodiscard]] static constexpr auto is_valid(auto square) noexcept
        {
                return Grid.is_valid(square) && !Lake()(square);
        }

        [[nodiscard]] static constexpr auto first_valid() noexcept
                -> std::optional<int>
        {
                for (auto index : std::views::iota(0, Grid.size())) {
                        auto const [ file, rank ] = Grid.coordinates(index);
                        if (auto const square = basic_square<Grid>(file, rank); is_valid(square) ) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

        [[nodiscard]] static constexpr auto last_valid() noexcept
                -> std::optional<int>
        {
                for (auto index : std::views::iota(0, Grid.size()) | std::views::reverse) {
                        auto const [ file, rank ] = Grid.coordinates(index);
                        if (auto const square = basic_square<Grid>(file, rank); is_valid(square)) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

public:
        static constexpr auto grid = Grid;
        using lake_type = Lake;

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
