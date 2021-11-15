#ifndef GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
#define GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP

#include <tuple>

namespace gnnt
{
    namespace detail
    {
        template<typename Tuple1, typename Tuple2, typename Tuple3, typename Func, std::size_t... Indices>
        constexpr void tuple_for_each(
                Tuple1 &&tuple1,
                Tuple2 &&tuple2,
                Tuple3 &&tuple3,
                Func &&func,
                std::index_sequence<Indices ...> &&
        )
        {
            (func(std::get<Indices>(tuple1), std::get<Indices>(tuple2), std::get<Indices>(tuple3)), ...);
        }

        template<typename Tuple, typename Func, std::size_t... Indices>
        constexpr void tuple_for_each(Tuple &&tuple, Func &&func, std::index_sequence<Indices ...> &&)
        {
            (func(std::get<Indices>(tuple)), ...);
        }
    }

    /**
     * Applies a callable object on sets of three respective elements of a tuple-like collection.
     */
    template<typename Tuple1, typename Tuple2, typename Tuple3, typename Func>
    constexpr void tuple_for_each(Tuple1 &&tuple1, Tuple2 &&tuple2, Tuple3 &&tuple3, Func &&func)
    {
        detail::tuple_for_each(
                std::forward<Tuple1>(tuple1),
                std::forward<Tuple2>(tuple2),
                std::forward<Tuple3>(tuple3),
                std::forward<Func>(func),
                std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple1>>>{}
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
