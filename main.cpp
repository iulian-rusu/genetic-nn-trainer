#include <iostream>
#include <gnnt.hpp>

int main()
{
    auto dataset = gnnt::mnist_serializer::read("../data");

    std::cout << "Train images: " << dataset.train_images.size() << '\n';
    std::cout << "Test images: " << dataset.test_images.size() << '\n';
    std::cout << "Train labels: " << dataset.train_labels.size() << '\n';
    std::cout << "Test labels: " << dataset.test_labels.size() << '\n';

    std::size_t random_index = 420;

    auto &img = dataset.train_images[random_index];
    for (auto i = 0u; i < img.size(); ++i)
    {
        std::printf("%3d ", img[i]);
        if (i % 28 == 27)
            std::cout << '\n';
    }
    std::printf("\nLabel: %d\n", dataset.train_labels[random_index]);
}
