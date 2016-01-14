#include <QCoreApplication>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include "prompt.h"
#include "display.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* receivingThread = new QThread;
    QThread* printingThread = new QThread;

    Display* displayer = new Display();
    Prompt* prompter = new Prompt();

    prompter->moveToThread(receivingThread);
    displayer->moveToThread(printingThread);

    QObject::connect(printingThread, SIGNAL(started()),
                     displayer, SLOT(server_start())); // uruchamiamy nasluch
    QObject::connect(receivingThread, SIGNAL(started()),
                     prompter, SLOT(connection_start())); // laczymy sie
    QObject::connect(receivingThread, SIGNAL(started()),
                     prompter, SLOT(startRead())); // prosimy o wiadomość

    QObject::connect(prompter, SIGNAL(started()),
                    displayer, SLOT(print(QDateTime)));





    QObject::connect(prompter, SIGNAL(messageSent()),
                     prompter, SLOT(startRead())); //zapętlenie promptu

    receivingThread->start();
    printingThread->start();

    return a.exec();
}

