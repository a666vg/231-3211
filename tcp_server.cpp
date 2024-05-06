#include "tcp_server.h" // Подключение заголовочного файла
#include "functions_for_server.h" // Подключение функций для сервера

TcpServer::~TcpServer()
{
    mTcpServer->close(); // Закрытие сервера
}

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this); // Создание сервера

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &TcpServer::slotNewConnection); // Связь слота нового подключения с сигналом от сервера

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) // Прослушивание сервером всех адресов и порта 33333
    {
        qDebug() << "Server is not started\r\n"; // Если не прослушивается
    }
    else
    {
        qDebug() << "Server is started\r\n"; // Если прослушивается
    }
}

void TcpServer::slotNewConnection()
{
    while (mTcpServer->hasPendingConnections()) {
        QTcpSocket *socket = mTcpServer->nextPendingConnection(); // Запись в переменную ожидающего сокета
        int descriptor = socket->socketDescriptor();
        mSockets[descriptor] = socket;

        connect(socket, &QTcpSocket::readyRead, this, &TcpServer::slotServerRead); // Соединение сигнала готовности к чтению со слотом чтения сообщений
        connect(socket, &QTcpSocket::disconnected, this, &TcpServer::slotClientDisconnected); // Соединение сигнала и слота отключения клиента

        socket->write("Server connected!\r\n"); // Отправка сокету сообщения об установлении соединения
    }
}

void TcpServer::slotServerRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender()); // Узнаем клиента, отправившего сообщение
    if (!socket)
    {
        return; // Если сокета не существует
    }

    int descriptor = socket->socketDescriptor();
    auto iter = mSockets.find(descriptor);

    if (iter == mSockets.end())
    {
        qDebug() << "Error";
        return; // Если сокет за пределами словаря
    }

    socket = iter.value();

    QString res = ""; // Строка результат
    while (socket->bytesAvailable() > 0) // Пока можно считывать байты
    {
        QByteArray arr = socket->readAll(); // Создание массива и запись в него всего, что считывается
        qDebug() << arr << "\n"; // Вывод считанных данных в консоль

        if (arr == "\x01") // Если конец строки
        {
            socket->write(res.toUtf8()); // Отправка проанализированного результата
            res = ""; // Обнуление строки
        }
        else // Если не конец строки
            res.append(arr); // Добавление к строке считанных данных
    }

    if (!res.isEmpty())
    {
        socket->write(FunctionsForServer::parse(res)); // Отправка проанализированного результата
    }
}

void TcpServer::slotClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    int descriptor = socket->socketDescriptor();
    mSockets.remove(descriptor);
    socket->deleteLater();
}
