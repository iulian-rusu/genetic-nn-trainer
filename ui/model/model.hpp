#ifndef GENETIC_NN_TRAINER_MODEL_HPP
#define GENETIC_NN_TRAINER_MODEL_HPP

#include <QObject>
#include <QString>
#include <QVariantList>
#include <array>
#include <string>
#include <config.hpp>

class Model : public QObject {
    Q_OBJECT
public:
    explicit Model(QObject * = nullptr);
    void resetModel();
    void loadModel(std::string &&);
    void trainModel(gnnt::mnist_image<value_type> const &);
    void saveModel(std::string &&);
    void updateModel(gnnt::mnist_image<value_type> const &);

signals:
    void updateTrainData(std::size_t, value_type);
    void updatePredictions(QVariantList const &);
    void showPopup(QString const &);

private:
    void computePredictions();
    void send(std::array<value_type, 10> const &);
    void send(std::size_t, value_type);

    gnnt::mnist_dataset dataset{gnnt::mnist_serializer::read("../data/mnist")};
    gnnt::mnist_image<value_type> norm_img{};
    neural_network nn{};
    gnnt::trainer<gnnt::chromosome<neural_network>, config> trainer{};
};

#endif //GENETIC_NN_TRAINER_MODEL_HPP
