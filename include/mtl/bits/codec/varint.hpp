#pragma once

#include <type_traits>

namespace mtl {

struct varint
{
    template<
      typename U,
      std::enable_if_t<std::is_unsigned<U>::value, bool> = true>
    static constexpr std::size_t bytesize(U value)
    {
        std::size_t size = 1;
        for (; value > 127; value >>= 7) {
            size++;
        }
        return size;
    }

    template<
      typename U,
      typename OutputIt,
      std::enable_if_t<std::is_unsigned<U>::value, bool> = true>
    static constexpr std::size_t encode(U value, OutputIt it)
    {
        std::size_t size = 0;
        while (value > 127) {
            *it = (value & 127) | 128;
            value >>= 7;
            it++;
            size++;
        }

        *it = value & 127;
        it++;
        size++;
        return size;
    }

    template<
      typename U,
      typename InputIt,
      std::enable_if_t<std::is_unsigned<U>::value, bool> = true>
    static constexpr U decode(InputIt it, std::size_t maxsize = bytesize(-1ULL))
    {
        U result = 0;
        for (std::size_t i = 0; i < maxsize; i++, it++) {
            result |= (*it & 127) << (7 * i);

            if (!(*it & 128)) {
                break;
            }
        }

        return result;
    }
};

} // namespace mtl
