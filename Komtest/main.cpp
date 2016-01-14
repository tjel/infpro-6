/*#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>
#include <cstring>
#include <QTextStream>
#include "server_controls.h"

int main(int argc, char *argv[])
{
    QTextStream cin(stdin); */

    /*QCoreApplication a(argc, argv);

    Server_Controls Server;
    Server.StartServer();

    QTcpSocket *socket;
    socket = new QTcpSocket();
    socket->connectToHost("155.158.101.35", 1337);
    QString Qtext;
    socket->write("aaa");
    socket->write("aak");
    socket->write("aae");
    if(socket->waitForConnected(3000))
       {
           qDebug() << "Connected!";
           while(!Qtext.contains("aoe"))
           {
           Qtext = cin.readLine();
           socket->write(Qtext.toLatin1());
           }
           socket->close();
       }
       else
       {
           qDebug() << "Not connected!";
       }

    return a.exec();
}*/




  /* QCoreApplication a(argc, argv);
    QTcpSocket *socket;
    socket = new QTcpSocket();
    QTcpServer *server;
    server = new QTcpServer();

    spox_socket = new QTcpSocket(); // nowy sokiet lel


    if(!server->listen(QHostAddress::Any, 1337))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
    }

    socket->connectToHost("155.158.101.35", 1337);
    if(socket->waitForConnected(3000))
       {
           spox_socket = server->nextPendingConnection();

           connect(spox_socket, SIGNAL(readyRead()),
               this, SLOT(startRead()));

           qDebug() << "Connected!";

           // send
           socket->write("hello server\r\n\r\n\r\n\r\n");


           //socket->waitForBytesWritten(1000);
           //socket->waitForReadyRead(3000);
           qDebug() << "Reading: " << socket->bytesAvailable();

           qDebug() << socket->readAll();

        qDebug() << "connected!";
           socket->close();
       }
       else
       {
           qDebug() << "Not connected!";
       }
    return a.exec();
} */


#include <QCoreApplication>
#include "header.cpp"


int main (int argc, char** argv)
{
    QCoreApplication app(argc, argv);

  Server server;
  Client client;

  client.start("192.168.0.13", 8888);

  return app.exec();
}
