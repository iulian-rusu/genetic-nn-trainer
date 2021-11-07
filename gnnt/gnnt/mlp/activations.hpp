#ifndef GENETIC_NN_TRAINER_ACTIVATIONS_HPP
#define GENETIC_NN_TRAINER_ACTIVATIONS_HPP

#include <concepts>
#include <algorithm>
#include <numeric>

namespace gnnt::mlp
{
    struct relu
    {
        template<std::floating_point T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) { return x > 0 ? x : 0; });
        }
    };

    struct softmax
    {
        template<std::floating_point T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) { return std::exp(x); });
            auto const sum = std::accumulate(values.cbegin(), values.cend(), T{0});
            std::transform(values.cbegin(), values.cend(), values.begin(), [=](auto x) { return x / sum; });
        }
    };

}
#endif //GENETIC_NN_TRAINER_ACTIVATIONS_HPP
