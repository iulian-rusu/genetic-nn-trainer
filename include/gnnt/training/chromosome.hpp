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

        network_t network{};
        value_type loss = std::numeric_limits<value_type>::max();

        constexpr auto operator<=>(chromosome const &other) const noexcept
        {
            return loss <=> other.loss;
        }
    };
    template<typename Network>
    chromosome(Network &&) -> chromosome<std::remove_cvref_t<Network>>;
}
#endif //GENETIC_NN_TRAINER_CHROMOSOME_HPP
