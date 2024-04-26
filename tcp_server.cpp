#include "tcp_server.h" // Подключение заголовочного файла
#include "functions_for_server.h" // Подключение функций для сервера

TcpServer::~TcpServer()
{
    mTcpServer->close(); // Закрытие сервера
    // server_status=0; // Установление статуса сервера на 0
}

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this); // Создание сервера

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &TcpServer::slotNewConnection); // Связь слота нового подключения с сигналом от сервера

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) // Прослушивание сервером всех адресов и порта 33333
    {
        qDebug() << "Server is not started"; // Если не прослушивается
    }
    else
    {
        //server_status=1; // Установление статуса сервера на 1
        qDebug() << "Server is started"; // Если прослушивается
    }
}

void TcpServer::slotNewConnection()
{
    //if(server_status==1){
    mTcpSocket = mTcpServer->nextPendingConnection(); // Запись в переменную ожидающего сокета

    connect(mTcpSocket, &QTcpSocket::readyRead,this,&TcpServer::slotServerRead); // Соединение сигнала готовности к чтению со слотом чтения сообщений
    connect(mTcpSocket,&QTcpSocket::disconnected,this,&TcpServer::slotClientDisconnected); // Соединение сигнала и слота отключения клиента

    mTcpSocket->write("Server connected!"); // Отправка сокету сообщения
    // }
}

void TcpServer::slotServerRead()
{
    QString res = ""; // Строка результат

    while (mTcpSocket->bytesAvailable() > 0) // Пока можно считывать байты
    {
        QByteArray arr = mTcpSocket->readAll(); // Создание массива и запись в него всего, что считывается
        qDebug() << arr << "\n"; // Вывод считанных данных в консоль
        if (arr == "\x01") // Если конец строки
        {
            mTcpSocket->write(res.toUtf8()); // Отправка ответа клиента
            res = ""; // Обнуление строки
        }
        else // Если не конец строки
            res.append(arr); // Добавление к строке считанных данных
    }
    mTcpSocket->write(FunctionsForServer::parse(res)); // Отправка проанализированного резултьата
}

void TcpServer::slotClientDisconnected()
{
    mTcpSocket->close(); // Закрытие сокета
}
