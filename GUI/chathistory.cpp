#include "chathistory.h"

ChatHistory::ChatHistory(Database* db)
{
    this->db = db;
    this->window = new ArchiveWindow(this);
    this->cache = new QMap<QString,QString>();

    connect(window->ui->list, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(populateBrowser(QListWidgetItem*,QListWidgetItem*)));

    window->show();

    prepareList();
}

ChatHistory::~ChatHistory()
{
    window->close(); // to nie wydaje się działać
    delete window; // nie wiem jak się za to zabrać
    delete cache; // help
}

void ChatHistory::prepareList()
{
    QSqlQuery addresses;
    QString address;

    addresses = db->select("SELECT DISTINCT Sender FROM CHATHISTORY "
                            "WHERE Sender NOT LIKE 'me' "
                           "UNION "
                           "SELECT DISTINCT Receiver FROM CHATHISTORY "
                            "WHERE Receiver NOT LIKE 'me';");
    addresses.first();

    do
    {  
        address = addresses.value(0).toString();
        QListWidgetItem* item = new QListWidgetItem(address);

        window->ui->list->addItem(item);
        cache->insert(address, "");
    }
    while (addresses.next());
}

void ChatHistory::populateBrowser(QListWidgetItem* newItem, QListWidgetItem* prevItem)
{
    window->ui->browser->clear();

    QString address = newItem->text();

    if (cache->value(address) != "")
    {
        window->ui->browser->append(cache->value(address));
        return;
    }

    QSqlQuery messages;
    QString cacheItem = "",
            datetime,
            sender,
            message;

    messages = db->selectMessages(address, "ASC");
    messages.first();

    /* if (messages.size() == -1)  // SQLite nie wydaje się obsługiwać size'a,
    {                              // ale taki if to i tak nierealny scenariusz
        cache->insert(address, " ");
        return;
    } */

    do
    {
        datetime = messages.value(0).toDateTime().toString("yyyy.MM.dd, hh:mm:ss");
        sender = messages.value(1).toString();
        message = messages.value(2).toString();

        cacheItem += "[" + datetime + " | " +
                     sender + "]:\n" + message + "\n";
    }
    while (messages.next());

    window->ui->browser->setText(cacheItem);
    cache->insert(address, cacheItem);
}
