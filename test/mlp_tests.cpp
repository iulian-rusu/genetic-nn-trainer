#include <gnnt/mlp/network.hpp>
#include <iostream>

using namespace gnnt::mlp;

using neural_network =
        network
        <
            float,
            input<28 * 28>,
            dense<5, leaky_relu>,
            dense<8, relu>,
            dense<10, softmax>
        >;

static_assert(
        std::is_same_v
        <
            typename neural_network::biases_t,
            std::tuple
            <
                std::array<float, 5>,
                std::array<float, 8>,
                std::array<float, 10>
            >
        >
);

static_assert(
        std::is_same_v
        <
            typename neural_network::weights_t,
            std::tuple
            <
                std::array<std::array<float, 28 * 28>, 5>,
                std::array<std::array<float, 5>, 8>,
                std::array<std::array<float, 8>, 10>
            >
        >
);
