#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

class Server : public QObject
{
    Q_OBJECT

    QTcpServer listener;

    void start();
};

#endif // TCPLISTENER_H

