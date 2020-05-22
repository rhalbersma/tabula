#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tuple>        // apply, tuple, tuple_cat, tuple_size_v
#include <type_traits>  // bool_constant, conditional_t, integral_constant

namespace tabula {

template<bool B>
constexpr auto bool_c = std::bool_constant<B>();

template<int N>
constexpr auto int_c = std::integral_constant<int, N>();

template<class T, T... Ns>
constexpr auto tuple_c = std::tuple(std::integral_constant<T, Ns>()...);

constexpr auto for_each(auto tup, auto fun) noexcept
{
        return std::apply([=](auto... args) {
                return (fun(args), ...);
        }, tup);
}

constexpr auto enumerate(auto tup, auto fun) noexcept
{
        return std::apply([=, i = 0](auto... args) mutable {
                return (fun(i++, args), ...);
        }, tup);
}

constexpr auto transform(auto tup, auto fun) noexcept
{
        return std::apply([=](auto... args) {
                return std::tuple(fun(args)...);
        }, tup);
}

constexpr auto accumulate(auto tup) noexcept
{
        return std::apply([](auto... args) {
                return (... + args);
        }, tup);
}

constexpr auto any_of(auto tup, auto pred) noexcept
{
        return std::apply([=](auto... args) {
                return (... || pred(args));
        }, tup);
}

constexpr auto any_of_all(auto tup, auto pred) noexcept
{
        return std::apply([=](auto... args) {
                return (... | pred(args));
        }, tup);
}

constexpr auto remove_if(auto tup, auto pred) noexcept
{
        return std::apply([=](auto... args) {
                return std::tuple_cat(
                        std::conditional_t<
                                pred(args),
                                std::tuple<>,
                                std::tuple<decltype(args)>
                        >()...
                );
        }, tup);
}

constexpr auto min_index(auto tup) noexcept
{
        if constexpr (std::tuple_size_v<decltype(tup)> == 0) {
                return 0;
        } else {
                return std::apply([](auto head, auto... tail) {
                        auto min = head;
                        auto index = 0;
                        auto i = 1;
                        ([&](auto arg) {
                                if (arg < min) {
                                        min = arg;
                                        index = i;
                                }
                                ++i;
                        }(tail), ...);
                        return index;
                }, tup);
        }
}

}       // namespace tabula
