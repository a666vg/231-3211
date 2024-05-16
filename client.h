#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class Client;

class ClientDestroyer
{
private:
    Client* p_instance;

public:
    ~ClientDestroyer() { delete p_instance; }
    void initialize(Client* p) { p_instance = p; }
};

class Client : public QObject
{
    Q_OBJECT

private:
    static Client* p_instance;
    static ClientDestroyer destroyer;
    QTcpSocket* mTcpSocket;

private slots:
    void slotServerRead();

protected:
    explicit Client(QObject* parent = nullptr);
    Client(Client&) = delete;
    Client& operator=(Client&) = delete;
    friend class ClientDestroyer;

public:
    static Client* getInstance();
    void sendMsgToServer(QString msg);

signals:
    void msgFromServer(QString msg);
};

#endif // CLIENT_H
