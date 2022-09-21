#ifndef OPTIMUM_H
#define OPTIMUM_H

#include <cstddef>	
#include <vector>
#include <optional>

namespace FuctionPointerLamda
{
    template <typename T, typename Comparison>
    inline std::optional<const T*> findOptimum(const std::vector<T>& values, Comparison compare)
    {
        if (values.empty()) return std::nullopt;

        const T* optimum{ &values[0] };
        for (size_t i{ 1 }; i < values.size(); ++i)
        {
            if (compare(values[i], *optimum))
                optimum = &values[i];
        }
        return optimum;
    }
}

#endif // !OPTIMUM_H
