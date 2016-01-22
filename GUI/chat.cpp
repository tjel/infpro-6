#include "chat.h"

ChatWindow::ChatWindow(ChatWidget* newWidget, QHostAddress address, QString addressString)
    : keyA(0),
      secretA(0),
      encryptionKey(0)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->socket = new QTcpSocket();
    this->recipient = address;
    this->recipientAddress = addressString;

    connect(this->socket, SIGNAL(connected()),
            this, SLOT(connectionEstablished()));
    connect(this->socket, SIGNAL(connected()),
            this, SLOT(keyExchange1()));

    toOutput("Connecting...");

    this->socket->connectToHost(address, 8888);
    if (!this->socket->waitForConnected(5000)) // zamula GUIa na 5 sekund :<
        connectionFailed();
    else
    {
        KeyPressFilter* keyPressFilter = new KeyPressFilter(this);
        this->widget->ui->msgInput->installEventFilter((keyPressFilter));

        connect(keyPressFilter, SIGNAL(enterPressed()),
                this->widget->ui->sendButton, SIGNAL(clicked()));
        connect(this->widget->ui->sendButton, SIGNAL(clicked()),
                this, SLOT(sendMessage()));
        connect(this->socket, SIGNAL(disconnected()),
                this, SLOT(connectionLost()));
        connect(this->socket, SIGNAL(readyRead()),
                this, SLOT(getMessage()));

        initUserLabels();
    }

}

ChatWindow::ChatWindow(ChatWidget* newWidget, QTcpSocket* socket, QHostAddress address, QString addressString)
    : keyA(0),
      secretA(0),
      encryptionKey(0)
{
    qsrand((uint)QTime::currentTime().msec());

    this->widget = newWidget;
    this->socket = socket;
    this->recipient = address;
    this->recipientAddress = addressString;

    KeyPressFilter* keyPressFilter = new KeyPressFilter(this);
    this->widget->ui->msgInput->installEventFilter((keyPressFilter));

    connect(keyPressFilter, SIGNAL(enterPressed()),
            this->widget->ui->sendButton, SIGNAL(clicked()));
    connect(this->socket, SIGNAL(readyRead()),
            this, SLOT(getMessage()));
    connect(this->widget->ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    connect(this->socket, SIGNAL(disconnected()),
            this, SLOT(connectionLost()));
    connect(this->socket, SIGNAL(connected()),
            this, SLOT(keyExchange1()));
    connect(this->socket, SIGNAL(connected()),
            this, SLOT(connectionEstablished()));

    keyExchange1();
    initUserLabels();
    enableInputWidgets();

    toOutput("Connected to " + recipientLabel + ".");
}

void ChatWindow::enableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(true);
    this->widget->ui->sendButton->blockSignals(false);
    this->widget->ui->connectionButton->setEnabled(true);
    this->widget->ui->connectionButton->blockSignals(false);
}

void ChatWindow::connectionEstablished()
{
    QString output = "Connection established.";

    toOutput(output);
    enableInputWidgets();
}

void ChatWindow::connectionFailed()
{
    QString output = "Connection failed.";

    toOutput(output);
    // Disconnect button -> Try Again button?
}

void ChatWindow::connectionLost()
{
    QString output = "Connection lost.";

    toOutput(output);
    disableInputWidgets();
    // Disconnect button -> Reconnect button?
}

void ChatWindow::toOutput(QString text)
{
    QString time = QDateTime::currentDateTime().toString(QString("hh:mm:ss"));

    this->widget->ui->msgOutput->setText( QString(
               this->widget->ui->msgOutput->toPlainText()
             + "{"
             + time
             + "} "
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
             + " | "
             + who
             + "]:\n"
             + what
             + "\n"));
}

void ChatWindow::saveMessage(QString sender, QString message)
{
    QString from, to;

    if (sender == "self")
    {
        from = "me";
        to = recipientAddress;
    }
    else
    {
        from = recipientAddress;
        to = "self";
    }

    emit toDatabase(from, message);
}

void ChatWindow::initUserLabels()
{
    this->selfLabel = QString("me");
    this->recipientLabel = this->recipientAddress;
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

    unsigned int base = 24611,
                 modulus = 44533, //Stale ktorych uzywamy do tworzenia kluczy. Wzialbym wieksze, ale nie mam kalkulatora ktory by liczyl eulera dla 6+ cyfrowych liczb bez zawieszania sie
                 random =  0;

    while (random == 0)
    {
        for (int i=0; i<qrand()%7; i++)
        // losujemy kilkukrotnie randomowa liczbe, bo qrand jest slaby i
        // jego pierwszy wynik jest zawsze zblizony do seeda
        {
            random=qrand();
        }
    }

    this->secretA = random;
    this->keyA = ((int)pow(base, random))%modulus;
    this->socket->write(QString::number(keyA).toUtf8());
}

