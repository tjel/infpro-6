#include "prompt.h"

QString const Prompt::PROMPTSTRING = ">>> ";

void Prompt::startRead()
{
    QString message;
    QDateTime timestamp;

    QTextStream(stdout) << PROMPTSTRING;
    QTextStream(stdin) >> message;

    emit newMessage(message, timestamp.currentDateTime()); //wysyłka do displayu
    emit messageSent(); //zapętlenie samego siebie
}
