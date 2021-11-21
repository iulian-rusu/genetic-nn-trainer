#ifndef GENETIC_NN_TRAINER_ALLOCATORS_HPP
#define GENETIC_NN_TRAINER_ALLOCATORS_HPP

#include <array>
#include <tuple>
#include <gnnt/mlp/layers.hpp>

namespace gnnt::mlp
{
    template<typename T, typename Layer>
    using layer_biases_t =  std::array<T, Layer::size>;

    template<typename T, typename First, typename... Rest>
    struct bias_allocator
    {
        template<typename... Biases>
        using type = typename bias_allocator<T, Rest ...>::template type<Biases ..., layer_biases_t<T, First>>;
    };

    template<typename T, typename Last>
    struct bias_allocator<T, Last>
    {
        template<typename... Biases>
        using type = std::tuple<Biases ..., layer_biases_t<T, Last>>;
    };

    template<typename T, typename Prev, typename Current>
    using layer_weights_t =  std::array<std::array<T, Prev::size>, Current::size>;

    template<typename T, typename Prev, typename Current, typename... Rest>
    struct weight_allocator
    {
        template<typename... Weights>
        using type = typename weight_allocator<T, Current, Rest ...>::template type<Weights ..., layer_weights_t<T, Prev, Current>>;
    };

    template<typename T, typename Prev, typename Current>
    struct weight_allocator<T, Prev, Current>
    {
        template<typename... Weights>
        using type = std::tuple<Weights ..., layer_weights_t<T, Prev, Current>>;
    };
}
#endif //GENETIC_NN_TRAINER_ALLOCATORS_HPP
