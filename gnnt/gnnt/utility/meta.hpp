#ifndef GENETIC_NN_TRAINER_META_HPP
#define GENETIC_NN_TRAINER_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;
}
#endif //GENETIC_NN_TRAINER_META_HPP
