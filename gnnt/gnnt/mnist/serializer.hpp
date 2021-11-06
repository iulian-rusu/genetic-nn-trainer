#ifndef GNNT_MNIST_SERIALIZER_HPP
#define GNNT_MNIST_SERIALIZER_HPP

#include <vector>
#include <fstream>
#include <filesystem>
#include <gnnt/mnist/dataset.hpp>

namespace gnnt
{
    static inline constexpr std::size_t image_dimension = 28 * 28;

    template<bidimensional_container ImageContainer, container LabelContainer>
    struct basic_mnist_serializer
    {
        using dataset_t = basic_mnist_dataset<ImageContainer, LabelContainer>;

        static constexpr std::size_t image_size_bytes = image_dimension * sizeof(typename dataset_t::pixel_t);
        static constexpr std::size_t label_size_bytes = sizeof(typename dataset_t::label_t);

        static dataset_t read(std::string const &dir_path)
        {
            std::string test_images_path = dir_path + "/test_images.data";
            std::string test_labels_path = dir_path + "/test_labels.data";
            std::string train_images_path = dir_path + "/train_images.data";
            std::string train_labels_path = dir_path + "/train_labels.data";

            auto train_images = read_images(train_images_path);
            auto test_images = read_images(test_images_path);
            auto train_labels = read_labels(train_labels_path);
            auto test_labels = read_labels(test_labels_path);

            return {
                    std::move(train_images),
                    std::move(test_images),
                    std::move(train_labels),
                    std::move(test_labels)
            };
        }

        static void write(std::string const &dir_path, dataset_t const &data)
        {
            std::filesystem::create_directory(dir_path);
            std::string test_images_path = dir_path + "/test_images.data";
            std::string test_labels_path = dir_path + "/test_labels.data";
            std::string train_images_path = dir_path + "/train_images.data";
            std::string train_labels_path = dir_path + "/train_labels.data";

            write_images(train_images_path, data.train_images);
            write_images(test_images_path, data.test_images);
            write_labels(train_labels_path, data.train_labels);
            write_labels(test_labels_path, data.test_labels);
        }

    private:
        static ImageContainer read_images(std::string const &path)
        {
            using image_t = typename dataset_t::image_t;

            std::ifstream is(path, std::ios::binary);
            std::size_t size = 0;
            is.read(reinterpret_cast<char *>(&size), sizeof size);

            ImageContainer images(size, image_t{});
            for (auto &img: images)
                is.read(reinterpret_cast<char *>(&img[0]), image_size_bytes);
            return images;
        }

        static LabelContainer read_labels(std::string const &path)
        {
            std::ifstream is(path, std::ios::binary);
            std::size_t size = 0;
            is.read(reinterpret_cast<char *>(&size), sizeof size);

            LabelContainer labels(size);
            is.read(reinterpret_cast<char *>(&labels[0]), size * label_size_bytes);
            return labels;
        }

        static void write_images(std::string const &path, ImageContainer const &images)
        {
            std::ofstream os(path.data(), std::ios::binary | std::ios::trunc);
            std::size_t size = images.size();
            os.write(reinterpret_cast<const char *>(&size), sizeof size);
            for (auto const &img: images)
                os.write(reinterpret_cast<const char *>(&img[0]), image_size_bytes);
        }

        static void write_labels(std::string const &path, LabelContainer const &labels)
        {
            std::ofstream os(path, std::ios::binary | std::ios::trunc);
            std::size_t size = labels.size();
            os.write(reinterpret_cast<const char *>(&size), sizeof size);
            os.write(reinterpret_cast<const char *>(&labels[0]), size * label_size_bytes);
        }
    };

    using mnist_image = std::array<uint8_t, image_dimension>;
    using mnist_serializer = basic_mnist_serializer<std::vector<mnist_image>, std::vector<uint8_t>>;
}
#endif //GNNT_MNIST_SERIALIZER_HPP
