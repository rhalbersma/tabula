#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class... Cuts>
struct basic_lakes;

template<>
struct basic_lakes<>
{
        [[nodiscard]] constexpr auto operator()(auto) const noexcept
        {
                return false;
        }
};

template<auto F, auto R>
struct cut;

template<char... Fs, int... Rs>
struct basic_lakes<cut<Fs, Rs>...>
{
        template<class Square>
        constexpr auto operator()(Square const& sq) const noexcept
        {
                return (... || (sq == Square(Fs - 'a', Rs - 1)));
        }
};

// https://developercommunity.visualstudio.com/content/problem/865810/vs-2019-164-ambiguous-partial-specialization-of-au.html
// template<int... Fs, int... Rs>
// struct basic_lakes<cut<Fs, Rs>...>
// {
//         template<class Square>
//         constexpr auto operator()(Square const& sq) const noexcept
//         {
//                 return ((sq == Square{Fs - 1, Rs - 1}) || ...);
//         }
// };

}       // namespace tabula
