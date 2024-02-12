#pragma once

#include <climits>
#include <type_traits>

namespace mtl {

struct zigzag
{
    template<
      typename S,
      std::enable_if_t<std::is_signed<S>::value, bool> = true>
    static constexpr auto encode(S x) -> std::make_unsigned_t<S>
    {
        using U             = std::make_unsigned_t<S>;
        constexpr auto mask = (sizeof(S) * CHAR_BIT) - 1;
        return (2 * static_cast<U>(x)) ^ -(static_cast<U>(x) >> mask);
    }

    template<
      typename U,
      std::enable_if_t<std::is_unsigned<U>::value, bool> = true>
    static constexpr auto decode(U x) -> std::make_signed_t<U>
    {
        return (x >> 1) ^ -(x & 1);
    }
};

} // namespace mtl
