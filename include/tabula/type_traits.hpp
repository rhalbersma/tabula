#pragma once

//          Copyright Rein Halbersma 2019-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/padding.hpp>   // padding

namespace tabula {

template<class> struct flipped;
template<class> struct flopped;
template<class> struct swapped;

template<class, padding> 
struct padded;

template<class T> using flipped_t = typename flipped<T>::type;
template<class T> using flopped_t = typename flopped<T>::type;
template<class T> using swapped_t = typename swapped<T>::type;

template<class T, padding P> 
using padded_t = typename padded<T, P>::type;

}       // namespace tabula
