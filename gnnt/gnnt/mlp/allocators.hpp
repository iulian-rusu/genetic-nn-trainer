#ifndef GENETIC_NN_TRAINER_ALLOCATORS_HPP
#define GENETIC_NN_TRAINER_ALLOCATORS_HPP

#include <array>
#include <tuple>
#include <gnnt/mlp/layers.hpp>

namespace gnnt::mlp
{
    template<typename Layer>
    using bias_t =  std::array<value_type<Layer>, Layer::size>;

    template<typename First, typename... Rest>
    struct bias_allocator
    {
        template<typename... Biases>
        using type = typename bias_allocator<Rest ...>::template type<Biases ..., bias_t<First>>;
    };

    template<typename Last>
    struct bias_allocator<Last>
    {
        template<typename... Biases>
        using type = std::tuple<Biases ..., bias_t<Last>>;
    };

    template<typename Prev, typename Current>
    using weight_t =  std::array<std::array<value_type<Prev>, Prev::size>, Current::size>;

    template<typename Prev, typename Current, typename... Rest>
    struct weight_allocator
    {
        template<typename... Weights>
        using type = typename weight_allocator<Current, Rest ...>::template type<Weights ..., weight_t<Prev, Current>>;
    };

    template<typename Prev, typename Current>
    struct weight_allocator<Prev, Current>
    {
        template<typename... Weights>
        using type = std::tuple<Weights ..., weight_t<Prev, Current>>;
    };
}
#endif //GENETIC_NN_TRAINER_ALLOCATORS_HPP
