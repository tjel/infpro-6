#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QApplication>
#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

class ChatWindow : public QObject
{
    Q_OBJECT

    QHostAddress recipient;
    int tabNumber;
    QTcpSocket* readingSocket;
    QTcpSocket sendingSocket;

public:
    ChatWindow(int, QHostAddress); // przy nawiazywaniu polaczenia
    ChatWindow(int, QTcpSocket*); // przy akceptowaniu polaczenia
};



#endif // CHATWINDOW_H

