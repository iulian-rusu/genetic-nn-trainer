#ifndef GENETIC_NN_TRAINER_ACTIVATIONS_HPP
#define GENETIC_NN_TRAINER_ACTIVATIONS_HPP

#include <concepts>
#include <algorithm>
#include <numeric>
#include <valarray>

namespace gnnt::mlp
{
    template<std::floating_point T, std::size_t N>
    using activation_t = void (*)(std::array<T, N> &);

    template<std::floating_point T, std::size_t N>
    constexpr void relu(std::array<T, N> &values) noexcept
    {
        std::for_each(values.begin(), values.end(), [](auto &x) {
            x = std::max(0, x);
        });
    }

    template<std::floating_point T, std::size_t N>
    constexpr void softmax(std::array<T, N> &values) noexcept
    {
        auto const sum = std::accumulate(values.cbegin(), values.cend(), T{}, [](T acc, T x) {
            return acc + std::exp(x);
        });
        std::for_each(values.begin(), values.end(), [sum](T &x) {
            x = std::exp(x) / sum;
        });
    }
}
#endif //GENETIC_NN_TRAINER_ACTIVATIONS_HPP
