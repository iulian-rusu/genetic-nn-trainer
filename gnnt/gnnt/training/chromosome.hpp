#ifndef GENETIC_NN_TRAINER_CHROMOSOME_HPP
#define GENETIC_NN_TRAINER_CHROMOSOME_HPP

#include <limits>
#include <compare>

namespace gnnt
{
    template<typename Network>
    struct chromosome
    {
        using value_type = typename Network::value_type;
        using network_t = Network;

        value_type fitness = std::numeric_limits<value_type>::max();
        network_t network{};

        constexpr std::strong_ordering operator<=>(chromosome const &other) const noexcept
        {
            return fitness <=> other.fitness;
        }
    };
}
#endif //GENETIC_NN_TRAINER_CHROMOSOME_HPP
