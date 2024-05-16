#include "functions_for_client.h"

FunctionsForClient::FunctionsForClient()
{
    client = Client::getInstance();

    ui_auth = new AuthRegForm;
    ui_auth->show();
    connect(ui_auth, &AuthRegForm::auth, this, &FunctionsForClient::sendAuth);
    connect(ui_auth, &AuthRegForm::reg, this, &FunctionsForClient::sendReg);
    connect(client, &Client::msgFromServer, this, &FunctionsForClient::msgHandler);
}

void FunctionsForClient::sendAuth(QString log, QString pass)
{
    client->sendMsgToServer("auth&" + log + "&" + pass);
}

void FunctionsForClient::sendReg(QString log, QString pass, QString email)
{
    client->sendMsgToServer("auth&" + log + "&" + pass + "&" + email);
}

void FunctionsForClient::msgHandler(QString msg)
{
    if (msg == "Successfully auth\r\n" || msg == "Successfully reg\r\n")
    {
        delete ui_auth;
        ui_main = new MainWindow;
        ui_main->show();

        connect(ui_main, &MainWindow::encrypt, this, &FunctionsForClient::solutionEncrypt);
        connect(ui_main, &MainWindow::hash, this, &FunctionsForClient::solutionHash);
        connect(ui_main, &MainWindow::spline, this, &FunctionsForClient::solutionSpline);
        connect(ui_main, &MainWindow::gradient, this, &FunctionsForClient::solutionGradient);

        connect(this, &FunctionsForClient::solution, ui_main, &MainWindow::solution);
    }
    else
    {
        emit solution(msg);
    }
}

void FunctionsForClient::solutionEncrypt(QString text, QString key)
{
    client->sendMsgToServer("vigenereEncrypt&" + text + "&" + key);
}

void FunctionsForClient::solutionHash(QString text)
{
    client->sendMsgToServer("sha256&" + text);
}

void FunctionsForClient::solutionSpline(QString pointA, QString pointB, QString pointC)
{
    client->sendMsgToServer("splineMethod&" + pointA + "&" + pointB + "&" + pointC);
}

void FunctionsForClient::solutionGradient(QString learningRate, QString maxIterations, QString precision)
{
    client->sendMsgToServer("gradientDescent&" + learningRate + "&" + maxIterations + "&" + precision);
}
