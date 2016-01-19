#include "chat.h"

ChatWindow::ChatWindow(ChatWidget* newWidget, QHostAddress address)
{
    this->widget = newWidget;
    this->recipient = address;
    this->socket = new QTcpSocket();

    this->socket->connectToHost(address, 8888);

    connectSignals();
}

ChatWindow::ChatWindow(ChatWidget* newWidget, QTcpSocket* socket)
{
    this->widget = newWidget;
    this->socket = socket;
    this->recipient = this->socket->peerAddress();

    connectSignals();
    enableInputWidgets();
}

void ChatWindow::connectSignals()
{
    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->socket, SIGNAL(disconnected()),
            this, SLOT(disableInputWidgets()));
    connect(this->socket, SIGNAL(connected()),
            this, SLOT(enableInputWidgets()));
    connect(this->socket, SIGNAL(readyRead()),
            this, SLOT(getMessage()));
}

void ChatWindow::enableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(true);
    this->widget->ui->disconnectButton->setEnabled(true);
}

void ChatWindow::disableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(false);
    this->widget->ui->disconnectButton->setEnabled(false);
}

void ChatWindow::sendMessage()
{
    QString message = this->widget->ui->msgInput->toPlainText();

    if (message.length())
    {
        this->socket->write(message.toUtf8());

        this->widget->ui->msgInput->clear();

        // co jeśli nie dojdzie? :<

        QString date = QDate::currentDate().toString();
        QString time = QTime::currentTime().toString();

        this->widget->ui->msgOutput->setText(QString(
                   this->widget->ui->msgOutput->toPlainText()
                 + "["
                 + time
                 + ", ja]: "
                 + message
                 + "\n"));
    }
}

// przydałaby się do wyświetlania wspólna funkcja typu toOutput(kto,co), która wyłuskuje już na miejscu datę/czas

void ChatWindow::getMessage()
{
    QString message = this->socket->read(2000); // jakiś globalny MAXSIZE?

    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();

    this->widget->ui->msgOutput->setText(QString(
                this->widget->ui->msgOutput->toPlainText()
              + "["
              + time
              + ", "
              + this->recipient.toString() // nieładnie za każdym razem go stringować, trzeba by to już mieć na miejscu
              + "]: "
              + message
              + "\n"));
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
    QString text = this->gui->ui->addressInput->text();
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
    // GUI przełącza się na nowy tab
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
