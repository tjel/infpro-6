#ifndef SERVER_CONTROLS
#define SERVER_CONTROLS

#include <QTcpServer>
#include <QDebug>
#include "thread_controls.h"

class Server_Controls : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server_Controls(QObject *parent = 0);
    void StartServer();

signals:

public slots:

protected:
    void incomingConnection(int Descriptior);

};

#endif // SERVER_CONTROLS

