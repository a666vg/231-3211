#ifndef FUNCTIONS_FOR_CLIENT_H
#define FUNCTIONS_FOR_CLIENT_H

#include <QObject>
#include "mainwindow.h"
#include "authregform.h"
#include "client.h"

class FunctionsForClient : public QObject
{
    Q_OBJECT

private:
    MainWindow* ui_main;
    AuthRegForm* ui_auth;
    Client* client;

public:
    FunctionsForClient();

public slots:
    void sendAuth(QString log, QString pass);
    void sendReg(QString log, QString pass, QString email);
    void msgHandler(QString msg);

    void solutionEncrypt(QString text, QString key);
    void solutionHash(QString text);
    void solutionSpline(QString pointA, QString pointB, QString pointC);
    void solutionGradient(QString learningRate, QString maxIterations, QString precision);

signals:
    void solution(QString text);
};

#endif // FUNCTIONS_FOR_CLIENT_H
