#include <model.hpp>

#include <iostream>
#include <QDebug>

Model::Model(QObject *parent) : QObject(parent) {
}

void Model::resetModel() {
    nn = neural_network{};

    send(0, 0);
    emit showPopup(QStringLiteral("Model reset"));
}

void Model::loadModel(std::string &&location) {
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

void show_image(std::size_t index, auto const &dataset)
{
    auto const &img = dataset.train_images[index];
    for (auto i = 0u; i < img.size(); ++i)
    {
        std::printf("%3d ", img[i]);
        if (i % 28 == 27)
            std::cout << '\n';
    }
    std::printf("\nLabel: %d\n", dataset.train_labels[index]);
}

void Model::trainModel(std::array<float, 28 * 28> const &grid) {
    std::size_t random_index = 420;
    auto const &img = dataset.train_images[random_index];
    show_image(random_index, dataset);
    gnnt::normalize(img.cbegin(), img.cend(), norm_img.begin(), 0, 255);

    auto [chrom, generations] = trainer.train(
        [&](auto &population) {
            for (auto &c: population)
            {
                auto res = c.network(norm_img);
                // This loss function is minimal when res[0] == res[1] == 0.5
                c.loss = std::abs(res[0] - 0.5) + std::abs(res[1] - 0.5);
            }
        },
        [this](std::size_t generations, float loss) {
            send(generations, loss);
        }
    );

    nn = chrom.network;

    send(generations, chrom.loss);
    emit showPopup(QStringLiteral("Model trained"));
}

void Model::saveModel(std::string &&location) {
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

void Model::updateModel(std::array<float, 28 * 28> const &grid) {
    std::array<float, 10> predictions{};
    predictions = nn(grid);
    send(predictions);
}

void Model::send(std::array<float, 10> const &predictions) {
    QVariantList qpredictions{};
    for (auto const &prediction: predictions) {
        qpredictions.append(QVariant::fromValue(prediction * 100));
    }
    emit updatePredictions(qpredictions);
}

void Model::send(std::size_t generations, float accuracy) {
    emit updateTrainData(generations, accuracy);
}
