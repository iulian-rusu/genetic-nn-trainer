#include <model.hpp>

#include <execution>
#include <iostream>
#include <thread>

Model::Model(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &Model::trainModel, this, &Model::onTrainModel);
    std::cout << "Train images: " << dataset.train_images.size() << '\n';
    std::cout << "Test images: " << dataset.test_images.size() << '\n';
}

void Model::train()
{
    constexpr std::size_t batch_size = 12000;
    auto batch_begin = dataset.train_images.cbegin();
    auto lbl_begin = dataset.train_labels.cbegin();

    auto[chrom, generations] = trainer.train(
            [&](auto &population) {
                std::for_each(
                        population.begin(), population.end(),
                        [&](auto &c) noexcept {
                            c.loss = gnnt::categorical_crossentropy<batch_size>(c.network, batch_begin, lbl_begin);
                        }
                );
            },
            [&](std::size_t gen, value_type loss) {
                send(gen, loss, 3, 5);
            }
    );
    nn = chrom.network;

    // How to calculate accuracy example:
    std::vector<std::array<value_type, 10>> preds(batch_size);
    for (auto i = 0u; i < preds.size(); ++i)
        preds[i] = nn(dataset.train_images[i]);
    double acc = gnnt::accuracy(preds.cbegin(), preds.cend(), dataset.train_labels.cbegin());
    std::cout << "Accuracy over " << preds.size() << " train images: " << acc << '\n';

    std::vector<std::array<value_type, 10>> test_preds(dataset.test_images.size());
    for (auto i = 0u; i < test_preds.size(); ++i)
        test_preds[i] = nn(dataset.test_images[i]);
    acc = gnnt::accuracy(test_preds.cbegin(), test_preds.cend(), dataset.test_labels.cbegin());
    std::cout << "Accuracy over " << test_preds.size() << " test images: " << acc << '\n';

    send(generations, chrom.loss, (value_type)acc, 0);
    emit showPopup(QStringLiteral("Model trained"));
}

void Model::resetModel()
{
    nn = neural_network{};
    send(0, 0, 0, 0);
    emit showPopup(QStringLiteral("Model reset"));
}

void Model::loadModel(std::string &&location)
{
    try
    {
        nn.read(location);
        emit showPopup(QStringLiteral("Model loaded"));
    } catch (...)
    {
        emit showPopup(QStringLiteral("Could not load model"));
    }
}

void Model::onTrainModel(gnnt::mnist_image<value_type> const &)
{
    auto *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void Model::saveModel(std::string &&location)
{
    try
    {
        nn.write(location);
        emit showPopup(QStringLiteral("Model saved"));
    } catch (...)
    {
        emit showPopup(QStringLiteral("Could not save model"));
    }
}

void Model::updateModel(gnnt::mnist_image<value_type> const &grid)
{
    std::array<value_type, 10> predictions{};
    predictions = nn(grid);
    send(predictions);
}

void Model::send(std::array<value_type, 10> const &predictions)
{
    QVariantList qpredictions{};
    for (auto const &prediction: predictions)
    {
        qpredictions.append(QVariant::fromValue(prediction * 100));
    }
    emit updatePredictions(qpredictions);
}

void Model::send(std::size_t generations, value_type loss, value_type accuracy, value_type precision)
{
    emit updateTrainData((int) generations, (float) loss, (float) accuracy * 100, (float) precision * 100);
}
