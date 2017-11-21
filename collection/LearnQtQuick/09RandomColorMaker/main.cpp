#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "randomcolormaker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RandomColorMaker>("an.qt.RandomColorMaker", 1, 0, "RandomColorMaker");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
