#include "chatwindow.h"

ChatWindow::ChatWindow(int id, QHostAddress address)
{
    this->tabNumber = id;
    this->recipient = address;
}

ChatWindow::ChatWindow(int id, QTcpSocket* socket)
{
    this->tabNumber = id;
    this->readingSocket = socket;
}
