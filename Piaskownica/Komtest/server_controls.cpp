
#include "server_controls.h"

Server_Controls::Server_Controls(QObject *parent) :
    QTcpServer(parent)
{
}

void Server_Controls::StartServer()
{
    if(!this->listen(QHostAddress::Any,1337))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void Server_Controls::incomingConnection(int Descriptor)
{
    qDebug() << Descriptor << " Connecting...";

    Thread_Controls *thread = new Thread_Controls(Descriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

