#ifndef PROMPT_H
#define PROMPT_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDateTime>

class Prompt : public QObject
{
    Q_OBJECT

    static const QString PROMPTSTRING;

public slots:
    void startRead();

signals:
    void newMessage(QString, QDateTime);
    void messageSent();
};

#endif // PROMPT_H

