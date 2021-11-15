#ifndef GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
#define GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP

#include <tuple>

namespace gnnt
{
    namespace detail
    {
        template<typename Tuple, typename Func, std::size_t... Indices>
        constexpr void tuple_for_each(
                Tuple const &tuple_in1,
                Tuple const &tuple_in2,
                Tuple &tuple_out,
                Func &&func,
                std::index_sequence<Indices ...> &&
        )
        {
            (func(std::get<Indices>(tuple_in1), std::get<Indices>(tuple_in2), std::get<Indices>(tuple_out)), ...);
        }

        template<typename Tuple, typename Func, std::size_t... Indices>
        constexpr void tuple_for_each(Tuple &&tuple, Func &&func, std::index_sequence<Indices ...> &&)
        {
            (func(std::get<Indices>(tuple)), ...);
        }
    }

    /**
     * Applies a callable object on sets of three respective elements of a tuple-like collection.
     * The first two tuples are considered inputs, the last tuple is a mutable out-parameter.
     *
     * @param tuple_in1     The first input tuple
     * @param tuple_in2     The second input tuple
     * @param tuple_out     The output tuple passed as mutable reference
     * @param func          The mapped function
     */
    template<typename Tuple, typename Func>
    constexpr void tuple_for_each(Tuple const &tuple_in1, Tuple const &tuple_in2, Tuple &tuple_out, Func &&func)
    {
        detail::tuple_for_each(
                tuple_in1,
                tuple_in2,
                tuple_out,
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
