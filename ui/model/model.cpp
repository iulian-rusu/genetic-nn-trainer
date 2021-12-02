#include <model.hpp>

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
    constexpr std::size_t batch_size = 128;
    auto batcher = gnnt::batch<batch_size>(dataset.train_images);
    auto img_begin = dataset.train_images.cbegin();
    auto labels_begin = dataset.train_labels.cbegin();

    auto[chrom, generations] = trainer.train(
            [&](auto &population) {
                auto [a, b] = batcher();
                auto img_batch_begin = img_begin + a;
                auto img_batch_end = img_begin + b;
                auto labels_batch_begin = labels_begin + a;
                std::for_each(
                        population.begin(), population.end(),
                        [&](auto &c) noexcept {
                            c.loss = gnnt::categorical_crossentropy(
                                    c.network,
                                    img_batch_begin,
                                    img_batch_end,
                                    labels_batch_begin
                            );
                        }
                );
            },
            [&](std::size_t gen, value_type loss) {
                send(gen, loss, 0, 0);
            },
            gnnt::chromosome{nn}
    );
    nn = chrom.network;

    // How to calculate accuracy example:
    auto const train_acc = gnnt::accuracy(
            nn,
            dataset.train_images.cbegin(),
            dataset.train_images.cend(),
            dataset.train_labels.cbegin()
    );
    std::cout << "Accuracy over " << dataset.train_images.size() << " train images: " << train_acc << '\n';

    auto const test_acc = gnnt::accuracy(
            nn,
            dataset.test_images.cbegin(),
            dataset.test_images.cend(),
            dataset.test_labels.cbegin()
    );
    std::cout << "Accuracy over " << dataset.test_images.size() << " test images: " << test_acc << '\n';

    send(generations, chrom.loss, (value_type)train_acc, (value_type)test_acc);
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

void Model::send(std::size_t generations, value_type loss, value_type train_accuracy, value_type test_accuracy)
{
    emit updateTrainData((int) generations, (float) loss, (float) train_accuracy * 100, (float) test_accuracy * 100);
}
