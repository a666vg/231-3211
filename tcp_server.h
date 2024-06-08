#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

/**
 * @brief Class representing a TCP server.
 */
class TcpServer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a TCP server.
     * @param parent Parent object (default is nullptr).
     */
    explicit TcpServer(QObject* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~TcpServer();

public slots:
    /**
     * @brief Slot for handling new client connections.
     */
    void slotNewConnection();

    /**
     * @brief Slot for handling client disconnections.
     */
    void slotClientDisconnected();

    /**
     * @brief Slot for reading data from clients.
     */
    void slotServerRead();

private:
    QTcpServer* mTcpServer; ///< The TCP server
    QMap<int, QTcpSocket*> mSockets; ///< Map of connected client sockets
};

#endif // TCP_SERVER_H
