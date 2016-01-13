#include "display.h"

QString const Display::DATETIMEFORMAT = "dd.MM.yyyy hh:mm:ss";

void Display::print(QString message, QDateTime datetime)
{
    QTextStream(stdout) << "["
                        << datetime.toString(DATETIMEFORMAT)
                        << "] "
                        << message
                        << "\n";
}
