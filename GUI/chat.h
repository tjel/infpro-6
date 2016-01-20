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

class ChatWindow : public QObject
{
    Q_OBJECT
    friend class ChatSync;

    ChatWidget* widget;
    QHostAddress recipient;
    QTcpSocket* socket;
    QString selfLabel;
    QString recipientLabel;
    unsigned int secretA;
    unsigned int keyA;
    unsigned int encryptionKey;

    void toOutput(QString); // do ogólnowojskowych komunikatów
    void toOutput(QString, QString); // do wyświetlania wiadomości
    void initUserLabels(); // domyślne aliasy

private slots:
    void sendMessage();
    void getMessage();
    void keyExchange1();
    void keyExchange2(QString);
    QString encriptior(QString);
    QString decriptior(QString);
    void disableInputWidgets();
    void enableInputWidgets();
    void connectionEstablished();
    void connectionFailed();
    void connectionLost();
    void setSelfLabel(QString); // na razie nie używane
    void setRecipientLabel(QString);

public:
    ChatWindow(ChatWidget*, QHostAddress); // przy nawiazywaniu polaczenia
    ChatWindow(ChatWidget*, QTcpSocket*); // przy akceptowaniu polaczenia
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
    Chat(MainWindow*);

public slots:
    void incomingConnection();
    void checkAddress();
};

#endif // CHAT_H

