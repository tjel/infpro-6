#ifndef HEADER_H
#define HEADER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <QHostAddress>
#include <QString>
#include <QDebug>


class Server : public QObject
{
    Q_OBJECT

public:
  Server(QObject * parent = 0);
  ~Server();

public slots:
  void acceptConnection();
  void startRead();

private:
  QTcpServer server;
  QTcpSocket* client;

signals:
  void donePrinting();
};


class Client : public QObject
{
    Q_OBJECT

public:
  Client(QObject* parent = 0);
  ~Client();
  void start(QString address, quint16 port);

public slots:
  void startTransfer();

private:
  QTcpSocket client;
};

#endif // HEADER_H

