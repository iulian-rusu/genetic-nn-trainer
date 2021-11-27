#ifndef GENETIC_NN_TRAINER_ACTIVATIONS_HPP
#define GENETIC_NN_TRAINER_ACTIVATIONS_HPP

#include <algorithm>
#include <gnnt/utility/meta.hpp>
#include <iostream>

namespace gnnt::mlp
{
    template<arithmetic_constant A>
    struct prelu
    {
        static constexpr auto param = A.value;

        template<typename T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) {
                return x > 0 ? x : param * x;
            });
        }
    };

    using relu = prelu<0>;

    struct sigmoid
    {
        template<typename T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            std::transform(values.cbegin(), values.cend(), values.begin(), [](auto x) {
                return 1.0 / (1.0 + std::exp(-x));
            });
        }
    };

    struct softmax
    {
        template<typename T, std::size_t N>
        constexpr void operator()(std::array<T, N> &values) const noexcept
        {
            const auto maximum = *std::max_element(values.cbegin(), values.cend());
            auto const sum = std::accumulate(
                    values.cbegin(), values.cend(), 0.0,
                    [=](auto acc, auto x) {
                        return acc + std::exp(x - maximum);
                    }
            );
            auto const offset = maximum + std::log(sum);
            std::transform(
                    values.cbegin(), values.cend(), values.begin(),
                    [=](auto x) {
                        return std::exp(x - offset);
                    }
            );
        }
    };
}
#endif //GENETIC_NN_TRAINER_ACTIVATIONS_HPP
