#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "databases.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQmlApplicationEngine engine;
    Databases db;

    engine.rootContext()->setContextProperty("db", &db);
    engine.load(QUrl(QStringLiteral("qrc:/home.qml")));

    return a.exec();
}

//    QString user, pwd;
//    QString name, number;
//    db.insertData("turnserver","voip","turn.pjsip.org");
//    if (db.loginDB("Danang2", "102")) {
//        db.updateData("turnserver","120.89.94.18:33478");
//        db.insertData("turnserver","voip","turn.pjsip.org");
//        db.readAllData();
//        db.readData(name, number);
//        QString nm = db.getContact("turnserver");
//        qDebug() << nm;
//    }
