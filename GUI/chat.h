#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "database.h"
#include "eventfilter.h"
#include "chathistory.h"
#include "mainwindow.h"
#include "chatwidget.h"
#include "ui_mainwindow.h"
#include "ui_chatwidget.h"

class ChatWindow : public QObject
{
    Q_OBJECT

    ChatWidget* widget;
    QTcpSocket* socket;
    QHostAddress recipient;
    QString selfLabel;
    QString recipientLabel;
    QString recipientAddress;
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
    void setSelfLabel(QString);
    void setRecipientLabel(QString);
    void saveMessage(QString, QString);
    void disconnect();

signals:
    void toDatabase(QString, QString, QString);

public:
    ChatWindow(ChatWidget*, QHostAddress, QString); // przy nawiazywaniu polaczenia
    ChatWindow(ChatWidget*, QTcpSocket*, QHostAddress, QString); // przy akceptowaniu polaczenia
};

class Chat : public QObject
{
    Q_OBJECT
    friend class ChatHistory;

    MainWindow* gui;
    QTcpServer listener;
    Database* db;
    QMap<int, ChatWindow*> windows;
    ChatHistory* history;

    //void initSignals();
    void addChatWindow(QHostAddress, QString); // przy nawiazywanu polaczen
    void addChatWindow(QTcpSocket*, QHostAddress, QString); // przy akceptowaniu polaczen

public:
    Chat(MainWindow*);
    ~Chat();
    static QString cropAddress(QString&);

public slots:
    void handleIncomingConnection();
    void checkAddress();
    void toDatabase(QString, QString, QString);
    void openHistory();
};

#endif // CHAT_H

