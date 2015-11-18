#ifndef THREAD_CONTROLS
#define THREAD_CONTROLS

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class Thread_Controls : public QThread
{
    Q_OBJECT
public:
    explicit Thread_Controls(int iID, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    int Descriptior;

};

#endif // THREAD_CONTROLS

