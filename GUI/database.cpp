#include "database.h"

Database::Database(QString path)
{
    this->dbPath = path;
    this->db = QSqlDatabase::addDatabase("QSQLITE");

    bool exists = QFile::exists(dbPath);

    db.setDatabaseName(dbPath);

    if (!exists)
    {
        open();

        QMap<QString,QString> columns;
        columns.insert("Sender", "TEXT");
        columns.insert("Receiver", "TEXT");
        columns.insert("DateTime", "TEXT");
        columns.insert("Message", "TEXT");

        createTable("CHATHISTORY", &columns);

        close();
    }
}

Database::~Database()
{
    this->close();
}

bool Database::open()
{
    return this->db.open();
}

void Database::close()
{
    this->db.close();
}

bool Database::createTable(QString name, QMap<QString,QString>* columns)
{
    QSqlQuery query(db);

    QString cmd = "CREATE TABLE "
                + name + " (";
           foreach (QString key, columns->keys())
               cmd += key + " " + columns->value(key) + ", ";
            cmd.chop(2);
            cmd += ");";

    qDebug() << cmd;
    query.exec(cmd);
    qDebug()<< query.lastError();

    return db.commit();
}

bool Database::insertInto(QString name, QMap<QString,QString>* columns)
{
    QSqlQuery query(db);

    QString cmd = "INSERT INTO "
                + name + " (DateTime, ";
          foreach (QString key, columns->keys())
              cmd += key + ", ";
           cmd.chop(2);
           cmd += ") VALUES (datetime('now','localtime'), ";
          foreach (QString key, columns->keys())
              cmd += ":" + key + ", ";
           cmd.chop(2);
           cmd += ");";

           qDebug() << cmd;

           query.prepare(cmd);

           foreach (QString key, columns->keys())
           {
                   query.bindValue(":"+key, columns->value(key));
                   qDebug() << key << columns->values(key);
           }

    qDebug() << "insert: " << query.exec() << query.lastError();

    return db.commit();
}

QSqlQuery Database::selectMessages(QString address, QString order)
{
    QSqlQuery query(db);

    QString cmd = "SELECT DateTime, Sender, Message FROM CHATHISTORY "
                  "WHERE (Sender = :Address OR Receiver = :Address) "
                  "ORDER BY datetime(DateTime)";
              if (order != "")
                  cmd += " " + order;
            cmd += ";";

    query.prepare(cmd);
    query.bindValue(":Address", address);

    qDebug() << "Select: " << query.exec() << query.lastError();

    return query;
}

QSqlQuery Database::select(QString cmd)
{
    QSqlQuery query;

    query.exec(cmd);

    return query;
}
