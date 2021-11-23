#include <iostream>
#include <array>
#include <gnnt.hpp>

void show_image(std::size_t index, auto const &dataset)
{
    auto const &img = dataset.train_images[index];
    for (auto i = 0u; i < img.size(); ++i)
    {
        std::printf("%3d ", img[i]);
        if (i % 28 == 27)
            std::cout << '\n';
    }
    std::printf("\nLabel: %d\n", dataset.train_labels[index]);
}

using namespace gnnt::mlp;

using neural_network =
        network
        <
            float,
            input<gnnt::image_dimension>,
            dense<8, prelu<0.01>>,
            dense<8, prelu<0.01>>,
            dense<10, softmax>
        >;

int main()
{
    auto dataset = gnnt::mnist_serializer::read("../../data/mnist");
    std::size_t random_index = 420;

    std::cout << "Train images: " << dataset.train_images.size() << '\n';
    std::cout << "Test images: " << dataset.test_images.size() << '\n';
    std::cout << "Train labels: " << dataset.train_labels.size() << '\n';
    std::cout << "Test labels: " << dataset.test_labels.size() << '\n';
    show_image(random_index, dataset);

    auto const &img = dataset.train_images[random_index];
    gnnt::mnist_image<float> norm_img{};
    gnnt::normalize(img.cbegin(), img.cend(), norm_img.begin(), 0, 255);

    // Example of how to create and train models
    constexpr auto config = gnnt::trainer_config{
            .max_generations = 1000,
            .population_size = 100,
            .mutation_prob = 0.04,
            .crossover_alpha = 0.33,
            .precision = 1e-2,
            .search_space = {-2, 2}
    };
    auto trainer = gnnt::trainer<gnnt::chromosome<neural_network>, config>{};

    auto[chrom, generations] = trainer.train(
            [&](auto &population) {
                for (auto &c: population)
                {
                    auto res = c.network(norm_img);
                    // This loss function is minimal when res[0] == res[1] == 0.5
                    c.loss = std::abs(res[0] - 0.5) + std::abs(res[1] - 0.5);
                }
            }
    );

    std::cout << "Generations: " << generations << '\n';
    auto out = chrom.network(norm_img);
    for (auto e: out)
        std::cout << e << ' ';
}