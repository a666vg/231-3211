#include <QCoreApplication>
#include "tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TcpServer server;

    return app.exec();
}

