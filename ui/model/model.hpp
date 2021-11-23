#ifndef GENETIC_NN_TRAINER_MODEL_HPP
#define GENETIC_NN_TRAINER_MODEL_HPP

#include <QObject>
#include <QString>
#include <QVariantList>

#include <array>
#include <string>

#include <gnnt.hpp>

using namespace gnnt::mlp;

using neural_network =
    network
        <
                float,
                input<gnnt::image_dimension>,
                dense<8, prelu<0.01>>,
                dense<8, prelu<0.01>>,
                dense<10, softmax>
        >;

constexpr static auto config = gnnt::trainer_config{
        .max_generations = 1000,
        .population_size = 100,
        .mutation_prob = 0.04,
        .crossover_alpha = 0.33,
        .precision = 1e-2,
        .search_space = {-2, 2}
};

class Model : public QObject {
    Q_OBJECT
public:
    explicit Model(QObject * = nullptr);
    void resetModel();
    void loadModel(std::string &&);
    void trainModel(std::array<float, 28 * 28> const &);
    void saveModel(std::string &&);
    void updateModel(std::array<float, 28 * 28> const &);

signals:
    void updateTrainData(std::size_t, float);
    void updatePredictions(QVariantList const &);
    void showPopup(QString const &);

private:
    void computePredictions();
    void send(std::array<float, 10> const &);
    void send(std::size_t, float);

    using dataset_t = decltype(gnnt::mnist_serializer::read("../data/mnist"));
    dataset_t dataset{gnnt::mnist_serializer::read("../data/mnist")};
    std::array<float, gnnt::image_dimension> norm_img{};
    neural_network nn{};
    gnnt::trainer<gnnt::chromosome<neural_network>, config> trainer{};
};

#endif //GENETIC_NN_TRAINER_MODEL_HPP
