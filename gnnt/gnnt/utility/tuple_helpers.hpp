#ifndef GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
#define GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP

#include <tuple>

namespace gnnt
{
    namespace detail
    {
        template<typename Tuple, typename Func, std::size_t... Indices>
        constexpr auto tuple_transform(Tuple const &tuple, Func &&func, std::index_sequence<Indices ...> &&)
        {
            return std::tuple{func(std::get<Indices>(tuple)) ...};
        }

        template<typename Tuple, typename Func, std::size_t... Indices>
        constexpr void tuple_for_each(Tuple &&tuple, Func &&func, std::index_sequence<Indices ...> &&)
        {
            (func(std::get<Indices>(tuple)), ...);
        }
    }

    /**
     * Creates a new tuple by applying a callable object on each element of
     * another tuple.
     *
     * @param tuple     The original tuple
     * @param func      The callable that generates elements for the new tuple
     * @return          A new std::tuple with elements returned by mapper
     */
    template<typename Tuple, typename Func>
    constexpr auto tuple_transform(Tuple const &tuple, Func &&func)
    {
        return detail::tuple_transform(
                tuple,
                std::forward<Func>(func),
                std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>{}
        );
    }

    /**
     * Applies a callable object on each element of a tuple-like container.
     *
     * @param tuple     The type tuple to map the function onto
     * @param func      The function used as a mapper
     */
    template<typename Tuple, typename Func>
    constexpr void tuple_for_each(Tuple &&tuple, Func &&func)
    {
        detail::tuple_for_each(
                std::forward<Tuple>(tuple),
                std::forward<Func>(func),
                std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>{}
        );
    }
}
#endif //GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
