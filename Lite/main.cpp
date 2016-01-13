#include <QCoreApplication>
#include <QThread>
#include "prompt.h"
#include "display.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread* receivingThread = new QThread;
    QThread* printingThread = new QThread;

    Prompt* prompter = new Prompt();
    Display* displayer = new Display();

    prompter->moveToThread(receivingThread);
    displayer->moveToThread(printingThread);

    QObject::connect(receivingThread, SIGNAL(started()),
                     prompter, SLOT(startRead())); // prosimy o wiadomość
    QObject::connect(prompter, SIGNAL(newMessage(QString,QDateTime)),
                     displayer, SLOT(print(QString,QDateTime))); //wiadomość wyrusza w międzywątkową podróż
    QObject::connect(prompter, SIGNAL(messageSent()),
                     prompter, SLOT(startRead())); //zapętlenie promptu

    receivingThread->start();
    printingThread->start();

    return a.exec();
}

