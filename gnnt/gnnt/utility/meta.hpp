#ifndef GENETIC_NN_TRAINER_META_HPP
#define GENETIC_NN_TRAINER_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    template<typename...>
    struct head;

    template<typename Head, typename... Rest>
    struct head<Head, Rest ...>
    {
        using type = Head;
    };

    template<typename... Elems>
    using head_t = typename head<Elems ...>::type;

    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;

    template<typename T>
    requires std::is_arithmetic_v<T>
    struct arithmetic_constant
    {
        T value{};

        constexpr arithmetic_constant(T t) : value{t}
        {}
    };
}
#endif //GENETIC_NN_TRAINER_META_HPP
