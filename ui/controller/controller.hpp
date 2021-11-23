#ifndef GENETIC_NN_TRAINER_CONTROLLER_HPP
#define GENETIC_NN_TRAINER_CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantList>
#include "model.hpp"

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(Model *, QObject * = nullptr);

public slots:
    void onResetModel();
    void onLoadModel(QUrl const &);
    void onTrainModel(QVariantList const &qgrid);
    void onSaveModel(QUrl const &);
    void onUpdateModel(QVariantList const &);

private:
    Model *model;
};

#endif //GENETIC_NN_TRAINER_CONTROLLER_HPP
