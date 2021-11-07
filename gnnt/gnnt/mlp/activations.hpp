#ifndef GENETIC_NN_TRAINER_ACTIVATIONS_HPP
#define GENETIC_NN_TRAINER_ACTIVATIONS_HPP

#include <concepts>
#include <algorithm>
#include <gnnt/utility/meta.hpp>

namespace gnnt::mlp
{
    template<arithmetic_constant A>
    struct prelu
    {
        static constexpr auto param = A.value;

        template<std::floating_point T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) {
                return x > 0 ? x : param * x;
            });
        }
    };

    using relu = prelu<0>;
    using leaky_relu = prelu<0.01>;

    struct sigmoid
    {
        template<std::floating_point T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) {
                return 1.0 / (1.0 + std::exp(-x));
            });
        }
    };

    struct softmax
    {
        template<std::floating_point T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) { return std::exp(x); });
            auto const sum = std::accumulate(values.cbegin(), values.cend(), 0.0);
            std::transform(values.cbegin(), values.cend(), values.begin(), [=](auto x) { return x / sum; });
        }
    };
}
#endif //GENETIC_NN_TRAINER_ACTIVATIONS_HPP
