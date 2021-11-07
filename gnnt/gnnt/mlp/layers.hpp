#ifndef GENETIC_NN_TRAINER_LAYER_BASE_HPP
#define GENETIC_NN_TRAINER_LAYER_BASE_HPP

#include <gnnt/mlp/activations.hpp>

namespace gnnt::mlp
{
    template<std::size_t N>
    struct layer
    {
        static constexpr std::size_t size = N;
    };

    template<std::size_t N>
    using input = layer<N>;

    template<std::size_t N, typename Activation>
    struct dense : layer<N>
    {
        using activation = Activation;
    };

    template<typename Layer>
    using activation = typename Layer::activation;

    namespace detail
    {
        template<std::size_t I, typename Layers, typename Default>
        struct layer_as_array
        {
            using type = std::decay_t<decltype(std::get<I - 1>(std::declval<Layers>()))>;
        };

        template<typename Layers, typename Default>
        struct layer_as_array<0, Layers, Default>
        {
            using type = Default;
        };
    }
}
#endif //GENETIC_NN_TRAINER_LAYER_BASE_HPP
