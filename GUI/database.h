#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QDebug>
#include <QString>

class Database : public QObject
{
    Q_OBJECT

    QString dbPath;
    QSqlDatabase db;

public:
    Database(QString);
    ~Database();
    bool open();
    bool createTable(QString, QMap<QString, QString>*);
    bool insertInto(QString, QMap<QString, QString>*);
};

#endif // DATABASE_H

