#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>
#include "thread_controls.h"
Thread_Controls::Thread_Controls(int ID, QObject *parent) :
    QThread(parent)
{
    this->Descriptor = ID;
}

void Thread_Controls::run()
{
    // thread starts here
    qDebug() << Descriptor << " Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->Descriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << Descriptor << " Client connected";

    // make this thread a loop
    exec();
}

void Thread_Controls::readyRead()
{
    QTime asd;
    QByteArray Data = socket->readAll();
    qDebug() << asd.currentTime() << "/n";
    qDebug() << Descriptor << " Data in: " << Data;

    socket->write(Data);
}

void Thread_Controls::disconnected()
{
    qDebug() << Descriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
