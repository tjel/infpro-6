#include "prompt.h"

QString const Prompt::PROMPTSTRING = "";

void Prompt::connection_start()
{
    socketOut = new QTcpSocket();

    connect(socketOut, SIGNAL(connected()),
      this, SLOT(startTransfer()));

    socketOut->connectToHost("89.74.93.135", 1337);
    socketOut->waitForConnected(3000);

}

void Prompt::startTransfer()
{
    qDebug() << "Connected!";
    qDebug() << socketOut->peerAddress();

    QTextStream cin(stdin);
     QString Qtext;
     Qtext = cin.readLine();
    socketOut->write(Qtext.toLatin1());
}

void Prompt::TransferError()
{
    qDebug() << socketOut->errorString();
}

//Teoretycznie lata tam sobie w tle, "wyciszany" na razie
void Prompt::startRead()
{
    QString message;
    QDateTime timestamp;

    QTextStream(stdout) << PROMPTSTRING;
    QTextStream(stdin) >> message;

   // socket->write("Hello, world", 13);
    emit messageSent(); //zapętlenie samego siebie
}
