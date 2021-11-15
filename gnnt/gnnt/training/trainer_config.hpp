#ifndef GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP
#define GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP

namespace gnnt
{
    struct trainer_config
    {
        uint32_t max_generations = 500;
        uint32_t population_size = 100;
        double crossover_prob = 0.9;
        double mutation_prob = 0.03;
        double crossover_alpha = 0.5;
        double precision = 1.0e-2;
        bool elitism = true;
        std::array<double, 2> search_space{-1.0, 1.0};
    };
}
#endif //GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP
