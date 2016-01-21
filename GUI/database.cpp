#include "database.h"

Database::Database(QString path)
{
    this->dbPath = path;
    this->db = QSqlDatabase::addDatabase("QSQLITE");

    bool existed;
    if (!QFile::exists(dbPath)) existed = false;

    db.setDatabaseName(dbPath);

    if (!existed)
    {
        QMap<QString,QString> columns;
        columns.insert("From", "TEXT");
        columns.insert("DateTime", "TEXT");
        columns.insert("Message", "TEXT");

        createTable("CHATHISTORY", &columns);
    }
}

Database::~Database()
{
    this->db.close();
}

bool Database::open()
{
    return this->db.open();
}

bool Database::createTable(QString name, QMap<QString,QString>* columns)
{
    QString cmd = "CREATE TABLE "
                + name + " (";
           foreach (QString key, columns->keys())
               cmd += key + " " + columns->value(key) + ", ";
            cmd.chop(2);  // urżnięcie ostatniego przecinka
            cmd += ");";

            qDebug() << cmd;

    QSqlQuery query = db.exec(cmd);

            qDebug()<< query.lastError();

    return db.commit();
}

bool Database::insertInto(QString name, QMap<QString,QString>* columns)
{
    QString cmd = "INSERT INTO "
                + name + " (";
          foreach (QString key, columns->keys())
              cmd += key + ", ";
           cmd.chop(2);
           cmd += ") VALUES (";
          foreach (QString key, columns->keys())
              cmd += columns->value(key) + ", ";
           cmd.chop(2);
           cmd += ");";

           qDebug() << cmd;

    QSqlQuery query = db.exec(cmd);

    return db.commit();
}
