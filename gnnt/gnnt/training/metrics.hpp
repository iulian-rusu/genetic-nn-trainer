#ifndef GENETIC_NN_TRAINER_METRICS_HPP
#define GENETIC_NN_TRAINER_METRICS_HPP

#include <execution>
#include <numeric>

namespace gnnt
{
    /**
     * Calculates the Categorical Cross-Entropy loss assuming mutually-exclusive categories.
     */
    template<typename ExecutionPolicy, typename Model, typename DataIter, typename LabelIter>
    auto categorical_crossentropy(
            ExecutionPolicy &&policy,
            Model const &model,
            DataIter data_begin,
            DataIter data_end,
            LabelIter label_iter
    ) noexcept
    {
        using value_type = typename Model::value_type;

        value_type loss = std::transform_reduce(
                std::forward<ExecutionPolicy>(policy), data_begin, data_end, label_iter, value_type{0.0},
                std::plus<>{},
                [&](auto const &data, auto lbl) {
                    auto preds = model(data);
                    return -std::log(preds[lbl] + 1e-12);
                }
        );
        auto batch_size = std::distance(data_begin, data_end);
        return loss / batch_size;
    }

    template<typename Model, typename DataIter, typename LabelIter>
    double accuracy(Model const &model, DataIter data_begin, DataIter data_end, LabelIter labels_begin)
    {
        using value_type = typename Model::value_type;

        auto data_size = std::distance(data_begin, data_end);
        std::vector<std::array<value_type, 10>> preds(data_size);
        std::transform(data_begin, data_end, preds.begin(), [&](auto const &img) {
            return model(img);
        });
        int correct_preds = std::inner_product(
                preds.cbegin(), preds.cend(), labels_begin, 0.0, std::plus<>{},
                [](auto const &pred, auto label) {
                    auto max_pos = std::max_element(pred.cbegin(), pred.cend());
                    return std::distance(pred.cbegin(), max_pos) == label ? 1 : 0;
                }
        );
        return correct_preds * 1.0 / data_size;
    }
}

#endif //GENETIC_NN_TRAINER_METRICS_HPP
