#ifndef GENETIC_NN_TRAINER_NETWORK_HPP
#define GENETIC_NN_TRAINER_NETWORK_HPP

#include <gnnt/utility/meta.hpp>
#include <gnnt/mlp/allocators.hpp>

namespace gnnt::mlp
{
    template<typename Input, typename... Layers>
    struct network
    {
        using biases_t = typename bias_allocator<Layers ...>::template type<>;
        using weights_t = typename weight_allocator<Input, Layers ...>::template type<>;

        static constexpr std::size_t inpus_size = Input::size;
        static constexpr std::size_t output_size = last_t<Layers ...>::size;

        biases_t biases{};
        weights_t weights{};
    };
}
#endif //GENETIC_NN_TRAINER_NETWORK_HPP
