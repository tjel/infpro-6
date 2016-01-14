#include "prompt.h"

QString const Prompt::PROMPTSTRING = "";

void Prompt::connection_start()
{
    QTcpSocket *socketOut;
    socketOut = new QTcpSocket();
    socketOut->connectToHost("89.74.93.135", 1337);

    if(socketOut->waitForConnected(3000))
       {
           qDebug() << "Connected!";
           socketOut->write("hello server");
           while(true)
               {
               for(int asd=0;asd<1000000000;asd++)  //Prowizoryczny delay
               {

           }
               socketOut->write("hello server");  //Spamujemy server
               qDebug()<< socketOut->peerAddress()<< "  " << socketOut->read(5);
           }

       }
       else
       {
           qDebug() << "Not connected!";
       }
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
