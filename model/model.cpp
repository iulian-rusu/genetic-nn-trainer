#include "model.h"

Model::Model(QObject *parent) : QObject(parent) {}

void Model::resetModel() {
    /*
     * TODO reset model
     */

    send(0, 0);
    emit showPopup(QStringLiteral("Model reset"));
}

void Model::loadModel(std::string location) {
    bool modelLoaded = false;

    /*
     * TODO load model from file
     */

    if (modelLoaded) {
        emit showPopup(QStringLiteral("Model loaded"));
    }
    else {
        emit showPopup(QStringLiteral("Could not load model"));
    }
}

void Model::trainModel() {
    std::size_t generations{0};
    double accuracy{0};

    /*
     * TODO train model
     */

    send(generations, accuracy);
    emit showPopup(QStringLiteral("Model trained"));
}

void Model::saveModel(std::string location) {
    bool modelSaved = false;

    /*
     * TODO save model to file
     */

    if (modelSaved) {
        emit showPopup(QStringLiteral("Model saved"));
    }
    else {
        emit showPopup(QStringLiteral("Could not save model"));
    }
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
