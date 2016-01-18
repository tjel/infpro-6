#include "tcplistener.h"

void Server::start()
{
    listener.listen(8888);
}
