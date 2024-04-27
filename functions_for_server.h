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

    static QByteArray vigenereEncrypt(const QString& text, const QString& key); // Шифрование
    static QString vigenereDecrypt(const QString& text, const QString& key); // Дешифрование
    static QChar shiftChar(QChar c, int shift); // Сдвиг символа

    static QByteArray gradientDescent(QString learningRate, QString maxIterations, QString precision); // Градиентный спуск
    static double computeGradient(QString function, double x); // Вычисление градиента
};

#endif // FUNCTIONS_FOR_SERVER_H
