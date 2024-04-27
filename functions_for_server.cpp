#include "functions_for_server.h"

QByteArray FunctionsForServer::parse(QString data)
{
    // data = NameOfFunc&Param1&Param2&Param3 => return NameOfFunc(Param1, Param2, Param3)
    QStringList dataList = data.split(QLatin1Char('&')); // Деление строки по символу '&'
    QString nameOfFunc = dataList.front(); // Название функции
    dataList.pop_front(); // Удаление из списка элемента с названием функции
    if (nameOfFunc == "auth") // Если авторизация
    {
        return auth(dataList.at(0), dataList.at(1));
    }
    else if (nameOfFunc == "reg") // Если регистрация
    {
        return reg(dataList.at(0), dataList.at(1), dataList.at(2));
    }
    else if (nameOfFunc == "gradientDescent") // Если градиентый спуск
    {
        return gradientDescent(dataList.at(0), dataList.at(1), dataList.at(2));
    }
    else // Если другое
    {
        return QString("Error while parsing, try to type something again\r\n").toUtf8(); // Сообщение об ошибке
    }
}

QByteArray FunctionsForServer::auth(QString log, QString pass)
{
    Q_UNUSED(log);
    Q_UNUSED(pass);
    return QString("Succesfully auth\r\n").toUtf8();
}

QByteArray FunctionsForServer::reg(QString log, QString pass, QString mail)
{
    Q_UNUSED(log);
    Q_UNUSED(pass);
    Q_UNUSED(mail);
    return QString("Succesfully reg\r\n").toUtf8();
}

QByteArray FunctionsForServer::vigenereEncrypt(const QString &text, const QString &key)
{
    QString result;
    int keyLength = key.length();
    for (int i = 0; i < text.length(); ++i)
    {
        QChar currentChar = text.at(i);
        if (currentChar.isLetter())
        {
            QChar keyChar = key.at(i % keyLength);
            int shift = keyChar.toLatin1() - 'A';
            result.append(shiftChar(currentChar, shift));
        }
        else
        {
            result.append(currentChar);
        }
    }
    return result.toUtf8();
}

QString FunctionsForServer::vigenereDecrypt(const QString &text, const QString &key)
{
    QString result;
    int keyLength = key.length();
    for (int i = 0; i < text.length(); ++i)
    {
        QChar currentChar = text.at(i);
        if (currentChar.isLetter())
        {
            QChar keyChar = key.at(i % keyLength);
            int shift = keyChar.toLatin1() - 'A';
            result.append(shiftChar(currentChar, -shift));
        }
        else
        {
            result.append(currentChar);
        }
    }
    return result;
}

QChar FunctionsForServer::shiftChar(QChar c, int shift)
{
    if (c.isUpper()) {
        return QChar(((c.toLatin1() - 'A' + shift) % 26) + 'A');
    }
    else if (c.isLower())
    {
        return QChar(((c.toLatin1() - 'a' + shift) % 26) + 'a');
    }
    else
    {
        return c;
    }
}

QByteArray FunctionsForServer::gradientDescent(QString learningRate, QString maxIterations, QString precision)
{
    Q_UNUSED(learningRate);
    Q_UNUSED(maxIterations);
    Q_UNUSED(precision);
    return QString("Result: number\r\n").toUtf8();
}
