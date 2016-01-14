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
    QTcpSocket *socket = server->nextPendingConnection();
    while(true)
        {
        for(int asd=0;asd<1000000000;asd++)  //Prowizoryczny delay
        {
    }
        socket->write("hello client"); //Spamujemy klienta
        qDebug()<< socket->peerAddress()<< "  " << socket->read(5);
    }
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
