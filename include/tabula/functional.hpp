#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

template<class UnaryFunction>
struct flip_
{
        constexpr static auto size = UnaryFunction::size;

        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.flip());
        }
};

template<class UnaryFunction>
struct flop_
{
        constexpr static auto size = UnaryFunction::size;

        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.flop());
        }
};

template<class UnaryFunction>
struct swap_
{
        constexpr static auto size = UnaryFunction::size;

        template<class Arg>
        constexpr auto operator()(Arg const& arg) const noexcept
        {
                return UnaryFunction{}(arg.swap());
        }
};

inline constexpr auto flip_fn = [](auto const& arg) { return arg.flip(); };
inline constexpr auto flop_fn = [](auto const& arg) { return arg.flop(); };
inline constexpr auto swap_fn = [](auto const& arg) { return arg.swap(); };

}       // namespace tabula

