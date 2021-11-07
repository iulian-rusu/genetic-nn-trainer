#ifndef GENETIC_NN_TRAINER_RANDOM_HPP
#define GENETIC_NN_TRAINER_RANDOM_HPP

#include <random>

namespace gnnt
{
    template<typename Gen = std::minstd_rand>
    class random_generator_factory
    {
        std::random_device device{};
        Gen gen{device()};
    public:
        template<typename Dist>
        auto create(Dist &&dist) noexcept
        {
            return [&, dist = std::forward<Dist>(dist)]() mutable noexcept {
                return dist(gen);
            };
        }
    };
}
#endif //GENETIC_NN_TRAINER_RANDOM_HPP
