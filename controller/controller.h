#ifndef GENETIC_NN_TRAINER_CONTROLLER_H
#define GENETIC_NN_TRAINER_CONTROLLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantList>
#include "model.h"

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(Model *, QObject * = nullptr);

public slots:
    void onResetModel();
    void onLoadModel(QUrl const &);
    void onTrainModel();
    void onSaveModel(QUrl const &);
    void onUpdateModel(QVariantList const &);

private:
    Model *model;
};

#endif //GENETIC_NN_TRAINER_CONTROLLER_H
