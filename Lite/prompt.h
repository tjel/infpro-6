#ifndef PROMPT_H
#define PROMPT_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class Prompt : public QObject
{
    Q_OBJECT

    static const QString PROMPTSTRING;

public slots:
    void connection_start();
    void startRead();

signals:
    void newMessage(QDateTime);
    void messageSent();

private:
    QTcpSocket* socketOut;

};

#endif // PROMPT_H

