#ifndef GENETIC_NN_TRAINER_META_HPP
#define GENETIC_NN_TRAINER_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;

    template<typename, typename... Rest>
    struct last
    {
        using type = typename last<Rest ...>::type;
    };

    template<typename Elem>
    struct last<Elem>
    {
        using type = Elem;
    };

    template<typename... Elems>
    using last_t = typename last<Elems ...>::type;
}
#endif //GENETIC_NN_TRAINER_META_HPP