void ChatWindow::keyExchange2(QString key)
{
    unsigned int modulus = 44533;
    unsigned int keyB = key.toInt();
    this->encryptionKey = ((int)pow(keyB, this->secretA))%modulus;

    //qDebug()<< this->encryptionKey;
}

QString ChatWindow::encriptior(QString message)
{
    QString messageOut = "";

    for(int i=0; i<message.length(); i++)
    {
        messageOut.append(message.at(i).unicode() + this->encryptionKey);
        qDebug()<<"Out: " << message.at(i).unicode() << " + " << this->encryptionKey << " = " << (message.at(i).unicode()+this->encryptionKey);
        //messageOut.append(message.at(i));
    }

    return messageOut;
}

QString ChatWindow::decriptior(QString message)
{
    QString messageIn = "";
    for(int i=0; i<message.length(); i++)
    {
        messageIn.append(message.at(i).unicode() - this->encryptionKey);
        //messageOut.append(message.at(i));
        qDebug()<<"In: " << message.at(i).unicode() << " - " << this->encryptionKey << " = " << (message.at(i).unicode()-this->encryptionKey);
    }

    return messageIn;
}

void ChatWindow::disableInputWidgets()
{
    this->widget->ui->sendButton->setEnabled(false);
    this->widget->ui->sendButton->blockSignals(true);
    this->widget->ui->connectionButton->setEnabled(false);
    this->widget->ui->connectionButton->blockSignals(true);
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
        saveMessage("self", message);
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
        saveMessage(recipientAddress, decryptedMessage);
    }
    else
    {
        keyExchange2(message);
    }
}

void ChatWindow::setSelfLabel(QString label)
{
    if (label.length())
        this->selfLabel = label;
}

void ChatWindow::setRecipientLabel(QString label)
{
    if (label.length())
        this->recipientLabel = label;
}

Chat::Chat(MainWindow* mw)
{
    this->gui = mw;
    this->db = new Database("../db.sqlite");

    KeyPressFilter* keyPressFilter = new KeyPressFilter(this);
    this->gui->ui->addressInput->installEventFilter(keyPressFilter);

    listener.listen(QHostAddress::Any, 8888);

    connect(keyPressFilter, SIGNAL(enterPressed()),
            this->gui->ui->connectButton, SIGNAL(clicked())); // totalna perwersja
    connect(&this->listener, SIGNAL(newConnection()),
            this, SLOT(handleIncomingConnection())); // obsługa przychodzacego requesta
    connect(this->gui->ui->connectButton, SIGNAL(clicked()),
            this, SLOT(checkAddress())); // przechwycenie adresu IP od GUI
    connect(this->gui->ui->historyButton, SIGNAL(clicked()),
            this->gui, SLOT(openHistory()));
}

void Chat::checkAddress()
{ 
    QString address = this->gui->ui->addressInput->text();

    if (address.length()) // and not already in use (and preferably is a proper IP address)
        addChatWindow(QHostAddress(address), cropAddress(address));
}

void Chat::addChatWindow(QHostAddress address, QString addressString)
{
    ChatWidget* newWidget = new ChatWidget(this->gui->ui->tabs);
    int id = this->gui->ui->tabs->addTab(newWidget, address.toString());

    //name = name.simplified();
    //if(name.compare(""))
    //{
    //    this->gui->ui->tabs->widget(this->gui->ui->tabs->count())->text="a"; // tso?!
    //}

    this->gui->ui->addressInput->clear();

    windows.insert(id, new ChatWindow(newWidget, address, addressString));
    this->gui->ui->tabs->setCurrentIndex(id);
}

void Chat::addChatWindow(QTcpSocket* socket, QHostAddress address, QString addressString)
{
    ChatWidget* newWidget = new ChatWidget(this->gui->ui->tabs);
    int id = this->gui->ui->tabs->addTab(newWidget, addressString);

    this->gui->ui->addressInput->clear();

    windows.insert(id, new ChatWindow(newWidget, socket, address, addressString));
}

void Chat::handleIncomingConnection()
{
    QTcpSocket* connection = this->listener.nextPendingConnection();
    QHostAddress address = connection->peerAddress();
    QString addressString = address.toString();

    // if address already in windows.addresses -> kill 'em all?
    //   (zakonczenie polaczenia nie zamyka taba, wiec moga sie zdublowac z jakims starym)

    // jakies okienko pyta o akceptacje
    // if ok
    addChatWindow(connection, address, cropAddress(addressString));
}

QString Chat::cropAddress(QString& address)
{
    QString HEAD = "::ffff:";

    if (address.startsWith(HEAD))
    {
       return address.split(HEAD)[1];
    }

    return address;
}

void Chat::toDatabase(QString from, QString to, QString message)
{
    QMap<QString,QString> shipment;
    shipment.insert("FROM", from);
    shipment.insert("TO", to);
    shipment.insert("DATETIME", "datetime(now)");
    shipment.insert("MESSAGE", message);

    db->insertInto("CHATHISTORY", &shipment);
}
