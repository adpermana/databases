#ifndef DATABASES_H
#define DATABASES_H

#include <QtSql>
#include <QFile>
#include <QDebug>

class Databases : public QObject
{
    Q_OBJECT
public:
    explicit Databases(QObject *parent = 0);

signals:
    void dataFromCpp(QString dataCpp1, QString dataCpp2);

public slots:
    bool createConnection();
    bool loginDB(QString username, QString password);
    void insertData(QString name, QString contact, QString number);
    void updateData(QString name, QString numberChanged);
    void readAllData();
    void readData(QString name, QString number);
    QString getDataForRegister();
    QString getContact(QString name);

    void update(QString dataName1, QString dataName2);
    void read();

};

#endif // DATABASES_H
