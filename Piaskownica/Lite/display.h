#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class Display : public QObject
{
    Q_OBJECT

    static const QString DATETIMEFORMAT;

public slots:
    void server_start();
    void print(QDateTime);
    void newConnection();
    void read_msg();

signals:
    void newMessage(QDateTime);
    void messageSent();

private:
    QTcpServer* server;
    QTcpSocket* socket;

};

#endif // DISPLAY_H

