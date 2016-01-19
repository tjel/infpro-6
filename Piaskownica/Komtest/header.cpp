

#include "header.h"
#include <QTextStream>


Server::Server(QObject* parent) //: QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
          this, SLOT(acceptConnection()));
  connect(client, SIGNAL(readyRead()),
          this, SLOT(startRead()));

  server.listen(QHostAddress::Any, 8888);
}

Server::~Server()
{
  server.close();
}

void Server::acceptConnection()
{
  client = server.nextPendingConnection();
}

void Server::startRead()
{
  char buffer[1024] = {0};

  client->read(buffer, client->bytesAvailable());
  qDebug() << buffer << endl;

  //emit donePrinting();
}


Client::Client(QObject* parent) //: QObject(parent)
{
  connect(&client, SIGNAL(connected()),
          this, SLOT(startTransfer()));
}

Client::~Client()
{
  client.close();
}

void Client::start(QString address, quint16 port)
{
  QHostAddress addr(address);
  client.connectToHost(addr, port);
}

void Client::startTransfer()
{
  QTextStream cin(stdin);
  QString Qtext;

  Qtext = cin.readLine();
  client.write(Qtext.toLatin1());
}
