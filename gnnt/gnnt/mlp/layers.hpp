#ifndef GENETIC_NN_TRAINER_LAYER_BASE_HPP
#define GENETIC_NN_TRAINER_LAYER_BASE_HPP

#include <gnnt/mlp/activations.hpp>

namespace gnnt::mlp
{
    template< std::floating_point T, std::size_t N>
    struct layer_base
    {
        using value_type = T;
        static constexpr std::size_t size = N;
    };

    template<typename Layer>
    using value_type = typename Layer::value_type;

    template<std::floating_point T, std::size_t N>
    using input = layer_base<T, N>;

    template<std::floating_point T, std::size_t N, activation_t<T, N> Act>
    struct layer : layer_base<T, N>
    {
        static constexpr auto activation = Act;
    };
}
#endif //GENETIC_NN_TRAINER_LAYER_BASE_HPP
