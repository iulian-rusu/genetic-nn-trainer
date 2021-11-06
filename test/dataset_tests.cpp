#include <iostream>
#include <gnnt.hpp>
#include <array>

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

int main()
{
    auto dataset = gnnt::mnist_serializer::read("../../data/mnist");
    std::size_t random_index = 420;

    std::cout << "Train images: " << dataset.train_images.size() << '\n';
    std::cout << "Test images: " << dataset.test_images.size() << '\n';
    std::cout << "Train labels: " << dataset.train_labels.size() << '\n';
    std::cout << "Test labels: " << dataset.test_labels.size() << '\n';

    show_image(random_index, dataset);
    gnnt::mnist_serializer::write("data_tmp", dataset);
    dataset = gnnt::mnist_serializer::read("data_tmp");
    show_image(random_index, dataset);
}