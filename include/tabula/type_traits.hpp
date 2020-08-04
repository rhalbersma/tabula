#pragma once

//          Copyright Rein Halbersma 2019-2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>  // void_t

namespace tabula {

template<class Grid, class = void>
inline constexpr auto is_chequered = false;

template<class Grid>
inline constexpr auto is_chequered<Grid, std::void_t<decltype(
        Grid::coloring
)>> = true;

template<class T> using    lake_t = typename T::   lake_type;

template<class T> using    grid_t = typename T::   grid_type;
template<class T> using padding_t = typename T::padding_type;

template<class T> using  square_t = typename T:: square_type;
template<class T> using  vector_t = typename T:: vector_type;

template<class T> using flipped_t = typename T::flipped_type;
template<class T> using flopped_t = typename T::flopped_type;
template<class T> using swapped_t = typename T::swapped_type;

}       // namespace tabula
