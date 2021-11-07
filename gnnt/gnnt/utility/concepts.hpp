#ifndef GENETIC_NN_TRAINER_CONCEPTS_HPP
#define GENETIC_NN_TRAINER_CONCEPTS_HPP

#include <gnnt/utility/meta.hpp>

namespace gnnt
{
    template<typename T>
    concept container = std::ranges::random_access_range<T>;

    template<typename T>
    concept bidimensional_container = container<T> && container<value_type<T>>;
}
#endif //GENETIC_NN_TRAINER_CONCEPTS_HPP
