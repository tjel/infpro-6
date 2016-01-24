#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include <QDateTime>
#include "database.h"
#include "archivewindow.h"
#include "ui_archivewindow.h"

class ChatHistory : public QObject
{
    Q_OBJECT

    ArchiveWindow* window;
    Database* db;
    QMap<QString,QString>* cache;

    void prepareList();

public:
    ChatHistory(Database* db);
    ~ChatHistory();

private slots:
    void populateBrowser(QListWidgetItem*,QListWidgetItem*);
};

#endif // CHATHISTORY_H

