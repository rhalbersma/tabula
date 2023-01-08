#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>   // padding

namespace tabula {

template<class T> using flipped_t = typename T::flipped_type;
template<class T> using flopped_t = typename T::flopped_type;
template<class T> using swapped_t = typename T::swapped_type;
template<class T> using  padded_t = typename T:: padded_type;

template<class, padding>
struct add_padding;

template<class T, padding P>
using add_padding_t = typename add_padding<T, P>::type;

}       // namespace tabula
