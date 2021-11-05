#ifndef GNNT_META_HPP
#define GNNT_META_HPP

#include <ranges>
#include <type_traits>

namespace gnnt
{
    template<std::ranges::range R>
    using value_type = std::decay_t<decltype(*(std::declval<R>().begin()))>;
}
#endif //GNNT_META_HPP
