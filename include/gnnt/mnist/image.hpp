#ifndef GENETIC_NN_TRAINER_IMAGE_HPP
#define GENETIC_NN_TRAINER_IMAGE_HPP

namespace gnnt
{
    static inline constexpr std::size_t image_dimension = 28 * 28;

    template<typename T = uint8_t>
    using mnist_image = std::array<T, image_dimension>;
}
#endif //GENETIC_NN_TRAINER_IMAGE_HPP
