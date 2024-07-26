#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "network/foodconfig.h"

#include "ComponentRegister/storage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<FoodConfig>("Client.FoodConfig",1,0,"FoodConfig");//类注入
    qmlRegisterType<Storage>("Client.Storage",1,0,"Storage");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
