#ifndef GENETIC_NN_TRAINER_PIPELINE_HPP
#define GENETIC_NN_TRAINER_PIPELINE_HPP

#include <gnnt/mnist/dataset.hpp>
#include <gnnt/utility/pair.hpp>

#include <iostream>
#include <gnnt/mnist/serializer.hpp>
#include <array>

namespace gnnt
{
    template<typename T, typename F>
    decltype(auto) operator|(T &&t, F &&f)
    {
        return f(std::forward<T>(t));
    }

    template<typename In, typename Out, typename T>
    requires std::is_arithmetic_v<T>
    void normalize(In begin, In end, Out dst, T min, T max) noexcept
    {
        std::remove_cvref_t<decltype(*dst)> const d = max - min;
        std::transform(begin, end, dst, [=](auto e) {
            return (e - min) / d;
        });
    }

    template<typename To, typename Value, typename Dataset>
    requires std::is_arithmetic_v<Value>
    auto normalize(Dataset const &dataset, Value min, Value max)
    {
        return transform<To>(dataset, [=](auto begin, auto end, auto dst) {
            normalize(begin, end, dst, min, max);
        });
    }

    template<typename In, typename Out, typename T>
    requires std::is_arithmetic_v<T>
    void threshold(In begin, In end, Out dst, T th) noexcept
    {
        std::transform(begin, end, dst, [=](auto e) {
            return e >= th ? 1 : 0;
        });
    }

    template<typename To, typename Value, typename Dataset>
    requires std::is_arithmetic_v<Value>
    auto threshold(Dataset const &dataset, Value th)
    {
        return transform<To>(dataset, [=](auto begin, auto end, auto dst) {
            threshold(begin, end, dst, th);
        });
    }

    template<typename To, typename F, typename Dataset>
    auto transform(Dataset const &dataset, F &&func)
    {
        using transformed_image = mnist_image<To>;

        auto const train_size = dataset.train_images.size();
        auto const test_size = dataset.test_images.size();
        std::vector<transformed_image> train_images(train_size);
        std::vector<transformed_image> test_images(test_size);

        for (auto i = 0u; i < train_size; ++i)
        {
            auto const &img = dataset.train_images[i];
            func(img.cbegin(), img.cend(), train_images[i].begin());
        }

        for (auto i = 0u; i < test_size; ++i)
        {
            auto const &img = dataset.test_images[i];
            func(img.cbegin(), img.cend(), test_images[i].begin());
        }

        return basic_mnist_dataset{
                std::move(train_images),
                std::move(test_images),
                dataset.train_labels,
                dataset.test_labels
        };
    }

    template<typename Condition, typename ImageContainer, typename LabelContainer>
    auto filter(basic_mnist_dataset<ImageContainer, LabelContainer> const &dataset, Condition &&cond)
    {
        ImageContainer train_images{};
        ImageContainer test_images{};
        LabelContainer train_labels{};
        LabelContainer test_labels{};

        auto const train_size = dataset.train_images.size();
        auto const test_size = dataset.test_images.size();
        std::size_t filtered_train_size = 0;
        std::size_t filtered_test_size = 0;

        for (auto i = 0u; i < train_size; ++i)
            if (cond(dataset.train_labels[i]))
                ++filtered_train_size;

        for (auto i = 0u; i < test_size; ++i)
            if (cond(dataset.test_labels[i]))
                ++filtered_test_size;

        train_images.reserve(filtered_train_size);
        test_images.reserve(filtered_test_size);
        train_labels.reserve(filtered_train_size);
        test_labels.reserve(filtered_test_size);

        for (auto i = 0u; i < train_size; ++i)
        {
            if (cond(dataset.train_labels[i]))
            {
                train_images.push_back(dataset.train_images[i]);
                train_labels.push_back(dataset.train_labels[i]);
            }
        }

        for (auto i = 0u; i < test_size; ++i)
        {
            if (cond(dataset.test_labels[i]))
            {
                test_images.push_back(dataset.test_images[i]);
                test_labels.push_back(dataset.test_labels[i]);
            }
        }

        return basic_mnist_dataset{
                std::move(train_images),
                std::move(test_images),
                std::move(train_labels),
                std::move(test_labels)
        };
    }

    template<std::size_t batch_size, typename Range>
    auto batch(Range const &range) noexcept
    {
        using iter_t = decltype(std::cbegin(range));
        using diff_t = int;

        auto const max_offset = std::size(range) / batch_size;
        return [=, offset = 0ull]() mutable noexcept {
            diff_t from = offset * batch_size;
            diff_t until = from + batch_size;
            offset = (offset + 1) % max_offset;
            return pair<diff_t, diff_t>{from, until};
        };
    }

    template<typename In>
    auto datasetNormalizing(In dataset)
    {
        std::vector<std::array<float, gnnt::image_dimension>> temp_train_images, temp_test_images;
        std::vector<uint8_t> temp_train_labels, temp_test_labels;
        for (int i =0; i<dataset.train_images.size(); i++) {
            std::array<float, gnnt::image_dimension> norm_img_train{};
            normalize(dataset.train_images[i].cbegin(), dataset.train_images[i].cend(), norm_img_train.begin(), 0, 255);
            temp_train_images.push_back(norm_img_train);
            temp_train_labels.push_back(dataset.train_labels[i]);
        }
        for (int i =0; i<dataset.test_images.size(); i++) {
            std::array<float, gnnt::image_dimension> norm_img_test{};
            normalize(dataset.test_images[i].cbegin(), dataset.test_images[i].cend(), norm_img_test.begin(), 0, 255);
            temp_test_images.push_back(norm_img_test);
            temp_test_labels.push_back(dataset.test_labels[i]);
        }
        using normalized_mnist_dataset = gnnt::basic_mnist_dataset<std::vector<std::array<float, gnnt::image_dimension>>, std::vector<uint8_t>>;
        normalized_mnist_dataset normalizedMnistDataset = normalized_mnist_dataset(temp_train_images, temp_test_images, temp_train_labels, temp_test_labels);
        return normalizedMnistDataset;
    }

//    struct normalizedDataset {
//        std::vector< std::array<float, 784>> float_train_images;
//        std::vector< std::array<float, 784>> float_test_images;
//        };
}
#endif //GENETIC_NN_TRAINER_PIPELINE_HPP
