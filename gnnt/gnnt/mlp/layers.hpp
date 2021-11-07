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

    template<std::floating_point T, std::size_t N, typename Activation>
    struct layer : layer_base<T, N>
    {
        using activation = Activation;
    };

    template<typename Layer>
    using activation = typename Layer::activation;

    namespace detail
    {
        template<std::size_t I, typename Layers, typename Input>
        struct layer_type
        {
            using type = std::decay_t<decltype(std::get<I - 1>(std::declval<Layers>()))>;
        };

        template<typename Layers, typename Input>
        struct layer_type<0, Layers, Input>
        {
            using type = std::array<value_type<Input>, Input::size>;
        };
    }
}
#endif //GENETIC_NN_TRAINER_LAYER_BASE_HPP
