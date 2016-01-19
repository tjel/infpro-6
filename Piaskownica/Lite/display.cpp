#include "display.h"
#include <QTcpSocket>
#include <QTcpServer>


QString const Display::DATETIMEFORMAT = "dd.MM.yyyy hh:mm:ss";

void Display::server_start()
{
    //Uruchamiamy server
    server = new QTcpServer();
    connect(server, SIGNAL(newConnection()),
                this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any,1337))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void Display::newConnection()
{
    qDebug() << "Woot woot actually connected";
    qDebug() << "lol jk m8 nothing works at all";
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()),
    this, SLOT(read_msg()));
}


//Tymczasowo nie istnieje
void Display::print(QDateTime datetime)
{

    char buffer[1024] = {0};
    //socket->read(buffer, socket->bytesAvailable());
    socket->write("oaea");
    while(true)
    {
       //if(socket->bytesAvailable()>0)
       {
        QTextStream(stdout) << "["
                            << datetime.toString(DATETIMEFORMAT)
                            << "] "
                            << buffer
                            << "\n";
       }
    }
}

void Display::read_msg()
{
     qDebug()<< socket->peerAddress()<< "  " << socket->read(socket->bytesAvailable());
}
