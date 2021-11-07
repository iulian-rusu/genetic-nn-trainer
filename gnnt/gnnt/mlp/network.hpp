#ifndef GENETIC_NN_TRAINER_NETWORK_HPP
#define GENETIC_NN_TRAINER_NETWORK_HPP

#include <gnnt/utility/meta.hpp>
#include <gnnt/utility/random.hpp>
#include <gnnt/utility/tuple_helpers.hpp>
#include <gnnt/utility/pipeline.hpp>
#include <gnnt/mlp/allocators.hpp>

namespace gnnt::mlp
{
    template<typename Input, typename... Layers>
    struct network
    {
        static constexpr std::size_t num_layers = sizeof... (Layers) + 1;

        using biases_t = typename bias_allocator<Layers ...>::template type<>;
        using weights_t = typename weight_allocator<Input, Layers ...>::template type<>;

        template<std::size_t I>
        using layer_t = typename detail::layer_type<I, biases_t, Input>::type;

        using input_t = layer_t<0>;
        using output_t = layer_t<num_layers - 1>;

        template<std::size_t I>
        static constexpr std::size_t layer_size = array_size<layer_t<I>>;

        static constexpr std::size_t input_size = Input::size;
        static constexpr std::size_t output_size = last_t<Layers ...>::size;
        static constexpr auto activations = std::tuple{activation<Layers>{} ...};

        biases_t biases{};
        weights_t weights{};

        template<std::floating_point T>
        explicit network(std::uniform_real_distribution<T> dist) noexcept
        {
            auto factory = random_generator_factory{};
            auto rng = factory.create(std::move(dist));
            tuple_for_each(biases, [&](auto &b) {
                std::generate(b.begin(), b.end(), rng);
            });
            tuple_for_each(weights, [&](auto &layer) {
                for (auto &w: layer)
                    std::generate(w.begin(), w.end(), rng);
            });
        }

        network() noexcept : network(std::uniform_real_distribution(-1.0f, 1.0f))
        {}

        output_t operator()(input_t const &input) const noexcept
        {
            return fold(input, std::make_index_sequence<num_layers - 1>{});
        }

    private:
        template<std::size_t I>
        layer_t<I + 1> feed_forward(layer_t<I> const &input) const noexcept
        {
            auto const &w = std::get<I>(weights);
            auto const &b = std::get<I>(biases);
            layer_t<I + 1> result{};

            for (std::size_t i = 0; i < result.size(); ++i)
                result[i] = std::inner_product(input.cbegin(), input.cend(), w[i].cbegin(), 0.0) + b[i];
            std::get<I>(activations)(result);
            return result;
        }

        template<std::size_t... Indices>
        output_t fold(input_t const &input, std::index_sequence<Indices ...> &&) const noexcept
        {
            return (input  | ... | [&](auto const &x) { return feed_forward<Indices>(x); });
        }
    };
}
#endif //GENETIC_NN_TRAINER_NETWORK_HPP
