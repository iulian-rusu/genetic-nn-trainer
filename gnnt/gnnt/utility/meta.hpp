#ifndef GENETIC_NN_TRAINER_META_HPP
#define GENETIC_NN_TRAINER_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    namespace detail
    {
        template<typename T>
        struct array_size_helper;

        template<std::size_t N, typename T>
        struct array_size_helper<std::array<T, N>>
        {
            static constexpr auto value = N;
        };
    }

    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;

    template<typename T>
    inline constexpr std::size_t array_size = detail::array_size_helper<std::decay_t<T>>::value;

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
