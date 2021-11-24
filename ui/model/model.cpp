#include <model.hpp>

#include <execution>
#include <iostream>
#include <thread>

Model::Model(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &Model::trainModel, this, &Model::onTrainModel);
}

void Model::train()
{
    constexpr int batch_size = 100;
    constexpr int batch_offset = 0;
    std::vector<gnnt::mnist_image<value_type>> norm_imgs(batch_offset + batch_size);
    for (int i = batch_offset; i < batch_offset + batch_size; ++i)
    {
        auto const &img = dataset.train_images[i];
        gnnt::normalize(img.cbegin(), img.cend(), norm_imgs[i].begin(), 0, 255);
    }

    auto[chrom, generations] = trainer.train(
            [&](auto &population) {
                auto const eval_one = [&](auto &c) noexcept {
                    c.loss = batch_size;
                    for (int i = batch_offset; i < batch_offset + batch_size; ++i)
                    {
                        auto lbl = dataset.train_labels[i];
                        auto res = c.network(norm_imgs[i]);
                        c.loss += std::accumulate(res.cbegin(), res.cend(), 0.0, [](auto acc, auto x) {
                            return acc + x * x;
                        });
                        c.loss -= 2 * res[lbl];
                    }
                    c.loss /= batch_size;
                };
                std::for_each(
                        population.begin(),
                        population.end(),
                        eval_one
                );
            },
            [&](std::size_t gens, value_type loss) {
                send(gens, loss);
            }
    );
    nn = chrom.network;

    send(generations, chrom.loss);
    emit showPopup(QStringLiteral("Model trained"));
}

void Model::resetModel()
{
    nn = neural_network{};

    send(0, 0);
    emit showPopup(QStringLiteral("Model reset"));
}

void Model::loadModel(std::string &&location)
{
    bool modelLoaded = false;

    /*
     * TODO load model from file
     */

    if (modelLoaded)
    {
        emit showPopup(QStringLiteral("Model loaded"));
    }
    else
    {
        emit showPopup(QStringLiteral("Could not load model"));
    }
}

void Model::onTrainModel(gnnt::mnist_image<value_type> const &grid)
{
    auto *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void Model::saveModel(std::string &&location)
{
    bool modelSaved = false;
    try
    {
        nn.write(location);
        modelSaved = true;
    } catch (...)
    {
        std::cerr << "bruh\n";
    }

    if (modelSaved)
    {
        emit showPopup(QStringLiteral("Model saved"));
    }
    else
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

void Model::send(std::size_t generations, value_type loss)
{
    emit updateTrainData((int) generations, (float) loss);
}
