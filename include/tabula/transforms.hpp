#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/hana/functional/compose.hpp>    // compose
#include <boost/hana/functional/id.hpp>         // id
#include <boost/hana/reverse.hpp>               // reverse
#include <boost/hana/tuple.hpp>                 // make_tuple

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

inline constexpr auto transforms = boost::hana::reverse(boost::hana::make_tuple(
        boost::hana::id,                                // origin at lower-left, left-to-right, bottom-to-top
        swap_fn,                                        // origin at lower-left, bottom-to-top, left-to-right
        flip_fn,                                        // origin at upper-left, left-to-right, top-to-bottom
        boost::hana::compose(swap_fn, flip_fn),         // origin at upper-left, top-to-bottom, left-to-right
        flop_fn,                                        // origin at lower-right, right-to-left, bottom-to-top
        boost::hana::compose(swap_fn, flop_fn),         // origin at lower-right, bottom-to-top, right-to-left
        boost::hana::compose(flop_fn, flip_fn),         // origin at upper-right, right-to-left, top-to-bottom
        boost::hana::compose(swap_fn, flop_fn, flip_fn) // origin at upper-right, top-to-bottom, right-to-left
));

}       // namespace tabula

