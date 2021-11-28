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

inline constexpr static auto config = gnnt::trainer_config{
        .max_generations = 5000,
        .population_size = 100,
        .mutation_prob = 0.0015,
        .crossover_alpha = 1.0 / 3,
        .precision = 0.1,
        .search_space = {-2.5, 2.5}
};

#endif //GENETIC_NN_TRAINER_CONFIG_HPP
