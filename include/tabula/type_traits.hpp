#pragma once

//          Copyright Rein Halbersma 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>  // void_t

namespace tabula {

template<class Shape, class = void>
inline constexpr auto is_chequered = false;

template<class Shape>
inline constexpr auto is_chequered<Shape, std::void_t<decltype(
        Shape::coloring
)>> = true;

template<class T> using     shape_t = typename T::    shape_type;
template<class T> using    square_t = typename T::   square_type;
template<class T> using direction_t = typename T::direction_type;

template<class T> using lake_t = typename T::lake_type;
template<class T> using flip_t = typename T::flip_type;
template<class T> using flop_t = typename T::flop_type;
template<class T> using swap_t = typename T::swap_type;

template<class Shape, class Padding> using padded_t = typename Shape::template padded_type<Padding>;

}       // namespace tabula
