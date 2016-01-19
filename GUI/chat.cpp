#include "chat.h"

ChatWindow::ChatWindow(ChatWidget* newWidget, QHostAddress address)
{
    this->widget = newWidget;
    this->recipient = address;
    this->sendingSocket = new QTcpSocket();

    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->sendingSocket, SIGNAL(connected()),
            this->widget->ui->msgInput, SLOT(setEnabled(bool)));

    //connectSignals();
}

ChatWindow::ChatWindow(ChatWidget* newWidget, QTcpSocket* socket)
{
    this->widget = newWidget;
    this->readingSocket = socket;
    this->sendingSocket = new QTcpSocket();

    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->readingSocket, SIGNAL(readyRead()),
            this, SLOT(printMessage()));
    connect(this->sendingSocket, SIGNAL(connected()),
            this->widget->ui->msgInput, SLOT(setEnabled(bool)));

   // connectSignals();
}

void ChatWindow::connectSignals()
{
    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->readingSocket, SIGNAL(readyRead()),
            this, SLOT(printMessage()));
    connect(this->sendingSocket, SIGNAL(connected()),
            this->widget->ui->msgInput, SLOT(setEnabled(bool)));
}

void ChatWindow::connectTo(QHostAddress address)
{
    this->sendingSocket->connectToHost(address, 8888);
}

void ChatWindow::sendMessage()
{
    QString message = this->widget->ui->msgInput->toPlainText();

    this->sendingSocket->write(message.toUtf8());
}

void ChatWindow::printMessage()
{
    QString message = this->readingSocket->read(2000);

    this->widget->ui->msgOutput->setText(message);
}

Chat::Chat(MainWindow* mw)
{
    this->gui = mw;

    listener.listen(QHostAddress::Any, 8888);

    connect(&this->listener, SIGNAL(newConnection()),
            this, SLOT(incomingConnection())); // obsługa przychodzacego requesta
    connect(this->gui->ui->connectButton, SIGNAL(clicked()),
            this, SLOT(checkAddress())); // przechwycenie adresu IP od GUI
}

void Chat::checkAddress()
{
    QString text = this->gui->ui->addressInput->toPlainText();
    // if text not already in chatWindows.addresses (and preferably is a proper IP address)
    // zaczynamy procedure laczenia...

    addChatWindow(QHostAddress(text));
}

void Chat::addChatWindow(QHostAddress address)
{
    // ...konstruujac nowy ChatWindow, podajac id nowego taba interfejsu i adres odbiorcy

    ChatWidget* newWidget = new ChatWidget();
    int id = this->gui->ui->tabs->addTab(newWidget, address.toString());

    windows.insert(id, new ChatWindow(newWidget, QHostAddress(address)));
    // napisac jakas funkcje GUIa, ktora przelacza go na ten nowy tab
    // i ja tu trzasnac

    this->windows[id]->connectTo(address);
}

void Chat::addChatWindow(QTcpSocket* socket, QHostAddress address)
{
    ChatWidget* newWidget = new ChatWidget();
    int id = this->gui->ui->tabs->addTab(newWidget, address.toString());

    windows.insert(id, new ChatWindow(newWidget, socket));
}

void Chat::incomingConnection()
{
    QTcpSocket* connection = this->listener.nextPendingConnection();
    QHostAddress address = connection->peerAddress();

    // if address already in windows.addresses -> kill 'em all?
    //   (zakonczenie polaczenia nie zamyka taba, wiec moga sie zdublowac z jakims starym)

    // jakies okienko pyta o akceptacje
    // if ok
    addChatWindow(connection, address);
}
