#pragma once

//          Copyright Rein Halbersma 2019-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <functional>   // identity

namespace tabula {
namespace detail {

template<class F>
struct composable
{
        F call;
};

template<class F, class G>
constexpr auto operator>>(composable<F> f, composable<G> g) noexcept
{
        return composable([=](auto arg) {
                return f.call(g.call(arg));
        });
}

}       // namespace detail

inline constexpr auto identity = std::identity();
inline constexpr auto compose = [](auto... fs) {
        return (detail::composable(fs) >> ... >> detail::composable(identity)).call;
};

namespace detail {

template<class... Fs>
inline constexpr auto composed = [](auto arg) { return compose(Fs()...)(arg); };

}       // namespace detail

template<class... Fs>
using compose_ = decltype(detail::composed<Fs...>);

inline constexpr auto flip = [](auto arg) { return arg.flip(); };
inline constexpr auto flop = [](auto arg) { return arg.flop(); };
inline constexpr auto swap = [](auto arg) { return arg.swap(); };

using flip_ = decltype(flip);
using flop_ = decltype(flop);
using swap_ = decltype(swap);

}       // namespace tabula
