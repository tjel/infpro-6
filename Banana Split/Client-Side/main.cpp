#include <QCoreApplication>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* clientThread = new QThread;
    Prompt* prompter = new Prompt();

    prompter->moveToThread(clientThread);

    QObject::connect(clientThread, SIGNAL(started()),
                     prompter, SLOT(connection_start())); // laczymy sie

    clientThread->start();

    return a.exec();
}

