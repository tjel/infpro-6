#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>
#include <cstring>
#include <QTextStream>
#include "server_controls.h"

int main(int argc, char *argv[])
{
    QTextStream cin(stdin);

    QCoreApplication a(argc, argv);

    Server_Controls Server;
    Server.StartServer();

    QTcpSocket *socket;
    socket = new QTcpSocket();
    socket->connectToHost("89.74.93.135", 1337);
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
}




 /*   QCoreApplication a(argc, argv);
    std::cout<<"asd";
    QTcpSocket *socket;
    socket = new QTcpSocket();
    QTcpServer *server;
    server = new QTcpServer();

    if(!server->listen(QHostAddress::Any, 1337))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
    }

    socket->connectToHost("89.74.93.135", 1337);
    if(socket->waitForConnected(3000))
       {
           qDebug() << "Connected!";

           // send
           socket->write("hello server\r\n\r\n\r\n\r\n");
           socket->waitForBytesWritten(1000);
           socket->waitForReadyRead(3000);
           qDebug() << "Reading: " << socket->bytesAvailable();

           qDebug() << socket->readAll();

        qDebug() << "connected!";
           socket->close();
       }
       else
       {
           qDebug() << "Not connected!";
       }
    return a.exec();*/


