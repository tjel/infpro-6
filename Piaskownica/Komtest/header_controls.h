#ifndef HEADER_CONTROLS
#define HEADER_CONTROLS

#include <QTcpServer>
#include <QDebug>
#include "thread_controls.h"

class header : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void StartServer();

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);

};

#endif // MYSERVER_H
#endif // HEADER_CONTROLS

