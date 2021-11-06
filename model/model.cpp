#include "model.h"

Model::Model(QObject *parent) : QObject(parent) {}

void Model::resetModel() {
    /*
     * TODO reset model
     */

    send(0, 0);
}

void Model::loadModel(std::string location) {
    /*
     * TODO load model from file
     */
}

void Model::trainModel() {
    std::size_t generations{0};
    double accuracy{0};

    /*
     * TODO train model
     */

    send(generations, accuracy);
}

void Model::saveModel(std::string location) {
    /*
     * TODO save model to file
     */
}

void Model::updateModel(std::array<std::array<std::uint8_t, 28>, 28> grid) {
    /*
     * TODO update model if needed
     */

    computePredictions();
}

void Model::computePredictions() {
    std::array<double, 10> predictions{};

    /*
     * TODO calculate predictions
     */

    send(predictions);
}

void Model::send(std::array<double, 10> predictions) {
    QVariantList qpredictions{};
    for (auto const &prediction: predictions) {
        qpredictions.append(QVariant::fromValue(prediction));
    }
    emit updatePredictions(qpredictions);
}

void Model::send(std::size_t generations, double accuracy) {
    emit updateTrainData(generations, accuracy);
}
