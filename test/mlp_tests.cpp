#include <gnnt/mlp/network.hpp>

using namespace gnnt::mlp;

using neural_network =
        network
        <
            input<float, 28 * 28>,      // Input data = 784 pixels
            layer<float, 5, relu>,      // First inner layer, 5 neurons => 784 * 5 weights, 5 biases
            layer<float, 10, relu>,     // Second inner layer, 10 neurons => 5 * 10 weights, 10 biases
            layer<float, 10, softmax>   // Output layer, 10 neurons => 10 * 10 weights, 10 biases
        >;

static_assert(
        std::is_same_v
        <
            typename neural_network::biases_t,
            std::tuple
            <
                std::array<float, 5>,      // Biases for first inner layer
                std::array<float, 10>,     // Biases for second inner layer
                std::array<float, 10>      // Biases for output layer
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
                std::array<std::array<float, 5>, 10>,
                std::array<std::array<float, 10>, 10>
            >
        >
);