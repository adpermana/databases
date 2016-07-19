#include "databases.h"

Databases::Databases(QObject *parent) : QObject(parent)
{
    if(!createConnection())
        qDebug() << "error conn";
}

bool Databases::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QFile dbFile(QDir::toNativeSeparators(QDir::homePath()+"/Documents/workspace/hello-sql/test.sqlt"));
    qDebug() << QSqlDatabase::drivers();
    db.setHostName("localhost");
    db.setDatabaseName(dbFile.fileName());
    db.setUserName("root");
    db.setPassword("root");
    if (dbFile.open(QIODevice::ReadWrite)) {
        if (!db.open()) {
            qDebug() << "Databases error!!";
            return false;
        }
        return true;
    }
}

void Databases::insertData(QString name, QString contact, QString number)
{
    QSqlQuery query;
    QSqlQueryModel model;
    int id;
    QString numbers, names;
    query.exec("CREATE TABLE employee(id INTEGER PRIMARY KEY, "
               "name VARCHAR(20), contact VARCHAR(20), number VARCHAR(10))");
    model.setQuery("SELECT * FROM employee");
    id = model.rowCount();
    query.prepare("SELECT number,name FROM employee WHERE number = ? or name = ?");
    query.bindValue(0,number);
    query.bindValue(1,name);
    query.exec();
    if (query.next() || !number.isEmpty() || !name.isEmpty()) {
        numbers = query.value(0).toString();
        names = query.value(1).toString();
        if (numbers != number && names != name) {
            query.prepare("INSERT INTO employee (id, name, contact, number) "
                          "VALUES (:id, :name, :contact, :number)");
            query.addBindValue(id+1);
            query.addBindValue(name);
            query.addBindValue(contact);
            query.addBindValue(number);
            query.exec();
        }
    }
}

void Databases::updateData(QString name, QString numberChanged)
{
    QSqlQuery query;
    if (getContact(name) != "kosong") {
        query.prepare("UPDATE employee SET number = ? WHERE name = ?");
        query.bindValue(0, numberChanged);
        query.bindValue(1, name);
        query.exec();
    }
}

QString Databases::getContact(QString name)
{
    QSqlQuery query;
    query.prepare("SELECT name, number FROM employee WHERE name = ?");
    query.bindValue(0,name);
    query.exec();
    if (query.next()) {
        return query.value(1).toString();
    }
    return "kosong";
}

void Databases::update(QString dataName1, QString dataName2)
{
    updateData("test", dataName1);
    updateData("test2", dataName2);
}

void Databases::read()
{
    QString data = getContact("test");
    QString data2 = getContact("test2");
    emit dataFromCpp(data, data2);
}

void Databases::readAllData()
{
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM employee");
    for(int i=0; i<model.rowCount(); ++i){
        int id = model.record(i).value("id").toInt();
        QString tempName = model.record(i).value("name").toString();
        QString tempNumber = model.record(i).value("number").toString();
        QString tempContact = model.record(i).value("contact").toString();
        qDebug() << id << tempName << tempContact << tempNumber;
    }
}

void Databases::readData(QString name, QString number)
{
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM employee");
    name = model.record(0).value("name").toString();
    number = model.record(0).value("number").toString();
}

bool Databases::loginDB(QString username, QString password)
{
    QSqlQuery query;
    QString userDB, passDB;
    query.prepare("SELECT name,number FROM employee WHERE name = ? or number = ?");
    query.bindValue(0,username);
    query.bindValue(1,password);
    query.exec();
    if (query.next() && !username.isEmpty() && !password.isEmpty()) {
        userDB = query.value(0).toString();
        passDB = query.value(1).toString();
        if (username == userDB && passDB == password) {
            return true;
        }
        return false;

    }
}

QString Databases::getDataForRegister()
{
    QSqlQuery query;
    query.prepare("SELECT name,number FROM employee WHERE id = 1");
    query.exec();
    query.next();
    return query.value(0).toString(), query.value(1).toString();
}
