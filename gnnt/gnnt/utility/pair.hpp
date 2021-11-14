#ifndef GENETIC_NN_TRAINER_PAIR_HPP
#define GENETIC_NN_TRAINER_PAIR_HPP

namespace gnnt
{
    template<typename A, typename B>
    struct pair
    {
        A first{};
        B second{};
    };
}
#endif //GENETIC_NN_TRAINER_PAIR_HPP
