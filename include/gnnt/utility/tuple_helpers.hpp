#ifndef GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
#define GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP

#include <tuple>
#include <gnnt/utility/meta.hpp>

namespace gnnt
{
    namespace detail
    {
        template<std::size_t Index, typename Func, typename... Tuples>
        constexpr void apply_tuples(Func &&func, Tuples &&... tuples)
        {
            func(std::get<Index>(tuples) ...);
        }

        template<typename Func, typename... Tuples,  std::size_t... Indices>
        constexpr void for_each_tuple(std::index_sequence<Indices ...> &&, Func &&func, Tuples &&... tuples)
        {
            (apply_tuples<Indices>(std::forward<Func>(func), std::forward<Tuples>(tuples) ...), ...);
        }
    }

    /**
     * Calls a function for each set of tuple elements. The function arguments are obtained
     * by simultaneously iterating the variadic tuple pack.
     *
     * @example:
     * Given the tuples (a, b, c) and (x, y, z), the funtion calls func(a, x), func(b, y) and func(c, z).
     */
    template<typename Func, typename... Tuples>
    constexpr void for_each_tuple(Func &&func, Tuples &&... tuples)
    {
        detail::for_each_tuple(
                std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<head_t<Tuples ...>>>>{},
                std::forward<Func>(func),
                std::forward<Tuples>(tuples) ...
        );
    }
}
#endif //GENETIC_NN_TRAINER_TUPLE_HELPERS_HPP
