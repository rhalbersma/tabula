#pragma once

//          Copyright Rein Halbersma 2019-2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

// CSS padding Property: https://www.w3schools.com/cssref/pr_padding.asp

struct padding
{
        int top         = 0;
        int right       = 0;
        int bottom      = 0;
        int left        = 0;

        padding() = default;

        [[nodiscard]] constexpr padding(int trbl) noexcept
        :
                top(trbl),
                right(trbl),
                bottom(trbl),
                left(trbl)
        {}

        [[nodiscard]] constexpr padding(int tb, int rl) noexcept
        :
                top(tb),
                right(rl),
                bottom(tb),
                left(rl)
        {}

        [[nodiscard]] constexpr padding(int t, int rl, int b) noexcept
        :
                top(t),
                right(rl),
                bottom(b),
                left(rl)
        {}

        [[nodiscard]] constexpr padding(int t, int r, int b, int l) noexcept
        :
                top(t),
                right(r),
                bottom(b),
                left(l)
        {}
};

[[nodiscard]] inline constexpr auto right_padding(int r) noexcept
{
        return padding(0, r, 0, 0);
}

inline constexpr auto mailbox_padding = padding(2, 1);

}       // namespace tabula
