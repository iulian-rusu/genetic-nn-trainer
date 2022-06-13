#ifndef GENETIC_NN_TRAINER_CONFIG_HPP
#define GENETIC_NN_TRAINER_CONFIG_HPP

#include <gnnt.hpp>

using namespace gnnt::mlp;

using value_type = float;
using neural_network =
        network
        <
            value_type,
            input<gnnt::image_dimension>,
            dense<16, relu>,
            dense<16, relu>,
            dense<10, softmax>
        >;

inline constexpr auto config = gnnt::trainer_config{
        .max_generations = 500,
        .population_size = 100,
        .mutation_prob = 0.0015,
        .crossover_alpha = 1.0 / 3,
        .error = 0.05,
        .search_space = {-2.5, 2.5}
};

inline constexpr std::size_t batch_size = 300;

#endif //GENETIC_NN_TRAINER_CONFIG_HPP
