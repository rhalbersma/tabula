#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class... Cuts>
struct basic_lakes;

template<char F, int R>
struct cut;

template<char... Fs, int... Rs>
struct basic_lakes<cut<Fs, Rs>...>
{
        template<class Square>
        constexpr auto operator()(Square const& sq) const noexcept
        {
                return ((sq == Square{Fs - 'a', Rs - 1}) || ...);
        }
};

}       // namespace tabula
