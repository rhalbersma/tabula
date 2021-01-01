#pragma once

//          Copyright Rein Halbersma 2019-2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>  // void_t

namespace tabula {

template<class T> using  square_t = typename T:: square_type;
template<class T> using  vector_t = typename T:: vector_type;

template<class T> using flipped_t = typename T::flipped_type;
template<class T> using flopped_t = typename T::flopped_type;
template<class T> using swapped_t = typename T::swapped_type;

template<class Grid, class = void>
inline constexpr auto is_chequered_v = false;

template<class Grid>
inline constexpr auto is_chequered_v<Grid, std::void_t<decltype(
        Grid::coloring
)>> = true;

}       // namespace tabula
