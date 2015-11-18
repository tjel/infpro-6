
#include "Server_Controls.h"

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

void Server_Controls::incomingConnection(int Descriptior)
{
    qDebug() << Descriptior << " Connecting...";

    Thread_Controls *thread = new Thread_Controls(Descriptior, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

