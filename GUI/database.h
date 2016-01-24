#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include <QString>
#include <QException>

class Database : public QObject
{
    Q_OBJECT

    QString dbPath;
    QSqlDatabase db;

public:
    Database(QString);
    ~Database();
    bool open();
    void close();
    bool createTable(QString, QMap<QString, QString>*);
    bool insertInto(QString, QMap<QString, QString>*);
    QSqlQuery selectMessages(QString,QString order="");
    QSqlQuery select(QString);
};

#endif // DATABASE_H

