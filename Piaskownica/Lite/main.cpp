#include <QCoreApplication>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "prompt.h"
#include "display.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* clientThread = new QThread;
    QThread* serverThread = new QThread;

    Display* displayer = new Display();
    Prompt* prompter = new Prompt();

    prompter->moveToThread(clientThread);
    displayer->moveToThread(serverThread);

    QObject::connect(serverThread, SIGNAL(started()),
                     displayer, SLOT(server_start())); // uruchamiamy nasluch
    QObject::connect(clientThread, SIGNAL(started()),
                     prompter, SLOT(connection_start())); // laczymy sie
    QObject::connect(serverThread, SIGNAL(started()),
                     prompter, SLOT(startRead())); // prosimy o wiadomość

   // QObject::connect(prompter, SIGNAL(started()),
   //                 displayer, SLOT(print(QDateTime)));





    QObject::connect(prompter, SIGNAL(messageSent()),
                     prompter, SLOT(startRead())); //zapętlenie promptu

    serverThread->start();
    clientThread->start();

    return a.exec();
}

