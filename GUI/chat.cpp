#include "chat.h"

ChatWindow::ChatWindow(ChatWidget* newWidget, QHostAddress address)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->recipient = address;
    this->socket = new QTcpSocket();
    this->keyA = this->secretA = this->encryptionKey = 0;

    connect(this->socket, SIGNAL(connected()),
            this, SLOT(connectionEstablished()));

    toOutput("Connecting...");

    this->socket->connectToHost(address, 8888);
    if (!this->socket->waitForConnected(5000)) // zamula GUIa, choć nie powinien
        connectionFailed();
    else
    {
        this->keyExchange1();

        connect(this->widget->ui->sendButton, SIGNAL(clicked()),
                this, SLOT(sendMessage()));
        connect(this->socket, SIGNAL(disconnected()),
                this, SLOT(connectionLost()));
        connect(this->socket, SIGNAL(readyRead()),
                this, SLOT(getMessage()));

        initUserLabels();
    }

}

ChatWindow::ChatWindow(ChatWidget* newWidget, QTcpSocket* socket)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->socket = socket;
    this->recipient = this->socket->peerAddress();
    this->keyA = this->secretA = this->encryptionKey = 0;

    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->socket, SIGNAL(disconnected()),
            this, SLOT(connectionLost()));
    connect(this->socket, SIGNAL(connected()),
            this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(readyRead()),
            this, SLOT(getMessage()));

    initUserLabels();
    enableInputWidgets();
}

void ChatWindow::enableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(true);
    this->widget->ui->disconnectButton->setEnabled(true);
}

void ChatWindow::connectionEstablished()
{
    QString output = "Connection established.";

    toOutput(output);
    enableInputWidgets();
}

void ChatWindow::connectionFailed()
{
    QString output = "Connection failed. You may want to rethink your life and/or try again.";

    toOutput(output);
    // input widgets still disabled so chill
    // Disconnect button -> Try Again button?
}

void ChatWindow::connectionLost()
{
    QString output = "Connection lost. Lord knows if there are any means of solving this right now.";

    toOutput(output);
    disableInputWidgets();
    // Disconnect button -> Reconnect button?
}

void ChatWindow::toOutput(QString text)
{
    /* do ogólnowojskowych komunikatów */

    this->widget->ui->msgOutput->setText( QString(
               this->widget->ui->msgOutput->toPlainText()
             + text
             + "\n"));
}

void ChatWindow::toOutput(QString who, QString what)
{
    QString time = QDateTime::currentDateTime().toString(QString("hh:mm:ss"));

    this->widget->ui->msgOutput->setText( QString(
               this->widget->ui->msgOutput->toPlainText()
             + "["
             + time
             + ", "
             + who
             + "]: "
             + what
             + "\n"));
}

void ChatWindow::initUserLabels()
{
    this->selfLabel = QString("me");
    this->recipientLabel = this->recipient.toString();
}

/*void ChatWindow::keyExchange1()
{
    while(this->encryptionKey==-1) //Placeholderowy publiczny key exchange
    {
        this->encryptionKey=qrand();
    }
    this->socket->write(QString::number(encryptionKey).toUtf8());
}

void ChatWindow::keyExchange2(QString key)
{
    this->decryptionKey=key.toInt();
}
*/

void ChatWindow::keyExchange1()
{

    unsigned int base = 24611, modulus = 44533; //Stale ktorych uzywamy do tworzenia kluczy. Wzialbym wieksze, ale nie mam kalkulatora ktory by liczyl eulera dla 6+ cyfrowych liczb bez zawieszania sie
    unsigned int random =  0;
    while(random==0)
    {
        for(int i=0;i<qrand()%7;i++)//losujemy kilkukrotnie randomowa liczbe, bo qrand jest slaby i jego pierwszy wynik jest zawsze zblizony do seeda
        {
        random=qrand();
        }
    }
    this->secretA=random;
    this->keyA=(base^random)%modulus;
    this->socket->write(QString::number(keyA).toUtf8());
}

void ChatWindow::keyExchange2(QString key)
{
    unsigned int base = 24611, modulus = 44533;
    unsigned int keyB=key.toInt();
    this->encryptionKey = (keyB^this->secretA)%modulus;
    qDebug()<< this->encryptionKey;

}

QString ChatWindow::encriptior(QString message)
{
    QString messageOut="";
    for(int i=0;i<message.length();i++)
    {
        messageOut.append(message.at(i).unicode()+this->encryptionKey);
        qDebug()<<"Out: " << message.at(i).unicode() << " + " << this->encryptionKey << " = " << (message.at(i).unicode()+this->encryptionKey);
        //messageOut.append(message.at(i));
    }
    return messageOut;
}

QString ChatWindow::decriptior(QString message)
{
    QString messageIn="";
    for(int i=0;i<message.length();i++)
    {
        messageIn.append(message.at(i).unicode()-this->encryptionKey);
        //messageOut.append(message.at(i));
        qDebug()<<"In: " << message.at(i).unicode() << " - " << this->encryptionKey << " = " << (message.at(i).unicode()-this->encryptionKey);
    }
    return messageIn;
}

void ChatWindow::disableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(false);
    this->widget->ui->disconnectButton->setEnabled(false);
}

void ChatWindow::sendMessage()
{
    QString message = this->widget->ui->msgInput->toPlainText();
    QString encryptedMessage;

    if (message.length())
    {
        encryptedMessage = encriptior(message);

        this->socket->write(encryptedMessage.toUtf8());
        this->widget->ui->msgInput->clear();

        // co jeśli nie dojdzie? :<
        toOutput(this->selfLabel, message);
    }
}

void ChatWindow::getMessage()
{
    QString message = this->socket->read(2000); // jakiś globalny MAXSIZE?
    QString decryptedMessage;

    if (this->encryptionKey != 0)
    {
        decryptedMessage = decriptior(message);

        toOutput(this->recipientLabel, decryptedMessage);
    }
    else
    {
        keyExchange2(message);
    }
}

void ChatWindow::setSelfLabel(QString label)
{
    // if not something terrible
    this->selfLabel = label;
    // else toOutput("Not gonna happen");
}

void ChatWindow::setRecipientLabel(QString label)
{
    // if kosher
    this->recipientLabel = label;
    // else toOutput("Yer mum");
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
    QString adress = this->gui->ui->addressInput->text();
    // if text not already in chatWindows.addresses (and preferably is a proper IP address)
    // zaczynamy procedure laczenia...

    addChatWindow(QHostAddress(adress));
}

void Chat::addChatWindow(QHostAddress address)
{
    // ...konstruujac nowy ChatWindow, podajac id nowego taba interfejsu i adres odbiorcy

    ChatWidget* newWidget = new ChatWidget();
    int id = this->gui->ui->tabs->addTab(newWidget, address.toString());
    //name = name.simplified();
    //if(name.compare(""))
    //{
    //    this->gui->ui->tabs->widget(this->gui->ui->tabs->count())->text="a";
    //}

    windows.insert(id, new ChatWindow(newWidget, QHostAddress(address)));
    this->gui->ui->tabs->setCurrentIndex(id);
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
