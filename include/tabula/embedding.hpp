#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/square.hpp>            // to_square
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
                        if (auto const square = to_square<Grid>(Grid::coordinates(index)); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

        [[nodiscard]] static constexpr auto last_valid_index() noexcept
                -> std::optional<int>
        {
                for (auto index = Grid::size - 1; index >= 0; --index) {
                        if (auto const square = to_square<Grid>(Grid::coordinates(index)); square.is_valid()) {
                                return pad(square).index();
                        }
                }
                return std::nullopt;
        }

public:
        using    grid_type = Grid;
        using padding_type = Padding;

        using flipped_type = basic_embedding<flipped_t<Grid>, Padding>;
        using flopped_type = basic_embedding<flopped_t<Grid>, Padding>;
        using swapped_type = basic_embedding<swapped_t<Grid>, Padding>;

        using padded_type = add_padding<Grid, Padding>;

        [[nodiscard]] static constexpr auto flip() noexcept -> flipped_type { return {}; }
        [[nodiscard]] static constexpr auto flop() noexcept -> flopped_type { return {}; }
        [[nodiscard]] static constexpr auto swap() noexcept -> swapped_type { return {}; }

        [[nodiscard]] static constexpr auto pad(auto coordinates) noexcept
        {
                return coordinates.template pad<Padding>();
        }

        static constexpr auto min_size = []() {
                constexpr auto first = first_valid_index();
                constexpr auto last = last_valid_index();
                if constexpr (first && last) {
                        return *last - *first + 1;
                } else {
                        return 0;
                }
        }();
};

}   // namespace tabula
