#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controller.h>
#include <model.h>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <sstream>
#include <stdexcept>
#endif

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    std::ostringstream oss;
    oss << "QT_VERSION = " << QT_VERSION << " >= 6.0.0 REQUIRED QT_VERSION = ";
    throw std::runtime_error(oss.str());
#endif
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

    return app.exec();
}
