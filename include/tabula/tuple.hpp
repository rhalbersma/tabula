#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <functional>   // less
#include <tuple>        // apply, tuple, tuple_cat, tuple_size_v
#include <type_traits>  // bool_constant, conditional_t, integral_constant

namespace tabula {

template<bool B>
inline constexpr auto bool_c = std::bool_constant<B>();

template<int N>
inline constexpr auto int_c = std::integral_constant<int, N>();

template<class T, T... Ns>
inline constexpr auto tuple_c = std::tuple(std::integral_constant<T, Ns>()...);

constexpr auto for_each(auto tup, auto fun) noexcept
{
        return std::apply([&](auto... args) {
                return (fun(args), ...);
        }, tup);
}

[[nodiscard]] constexpr auto transform(auto tup, auto fun) noexcept
{
        return std::apply([=](auto... args) {
                return std::tuple(fun(args)...);
        }, tup);
}

[[nodiscard]] constexpr auto accumulate(auto tup) noexcept
{
        return std::apply([](auto... args) {
                return (... + args);
        }, tup);
}

[[nodiscard]] constexpr auto all_of(auto tup, auto pred) noexcept
        -> bool
{
        return std::apply([=](auto... args) {
                return (... && pred(args));
        }, tup);
}

[[nodiscard]] constexpr auto any_of(auto tup, auto pred) noexcept
        -> bool
{
        return std::apply([=](auto... args) {
                return (... || pred(args));
        }, tup);
}

[[nodiscard]] constexpr auto any_of_all(auto tup, auto pred) noexcept
        -> bool
{
        return std::apply([=](auto... args) {
                return (... | pred(args));
        }, tup);
}

[[nodiscard]] constexpr auto remove_if(auto tup, auto pred) noexcept
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

template<class Compare = std::less<>>
[[nodiscard]] constexpr auto min_element(auto tup, Compare cmp = Compare()) noexcept
        -> int
{
        return std::apply([=](auto head, auto... tail) {
                auto min = head;
                auto element = 0;
                for_each(std::tuple(tail...), [&, cmp, index = 1] (auto arg) mutable {
                        if (cmp(arg, min)) {
                                min = arg;
                                element = index;
                        }
                        ++index;
                });
                return element;
        }, tup);
}

}       // namespace tabula
