#ifndef GNNT_MNIST_DATASET_HPP
#define GNNT_MNIST_DATASET_HPP

#include <gnnt/utility/concepts.hpp>

namespace gnnt
{
    template<bidimensional_container ImageContainer, container LabelContainer>
    struct basic_mnist_dataset
    {
        using image_t = gnnt::value_type<ImageContainer>;
        using label_t = gnnt::value_type<LabelContainer>;
        using pixel_t = gnnt::value_type<image_t>;

        ImageContainer train_images{};
        ImageContainer test_images{};
        LabelContainer train_labels{};
        LabelContainer test_labels{};

        template<typename I, typename L>
        basic_mnist_dataset(I &&train_images, I &&test_images, L &&train_labels, L &&test_labels)
                : train_images{std::forward<I>(train_images)},
                  test_images{std::forward<I>(test_images)},
                  train_labels{std::forward<L>(train_labels)},
                  test_labels{std::forward<L>(test_labels)}
        {}
    };
}
#endif //GNNT_MNIST_DATASET_HPP
