#include "chat.h"

ChatWindow::ChatWindow(ChatWidget* newWidget, QHostAddress address)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->recipient = address;
    this->socket = new QTcpSocket();

    this->socket->connectToHost(address, 8888);

    connectSignals();
}

ChatWindow::ChatWindow(ChatWidget* newWidget, QTcpSocket* socket)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->socket = socket;
    this->recipient = this->socket->peerAddress();

    connectSignals();
    enableInputWidgets();
}

void ChatWindow::connectSignals()
{
    //connect(this->widget->ui->nameInput, SIGNAL(textChanged(QString)), //Zmienianie imiena, zeby bylo czytelniej
    //        this, SLOT(changeName()));                                   //Na razie zescrapowane
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
    this->keyExchange1(); //zanim cokolwiek zrobimy, wymieniamy klucze szyfrowania
    this->widget->ui->sendButton->setEnabled(true);
    this->widget->ui->disconnectButton->setEnabled(true);
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
    QString messageOut = "";
    if (message.length())
    {
        messageOut=encriptior(message);
        this->socket->write(messageOut.toUtf8());

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

    if(this->encryptionKey!=0)
    {
        message = decriptior(message);
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
    else
    {
        keyExchange2(message);
    }
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
