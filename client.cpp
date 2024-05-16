#include "client.h"

Client* Client::p_instance = nullptr;
ClientDestroyer Client::destroyer;

Client::Client(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
}

Client* Client::getInstance()
{
    if (!p_instance)
    {
        p_instance = new Client();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

void Client::sendMsgToServer(QString msg)
{
    mTcpSocket->write(msg.toUtf8());
}

void Client::slotServerRead()
{
    QString msg = "";

    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }

    qDebug() << msg;
    emit msgFromServer(msg);
}
