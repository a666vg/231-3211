#ifndef FUNCTIONS_FOR_SERVER_H
#define FUNCTIONS_FOR_SERVER_H

#include <QString>
#include <QStringList>
#include <QByteArray>

class FunctionsForServer
{
public:
    static QByteArray parse(QString data); // Анализ запросов

private:
    static QByteArray auth(QString log, QString pass); // Авторизация
    static QByteArray reg(QString log, QString pass, QString mail); // Регистрация

    static QByteArray gradientDescent(QString learningRate, QString maxIterations, QString precision); // Градиентный спуск
    static double computeGradient(double x); // Вычисление градиента
};

#endif // FUNCTIONS_FOR_SERVER_H
