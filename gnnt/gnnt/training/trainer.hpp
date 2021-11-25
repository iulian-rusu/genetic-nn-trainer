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
        using population_t = std::vector<chromosome_t>;
        using parents_t = std::vector<pair<uint32_t, uint32_t>>;

        static constexpr auto crossover_func = [](auto const &xs, auto const &ys, auto &out) noexcept {
            std::transform(xs.cbegin(), xs.cend(), ys.cbegin(), out.begin(),
                    [](auto x, auto y) noexcept {
                        return y * config.crossover_alpha + x * (1 - config.crossover_alpha);
                    }
            );
        };

        trainer() : population(config.population_size), parents(config.population_size / 2)
        {}

        /**
         * Trains a population of chromosomes to minimize a given loss function.
         *
         * @param loss_evaluator    A callable object that will update the population's loss after each generation
         * @param callback          A callback function called after each generation
         * @param target_loss       The optimal loss value, defaults to 0.0
         * @return                  The best chromosome and the number of generations trained
         */
        template<typename Func>
        auto train(Func &&loss_evaluator, auto callback, value_type const target_loss = 0.0)
        -> pair<chromosome_t, uint32_t>
        {
            auto gene_rng = rng_factory.create(gene_dist);
            auto index_rng = rng_factory.create(index_dist);
            auto prob_rng = rng_factory.create(prob_dist);
            uint32_t current_generation = 0;

            generate_population(gene_rng);
            loss_evaluator(population);
            while (current_generation++ < config.max_generations)
            {
                auto best_chrom = find_best_chromosome();
                if (std::abs(best_chrom.loss - target_loss) < config.precision)
                    return {best_chrom, current_generation};

                selection(index_rng);
                crossover(prob_rng);
                mutation(prob_rng, gene_rng);
                loss_evaluator(population);

                if constexpr (config.elitism)
                {
                    auto ptr = std::max_element(population.begin(), population.end());
                    *ptr = best_chrom;
                }

                callback(current_generation, best_chrom.loss);
            }

            return {find_best_chromosome(), config.max_generations};
        }

        template<typename Func>
        auto train(Func &&loss_evaluator, value_type const target_loss = 0.0)
        {
            return train(std::forward<Func>(loss_evaluator), [](auto...){}, target_loss);
        }

    private:
        template<typename Rng>
        void generate_population(Rng &&rng) noexcept
        {
            for (auto &chrom: population)
                chrom.network.generate_params(rng);
        }

        chromosome_t const &find_best_chromosome() const noexcept
        {
            return *std::min_element(
                    population.cbegin(),
                    population.cend()
            );
        }

        template<typename RNG>
        uint32_t select_parent_by_tournament(RNG &&rng) noexcept
        {
            uint32_t first = rng();
            uint32_t second = rng();
            if (second >= first)
                second = (second + 1) % config.population_size;

            return population[first].loss < population[second].loss ? first : second;
        }

        template<typename RNG>
        void selection(RNG &&rng) noexcept
        {
            for (auto &pair: parents)
            {
                pair.first = select_parent_by_tournament(rng);
                pair.second = select_parent_by_tournament(rng);
            }
        }

        chromosome_t generate_child(chromosome_t const &first_parent, chromosome_t const &second_parent) const noexcept
        {
            chromosome_t child{};
            for_each_tuple(
                    [](auto const &first_parent_ws, auto const &second_parent_ws, auto &child_ws) {
                        for (uint32_t i = 0; i < first_parent_ws.size(); ++i)
                            crossover_func(first_parent_ws[i], second_parent_ws[i], child_ws[i]);
                    },
                    first_parent.network.weights,
                    second_parent.network.weights,
                    child.network.weights
            );
            for_each_tuple(
                    [](auto const &first_parent_bs, auto const &second_parent_bs, auto &child_bs) {
                        crossover_func(first_parent_bs, second_parent_bs, child_bs);
                    },
                    first_parent.network.biases,
                    second_parent.network.biases,
                    child.network.biases
            );
            return child;
        }

        template<typename RNG>
        void crossover(RNG &&rng) noexcept
        {
            population_t children(config.population_size);
            uint32_t index = 0;

            for (auto const pair: parents)
            {
                auto const &first_parent = population[pair.first];
                auto const &second_parent = population[pair.second];
                if (rng() < config.crossover_prob)
                {
                    // Probably not the most efficient, can't move std::array...
                    children[index++] = std::move(generate_child(first_parent, second_parent));
                    children[index++] = std::move(generate_child(second_parent, first_parent));
                }
                else
                {
                    children[index++] = first_parent;
                    children[index++] = second_parent;
                }
            }

            population = std::move(children);
        }

        template<typename ProbRNG, typename GeneRNG>
        void mutation(ProbRNG &&prob_rng, GeneRNG &&gene_rng) noexcept
        {
            for (auto &chrom: population)
            {
                for_each_tuple(
                        [&](auto &layer_ws) {
                            for (auto &neuron_ws: layer_ws)
                                for (auto &w: neuron_ws)
                                    if (prob_rng() < config.mutation_prob)
                                        w = gene_rng();
                        },
                        chrom.network.weights
                );
                for_each_tuple(
                        [&](auto &layer_bs) {
                            for (auto &b: layer_bs)
                                if (prob_rng() < config.mutation_prob)
                                    b = gene_rng();
                        },
                        chrom.network.biases
                );
            }
        }

        population_t population{};
        parents_t parents{};

        random_generator_factory<> rng_factory{};
        std::uniform_real_distribution<value_type> gene_dist{config.search_space[0], config.search_space[1]};
        std::uniform_int_distribution<uint32_t> index_dist{0, config.population_size - 1};
        std::uniform_real_distribution<double> prob_dist{0.0, 1.0};
    };
}
#endif //GENETIC_NN_TRAINER_TRAINER_HPP
