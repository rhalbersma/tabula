#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/concepts.hpp>          // transformable
#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // basic_lake
#include <concepts>                     // regular_invocable
#include <utility>                      // pair

namespace tabula {

template<int Width, int Height, class Lake = basic_lake<>>
        requires (0 < Width && 0 < Height)
class basic_rectangle
{
        [[nodiscard]] static constexpr auto is_within(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return
                        0 <= file && file < Width &&
                        0 <= rank && rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_lake(auto square) noexcept
                requires transformable<decltype(square)> && std::regular_invocable<Lake, decltype(square)>
        {
                return Lake()(square);
        }

public:
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto size   = Width * Height;

        using lake_type = Lake;

        using flipped_type = basic_rectangle<Width, Height, compose_<Lake, flip_>>;
        using flopped_type = basic_rectangle<Width, Height, compose_<Lake, flop_>>;
        using swapped_type = basic_rectangle<Height, Width, compose_<Lake, swap_>>;

        template<class Padding>
        using add_padding = basic_rectangle<
                Width  + Padding::left + Padding::right,
                Height + Padding::top  + Padding::bottom,
                Lake
        >;

        [[nodiscard]] static constexpr auto is_valid(auto square) noexcept
                requires transformable<decltype(square)> && std::regular_invocable<Lake, decltype(square)>
        {
                return is_within(square) && !is_lake(square);
        }

        [[nodiscard]] static constexpr auto index(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return file + rank * Width;
        }

        [[nodiscard]] static constexpr auto coordinates(int index) noexcept
                -> std::pair<int, int>
        {
                return { index % Width, index / Width };
        }
};

}       // namespace tabula
