#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "mainwindow.h"
#include "chatwidget.h"
#include "ui_mainwindow.h"
#include "ui_chatwidget.h"

// Do zrobienia
// koordynacja nazwiazywania polaczen, usuwania ChatWindowsow
//    po usunięciu odpowiadajacych im tabow

class ChatWindow : public QObject
{
    Q_OBJECT

    ChatWidget* widget;
    QHostAddress recipient;
    QTcpSocket* readingSocket;
    QTcpSocket* sendingSocket;

    void connectSignals();

private slots:
    void sendMessage();
    void printMessage();

public:
    ChatWindow(ChatWidget*, QHostAddress); // przy nawiazywaniu polaczenia
    ChatWindow(ChatWidget*, QTcpSocket*); // przy akceptowaniu polaczenia
    void connectTo(QHostAddress);
};

class Chat : public QObject
{
    Q_OBJECT

    MainWindow* gui;
    QTcpServer listener;
    QMap<int, ChatWindow*> windows;

    void initSignals();
    void addChatWindow(QHostAddress); // przy nawiazywanu polaczen
    void addChatWindow(QTcpSocket*, QHostAddress); // przy akceptowaniu polaczen

public:
    Chat(MainWindow*);\

public slots:
    void incomingConnection();
    void checkAddress();
};

#endif // CHAT_H

