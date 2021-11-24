#ifndef GENETIC_NN_TRAINER_MODEL_HPP
#define GENETIC_NN_TRAINER_MODEL_HPP

#include <QObject>
#include <QString>
#include <QThread>
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
    void saveModel(std::string &&);
    void updateModel(gnnt::mnist_image<value_type> const &);
    void train();

signals:
    void updateTrainData(int, float);
    void updatePredictions(QVariantList const &);
    void showPopup(QString const &);
    void trainModel(std::array<float, 28 * 28> const &);

private slots:
    void onTrainModel(std::array<float, 28 * 28> const &);

private:
    void computePredictions();
    void send(std::array<value_type, 10> const &);
    void send(std::size_t, value_type);

    gnnt::normalized_mnist_dataset<value_type> dataset = normalize(
            gnnt::mnist_serializer::read("../data/mnist"),
            value_type{0},
            value_type{255}
    );
    neural_network nn{};
    gnnt::trainer<gnnt::chromosome<neural_network>, config> trainer{};
};

class WorkerThread : public QThread
{
Q_OBJECT

public:
    WorkerThread(Model *parent = nullptr) : QThread(parent), model(parent) { }

private:
    void run() override
    {
        model->train();
    }
signals:
    void resultReady(const QString &s);

private:
    Model *model;
};

#endif //GENETIC_NN_TRAINER_MODEL_HPP
