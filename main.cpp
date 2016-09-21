#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtDebug>
#include <QString>
#include <QHash>
#include <QGuiApplication>
#include <QtQml>
#include <QQuickView>
#include <QtSql>
#include <QSqlQueryModel>

#include "databases.h"

class SqlModel : public QSqlQueryModel
{

public:
    SqlModel(QObject* parent = 0)
        : QSqlQueryModel(parent)
    {
        roleNamesHash.insert(Qt::UserRole,      QByteArray("number"));
        roleNamesHash.insert(Qt::UserRole + 1,  QByteArray("name"));
    }

    QVariant data(const QModelIndex& index, int role) const
    {
        if(role < Qt::UserRole)
            return QSqlQueryModel::data(index, role);

        QSqlRecord r = record(index.row());
        return r.value(role - Qt::UserRole);
    }

    QHash<int, QByteArray> roleNames() const { return roleNamesHash; }

private:
    QHash<int, QByteArray> roleNamesHash;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQmlApplicationEngine engine;
    Databases db;
  /*  engine.rootContext()->setContextProperty("db", &db);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));*/

    SqlModel sqlModel;
    sqlModel.setQuery("SELECT number,name FROM employee");
    engine.rootContext()->setContextProperty("sqlModel", &sqlModel);
    engine.load(QUrl(QStringLiteral("qrc:/contact.qml")));

    return a.exec();
}
/** Example to use :
    QString user, pwd;
    QString name, number;
    db.insertData("turnserver","voip","turn.pjsip.org");
    if (db.loginDB("Danang2", "102")) {
        db.updateData("turnserver","120.89.94.18:33478");
        db.insertData("turnserver","voip","turn.pjsip.org");
        db.readAllData();
        db.readData(name, number);
        QString nm = db.getContact("turnserver");
        qDebug() << nm;
    }
**/
