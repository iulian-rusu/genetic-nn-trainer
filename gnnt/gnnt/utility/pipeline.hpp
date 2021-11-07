#ifndef GENETIC_NN_TRAINER_PIPELINE_HPP
#define GENETIC_NN_TRAINER_PIPELINE_HPP

namespace gnnt
{
    template<typename T, typename F>
    decltype(auto) operator|(T &&t, F &&f)
    {
        return f(std::forward<T>(t));
    }

    template<std::input_iterator In, std::forward_iterator Out, typename T>
    auto normalize(In begin, In end, Out dst, T min, T max)
    {
        std::decay_t<decltype(*dst)> const d = max - min;
        std::transform(begin, end, dst, [=](auto e) {
            return (e - min) / d;
        });
    }
}
#endif //GENETIC_NN_TRAINER_PIPELINE_HPP
