#ifndef GENETIC_NN_TRAINER_PIPELINE_HPP
#define GENETIC_NN_TRAINER_PIPELINE_HPP

#include <gnnt/utility/pair.hpp>

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

    template<typename T, typename Image, template<typename> typename ImageContainer, typename LabelContainer>
    requires std::is_floating_point_v<T>
    auto normalize(basic_mnist_dataset<ImageContainer<Image>, LabelContainer> const &dataset, T min, T max)
    {
        using normalized_image = mnist_image<T>;

        auto const train_size = dataset.train_images.size();
        auto const test_size = dataset.test_images.size();
        ImageContainer<normalized_image> train_norm_images(train_size);
        ImageContainer<normalized_image> test_norm_images(test_size);

        for (auto i = 0u; i < train_size; ++i)
        {
            auto const &img = dataset.train_images[i];
            normalize(img.cbegin(), img.cend(), train_norm_images[i].begin(), min, max);
        }

        for (auto i = 0u; i < test_size; ++i)
        {
            auto const &img = dataset.test_images[i];
            normalize(img.cbegin(), img.cend(), test_norm_images[i].begin(), min, max);
        }

        return basic_mnist_dataset{
                std::move(train_norm_images),
                std::move(test_norm_images),
                dataset.train_labels,
                dataset.test_labels
        };
    }

    template<std::size_t batch_size, typename Range>
    auto batch(Range const &range) noexcept
    {
        auto const max_offset = std::size(range) / batch_size;

        return [=, offset = 0ull]() mutable noexcept -> pair<std::size_t, std::size_t> {
            auto start = offset * batch_size;
            offset = (offset + 1) % max_offset;
            return {start, start + batch_size};
        };
    }
}
#endif //GENETIC_NN_TRAINER_PIPELINE_HPP
