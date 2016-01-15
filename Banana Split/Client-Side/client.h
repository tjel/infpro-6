#ifndef CLIENT_H
#define CLIENT_H

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
    void startTransfer();
    void TransferError();

signals:
    void newMessage(QDateTime);
    void messageSent();

private:
    QTcpSocket* socketOut;

};

#endif // PROMPT_H
