#include <QCoreApplication>
#include <QSqlDatabase>
#include "tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv); // Создание приложения

    TcpServer server; // Запуск сервера

    return app.exec(); // Запуск приложения
}

