#pragma once

//          Copyright Rein Halbersma 2019-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace tabula {

struct padding
{
        int top;
        int right;
        int bottom;
        int left;

        [[nodiscard]] constexpr auto operator==(padding const&) const noexcept -> bool = default;
};

[[nodiscard]] constexpr auto pad_right(int r) noexcept
        -> padding
{
        return { .top = 0, .right = r, .bottom = 0, .left = 0 };
}

[[nodiscard]] constexpr auto pad_boxed(int tb, int rl) noexcept
        -> padding
{
        return { .top = tb, .right = rl, .bottom = tb, .left = rl };
}

}       // namespace tabula
