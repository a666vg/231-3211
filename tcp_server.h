#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QCoreApplication> // Для базовых функций QT
#include <QObject> // Для работы сигналов и слотов
#include <QString> // Для работы со строками
#include <QTcpServer> // Для реализации сервера по протоколу TCP
#include <QTcpSocket> // Для работы с сокетами (ip + порт)
#include <QtNetwork> // Для работы с сетью
#include <QByteArray> // Для работы с пригодными к передаче данными
#include <QDebug> // Для вывода сообщений в консоль

class TcpServer : public QObject // Публичный наследник класса QObject
{
    Q_OBJECT // Для включения сигнально-слотовой связи для класса
public:
    explicit TcpServer(QObject* parent = nullptr); // Конструктор сервера
    ~TcpServer(); // Деструктор сервера
public slots:
    void slotNewConnection(); // Слот нового подключения клиента
    void slotClientDisconnected(); // Слот отключения клиента
    void slotServerRead(); // Слот чтения сервера
private:
    QTcpServer* mTcpServer; // Сервер
    QTcpSocket* mTcpSocket; // Сокет (Текущее соединение)
    //int server_status; // Статус сервера
};

#endif // TCP_SERVER_H
