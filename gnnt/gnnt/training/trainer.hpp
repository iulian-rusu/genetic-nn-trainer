#ifndef GENETIC_NN_TRAINER_TRAINER_HPP
#define GENETIC_NN_TRAINER_TRAINER_HPP

#include <unordered_set>
#include <gnnt/training/chromosome.hpp>
#include <gnnt/training/trainer_config.hpp>
#include <gnnt/utility/pair.hpp>

namespace gnnt
{
    template<typename Chromosome, trainer_config config>
    struct trainer
    {
        using value_type = typename Chromosome::value_type;
        using chromosome_t = Chromosome;
        using population_t = std::array<chromosome_t, config.population_size>;
        using parent_pair_t = std::pair<std::size_t, std::size_t>;
        using parents_t = std::array<parent_pair_t, config.population_size / 2>;

        static constexpr auto crossover_func = [](value_type x, value_type y) noexcept {
            return x * config.crossover_alpha + y * (1 - config.crossover_alpha);
        };

        chromosome_t const &find_best_chromosome() const noexcept
        {
            return *std::min_element(
                    population.cbegin(),
                    population.cend()
                    );
        }

        template<typename Func>
        void calculate_fitness(Func &&loss_func)
        {
            for (auto &chrom: population)
                chrom.fitness = loss(chrom.network);
        }

        template<typename RNG>
        std::size_t select_parent_by_tournament(RNG &&rng)
        {
            tournament_competition.clear();
            while (tournament_competition.size() < config.tournament_competition_size)
                tournament_competition.insert(rng());

            return *std::min_element(
                    tournament_competition.cbegin(),
                    tournament_competition.cend(),
                    [&](auto const a, auto const b) {
                        return population[a].fitness < population[b].fitness;
                    }
            );
        }

        template<typename RNG>
        void selection(RNG &&rng)
        {
            for (auto &pair: parents)
            {
                pair.first = select_parent_by_tournament(rng);
                pair.second = select_parent_by_tournament(rng);
            }
        }

        chromosome_t generate_child(chromosome_t const &first_parent, chromosome_t const &second_parent)
        {
            chromosome_t child;
            // TODO: implement a way to traverse a pair of std::tuples for crossover
            return child;
        }

        void crossover()
        {
            population_t children;
            std::size_t index = 0;

            for (auto const pair: parents)
            {
                auto const &first_parent = population[pair.first];
                auto const &second_parent = population[pair.second];
                children[index++] = std::move(generate_child(first_parent, second_parent));
                children[index++] = std::move(generate_child(second_parent, first_parent));
            }

            auto const remaining = population.size() - index;
            if (remaining > 0)
                std::partial_sort(population.begin(), population.begin() + remaining, population.end());

            std::copy(
                    std::make_move_iterator(children.begin()),
                    std::make_move_iterator(children.begin() + index),
                    population.begin() + remaining
            );
        }

        template<typename ProbRNG, typename GeneRNG>
        void mutation(ProbRNG &&prob_rng, GeneRNG &&gene_rng)
        {
            // TODO: iterave over std::tuples and mutate genes
        }

        template<typename Func>
        auto train(Func &&loss_func, value_type const target = 0.0) -> pair<chromosome_t, std::size_t>
        {
            auto index_rng = rng_factory.create(index_dist);
            auto prob_rng = rng_factory.create(prob_dist);
            auto gene_rng = rng_factory.create(gene_dist);
            std::size_t current_generation = 0;

            calculate_fitness(loss_func);
            while (current_generation++ < config.max_generations)
            {
                auto &best_chrom = find_best_chromosome();
                if (best_chrom.fitness - target < config.precision)
                    return {best_chrom, current_generation};

//                selection(index_rng);
//                crossover();
//                mutation(prob_rng, gene_rng);
//                calculate_fitness(func);
            }

            return {find_best_chromosome(), config.max_generations};
        }
    private:
        population_t population{};
        parents_t parents{};
        std::unordered_set<std::size_t> tournament_competition{config.tournament_competition_size};

        random_generator_factory<> rng_factory{};
        std::normal_distribution<value_type> gene_dist{config.gene_mean, config.gene_stddev};
        std::uniform_int_distribution<std::size_t> index_dist{0, config.population_size - 1};
        std::uniform_real_distribution<double> prob_dist{0.0, 1.0};
    };
}
#endif //GENETIC_NN_TRAINER_TRAINER_HPP
