#ifndef GENETIC_NN_TRAINER_METRICS_HPP
#define GENETIC_NN_TRAINER_METRICS_HPP

namespace gnnt
{
    /**
     * Calculates the Categorical Cross-Entropy loss assuming mutually-exclusive categories.
     */
    template<std::size_t batch_size, typename Model, typename DataIter, typename LabelIter>
    auto categorical_crossentropy(Model const &model, DataIter data_begin, LabelIter label_iter) noexcept
    {
        using value_type = typename Model::value_type;

        value_type loss = 0.0;
        for (auto it = data_begin; it != data_begin + batch_size; ++it, ++label_iter)
        {
            auto label = *label_iter;
            auto preds = model(*it);
            loss -= std::log(preds[label]);

        }
        return loss / batch_size;
    }

    template<typename PredIter, typename LabelIter>
    double accuracy(PredIter preds_begin, PredIter preds_end, LabelIter labels_begin)
    {
        auto length = std::distance(preds_begin, preds_end);
        int correct_preds = std::inner_product(preds_begin, preds_end, labels_begin, 0.0, std::plus<>{},
                [](auto const &pred, auto label) {
                    auto max_pos = std::max_element(pred.cbegin(), pred.cend());
                    return std::distance(pred.cbegin(), max_pos) == label ? 1 : 0;
                });
        return correct_preds * 1.0 / length;
    }
}

#endif //GENETIC_NN_TRAINER_METRICS_HPP
