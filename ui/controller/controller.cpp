#include <array>
#include <controller.hpp>

Controller::Controller(Model *amodel, QObject *parent) : QObject(parent), model(amodel) {}

void Controller::onResetModel() {
    model->resetModel();
}

void Controller::onLoadModel(QUrl const &qlocation) {
    auto location = qlocation.toLocalFile().toStdString();
    model->loadModel(std::move(location));
}

void Controller::onTrainModel(QVariantList const &qgrid) {
    gnnt::mnist_image<value_type> grid{};

    for (qsizetype i = 0; i < qgrid.size(); ++i) {
        auto const &row = qgrid[i].toList();
        for (qsizetype j = 0; j < row.size(); ++j) {
            grid[i * 28 + j] = row[j].toFloat();
        }
    }

    emit model->trainModel(grid);
}

void Controller::onSaveModel(QUrl const &qlocation) {
    auto location = qlocation.toLocalFile().toStdString();
    model->saveModel(std::move(location));
}

void Controller::onUpdateModel(QVariantList const &qgrid) {
    gnnt::mnist_image<value_type> grid{};

    for (qsizetype i = 0; i < qgrid.size(); ++i) {
        auto const &row = qgrid[i].toList();
        for (qsizetype j = 0; j < row.size(); ++j) {
            grid[i * 28 + j] = row[j].toFloat();
        }
    }

    model->updateModel(grid);
}
