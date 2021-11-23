#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controller.hpp>
#include <model.hpp>

static_assert(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0), "QT >= 6.0.0 required");

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/view/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    Model *model{new Model{}};
    engine.rootContext()->setContextProperty("model", model);
    Controller controller{model};
    engine.rootContext()->setContextProperty("controller", &controller);

    engine.load(url);

    return QGuiApplication::exec();
}
