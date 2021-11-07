#ifndef GENETIC_NN_TRAINER_MODEL_HPP
#define GENETIC_NN_TRAINER_MODEL_HPP

#include <QObject>
#include <QString>
#include <QVariantList>
#include <array>
#include <string>
#include <gnnt.hpp>

class Model : public QObject {
    Q_OBJECT
public:
    explicit Model(QObject * = nullptr);
    void resetModel();
    void loadModel(std::string &&);
    void trainModel();
    void saveModel(std::string &&);
    void updateModel(std::array<std::array<std::uint8_t, 28>, 28>);

signals:
    void updateTrainData(std::size_t, double);
    void updatePredictions(QVariantList);
    void showPopup(QString);

private:
    void computePredictions();
    void send(std::array<double, 10>);
    void send(std::size_t, double);
};

#endif //GENETIC_NN_TRAINER_MODEL_HPP
