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

template<int Width, int Height, int Parity = 0, class Lake = basic_lake<>>
        requires (0 < Width &&  0 < Height && (Parity == 0 || Parity == 1))
class chequered_rectangle
{
        [[nodiscard]] static constexpr auto is_within(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return
                        0 <= file && file < Width &&
                        0 <= rank && rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_colored(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return !((file ^ rank ^ Parity) % 2);
        }

        [[nodiscard]] static constexpr auto is_lake(auto square) noexcept
                requires transformable<decltype(square)> && std::regular_invocable<Lake, decltype(square)>
        {
                return Lake()(square);
        }

public:
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto parity = Parity;
        static constexpr auto size   = (Width * Height + !Parity) / 2;

        using lake_type = Lake;

        using flipped_type = chequered_rectangle<Width, Height, Parity ^ !(Height % 2), compose_<Lake, flip_>>;
        using flopped_type = chequered_rectangle<Width, Height, Parity ^ !(Width  % 2), compose_<Lake, flop_>>;
        using swapped_type = chequered_rectangle<Height, Width, Parity,                 compose_<Lake, swap_>>;

        template<class Padding>
        using add_padding = chequered_rectangle<
                Width  + Padding::left + Padding::right + !((Width + Padding::left + Padding::right) % 2),
                Height + Padding::top  + Padding::bottom,
                Parity ^ (Padding::left % 2) ^ (Padding::bottom % 2),
                Lake
        >;

        [[nodiscard]] static constexpr auto is_valid(auto square) noexcept
                requires transformable<decltype(square)> && std::regular_invocable<Lake, decltype(square)>
        {
                return is_within(square) && is_colored(square) && !is_lake(square);
        }

        [[nodiscard]] static constexpr auto index(auto coordinates) noexcept
        {
                auto const [ file, rank ] = coordinates;
                return (file + rank * Width) / 2;
        };

        [[nodiscard]] static constexpr auto coordinates(int index) noexcept
                -> std::pair<int, int>
        {
                index *= 2;
                index += (Width % 2) ? Parity : Parity ^ ((index / Width) % 2);
                return { index % Width, index / Width };
        }
};

}       // namespace tabula
