#ifndef GENETIC_NN_TRAINER_META_HPP
#define GENETIC_NN_TRAINER_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    namespace detail
    {
        template<typename, typename... Rest>
        struct get_last
        {
            using type = typename get_last<Rest ...>::type;
        };

        template<typename Elem>
        struct get_last<Elem>
        {
            using type = Elem;
        };

        template<typename T>
        struct get_array_size;

        template<std::size_t N, typename T>
        struct get_array_size<std::array<T, N>>
        {
            static constexpr auto value = N;
        };
    }

    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;

    template<typename... Elems>
    using last_t = typename detail::get_last<Elems ...>::type;

    template<typename T>
    inline constexpr std::size_t array_size = detail::get_array_size<std::decay_t<T>>::value;
}
#endif //GENETIC_NN_TRAINER_META_HPP
