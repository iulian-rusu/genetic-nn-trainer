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
            dense<5, prelu<0.01>>,
            dense<10, prelu<0.01>>,
            dense<10, softmax>
        >;

inline constexpr static auto config = gnnt::trainer_config{
        .max_generations = 5000,
        .population_size = 100,
        .mutation_prob = 0.002,
        .crossover_alpha = 0.4,
        .precision = 0.02,
        .search_space = {-1.0, 1.0}
};

#endif //GENETIC_NN_TRAINER_CONFIG_HPP
