#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lake.hpp>              // basic_lake
#include <tabula/square.hpp>            // basic_square
#include <tabula/vector.hpp>            // basic_vector
#include <concepts>                     // regular_invocable

namespace tabula {

template<int Width, int Height, int Parity = 0, class Lake = basic_lake<>>
        requires (0 < Width &&  0 < Height && (Parity == 0 || Parity == 1))
struct chequered_rectangle
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto parity = Parity;
        static constexpr auto size   = (Width * Height + !Parity) / 2;

        using lake_type = Lake;

        using flipped_type = chequered_rectangle<Width, Height, Parity ^ !(Height % 2), compose_<Lake, flip_>>;
        using flopped_type = chequered_rectangle<Width, Height, Parity ^ !(Width  % 2), compose_<Lake, flop_>>;
        using swapped_type = chequered_rectangle<Height, Width, Parity,                 compose_<Lake, swap_>>;

        template<class Padding>
        using padded = chequered_rectangle<
                Width  + Padding::left + Padding::right + !((Width + Padding::left + Padding::right) % 2),
                Height + Padding::top  + Padding::bottom,
                Parity ^ (Padding::left % 2) ^ (Padding::bottom % 2),
                Lake
        >;

        using square_type = basic_square<chequered_rectangle>;
        using vector_type = basic_vector<chequered_rectangle>;

        [[nodiscard]] static constexpr auto is_within(square_type const& s) noexcept
        {
                return
                        0 <= s.file && s.file < Width &&
                        0 <= s.rank && s.rank < Height
                ;
        }

        [[nodiscard]] static constexpr auto is_lake(square_type const& s) noexcept
                requires std::regular_invocable<Lake, square_type>
        {
                return Lake()(s);
        }

        [[nodiscard]] static constexpr auto is_colored(square_type const& s) noexcept
                -> bool
        {
                return (s.file ^ s.rank ^ !Parity) % 2;
        }

        [[nodiscard]] static constexpr auto is_valid(square_type const& s) noexcept
        {
                return is_within(s) && !is_lake(s) && is_colored(s);
        }

        [[nodiscard]] static constexpr auto square(int index) noexcept
                -> square_type
        {
                index *= 2;
                index += (Width % 2) ? Parity : Parity ^ ((index / Width) % 2);
                return { index % Width, index / Width };
        }

        [[nodiscard]] static constexpr auto index(auto arg) noexcept
        {
                return (arg.file + arg.rank * Width) / 2;
        };
};

}       // namespace tabula
