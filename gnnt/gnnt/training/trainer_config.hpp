#ifndef GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP
#define GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP

namespace gnnt
{
    struct trainer_config
    {
        std::size_t max_generations = 50;
        std::size_t population_size = 100;
        std::size_t tournament_competition_size = 2;
        double crossover_prob = 0.9;
        double mutation_prob = 0.03;
        double crossover_alpha = 0.5;
        double precision = 1.0e-4;
        double gene_mean = 0.0;
        double gene_stddev = 0.3;
        bool elitism = true;
    };
}
#endif //GENETIC_NN_TRAINER_TRAINER_CONFIG_HPP
