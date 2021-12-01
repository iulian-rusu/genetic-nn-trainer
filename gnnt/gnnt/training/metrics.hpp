#ifndef GENETIC_NN_TRAINER_METRICS_HPP
#define GENETIC_NN_TRAINER_METRICS_HPP

#include <execution>
#include <numeric>

namespace gnnt
{
    /**
     * Calculates the Categorical Cross-Entropy loss assuming mutually-exclusive categories.
     */
    template<std::size_t batch_size, typename Model, typename DataIter, typename LabelIter>
    auto categorical_crossentropy(Model const &model, DataIter data_begin, LabelIter label_iter) noexcept
    {
        using value_type = typename Model::value_type;

        static constexpr double epsilon = 1e-12;
        value_type loss = std::transform_reduce(
                std::execution::par_unseq, data_begin, data_begin + batch_size, label_iter, value_type{0.0},
                std::plus<>{},
                [&](auto const &data, auto lbl) {
                    auto preds = model(data);
                    return -std::log(preds[lbl] + epsilon);
                }
        );
        return loss / batch_size;
    }

    template<typename PredIter, typename LabelIter>
    double accuracy(PredIter preds_begin, PredIter preds_end, LabelIter labels_begin)
    {
        auto length = std::distance(preds_begin, preds_end);
        int correct_preds = std::inner_product(
                preds_begin, preds_end, labels_begin, 0.0, std::plus<>{},
                [](auto const &pred, auto label) {
                    auto max_pos = std::max_element(pred.cbegin(), pred.cend());
                    return std::distance(pred.cbegin(), max_pos) == label ? 1 : 0;
                }
        );
        return correct_preds * 1.0 / length;
    }
}

#endif //GENETIC_NN_TRAINER_METRICS_HPP
