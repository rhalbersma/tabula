#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/functional.hpp>        // compose_, flip_, flop_, swap_
#include <tabula/lakes.hpp>             // basic_lakes
#include <tabula/square.hpp>            // basic_square
#include <tabula/vector.hpp>            // basic_vector

namespace tabula {

template<int Width, int Height, int Parity = 0, class Lakes = basic_lakes<>>
requires (0 < Width &&  0 < Height && (Parity == 0 || Parity == 1))
struct chequered_rectangle
{
        static constexpr auto width  = Width;
        static constexpr auto height = Height;
        static constexpr auto parity = Parity;
        static constexpr auto size   = (Width * Height + !Parity) / 2;

        using lake_type = Lakes;

        using flipped_type = chequered_rectangle<Width, Height, Parity ^ !(Height % 2), compose_<Lakes, flip_>>;
        using flopped_type = chequered_rectangle<Width, Height, Parity ^ !(Width  % 2), compose_<Lakes, flop_>>;
        using swapped_type = chequered_rectangle<Height, Width, Parity,                 compose_<Lakes, swap_>>;

        template<class Padding>
        using padded_type = chequered_rectangle<
                Width  + Padding::left + Padding::right + !((Width + Padding::left + Padding::right) % 2),
                Height + Padding::top  + Padding::bottom,
                Parity ^ (Padding::left % 2) ^ (Padding::bottom % 2),
                Lakes
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
                requires std::regular_invocable<Lakes, square_type>
        {
                return Lakes()(s);
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

        [[nodiscard]] static constexpr auto square(int const n) noexcept
                -> square_type
        {
                auto const d = 2 * n;
                auto const i = d + ((Width % 2) ? Parity : Parity ^ ((d / Width) % 2));
                return { i % Width, i / Width };
        }

        [[nodiscard]] static constexpr auto index(square_type const& s) noexcept
        {
                return (s.file + s.rank * Width) / 2;
        }

        [[nodiscard]] static constexpr auto stride(vector_type const& v) noexcept
        {
                return (v.file + v.rank * Width) / 2;
        }
};

}       // namespace tabula
