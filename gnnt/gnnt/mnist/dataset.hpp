#ifndef GENETIC_NN_TRAINER_MNIST_DATASET_HPP
#define GENETIC_NN_TRAINER_MNIST_DATASET_HPP

#include <gnnt/utility/meta.hpp>

namespace gnnt
{
    template<typename ImageContainer, typename LabelContainer>
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
        basic_mnist_dataset(I &&train_img, I &&test_img, L &&train_lbl, L &&test_lbl)
                : train_images{std::forward<I>(train_img)},
                  test_images{std::forward<I>(test_img)},
                  train_labels{std::forward<L>(train_lbl)},
                  test_labels{std::forward<L>(test_lbl)}
        {}
    };

    template<typename I, typename L>
    basic_mnist_dataset(I &&, I &&, L &&, L &&) -> basic_mnist_dataset<std::decay_t<I>, std::decay_t<L>>;
}
#endif //GENETIC_NN_TRAINER_MNIST_DATASET_HPP
