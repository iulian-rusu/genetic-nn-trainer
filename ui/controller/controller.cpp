#include <array>
#include <controller.hpp>

Controller::Controller(Model *amodel, QObject *parent) : QObject(parent), model(amodel) {}

void Controller::onResetModel() {
    model->resetModel();
}

void Controller::onLoadModel(QUrl const &qlocation) {
    auto location = qlocation.toString().toStdString();
    model->loadModel(std::move(location));
}

void Controller::onTrainModel(QVariantList const &qgrid) {
    std::array<float, 28 * 28> grid{};

    for (qsizetype i = 0; i < qgrid.size(); ++i) {
        auto const &row = qgrid[i].toList();
        for (qsizetype j = 0; j < row.size(); ++j) {
            grid[i * 28 + j] = row[j].toBool();
        }
    }

    emit model->trainModel(grid);
}

void Controller::onSaveModel(QUrl const &qlocation) {
    auto location = qlocation.toString().toStdString();
    model->saveModel(std::move(location));
}

void Controller::onUpdateModel(QVariantList const &qgrid) {
    std::array<float, 28 * 28> grid{};

    for (qsizetype i = 0; i < qgrid.size(); ++i) {
        auto const &row = qgrid[i].toList();
        for (qsizetype j = 0; j < row.size(); ++j) {
            grid[i * 28 + j] = row[j].toBool();
        }
    }

    model->updateModel(grid);
}
