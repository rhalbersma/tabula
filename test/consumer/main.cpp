//          Copyright Rein Halbersma 2019-2026.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tabula/games.hpp>

int main()
{
        using namespace tabula;
        constexpr auto b = chess::board{};
        static_assert(b.width == 8);
        static_assert(b.height == 8);
        static_assert(b.size == 64);
        return b.width == 8 && b.height == 8 ? 0 : 1;
}
