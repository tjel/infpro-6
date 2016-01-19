#include <QCoreApplication>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* serverThread = new QThread;

    Display* displayer = new Display();

    displayer->moveToThread(serverThread);

    QObject::connect(serverThread, SIGNAL(started()),
                     displayer, SLOT(server_start())); // uruchamiamy nasluch


    serverThread->start();

    return a.exec();
}
