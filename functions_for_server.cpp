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
        return QString("Error while parsing").toUtf8(); // Сообщение об ошибке
    }
}

QByteArray FunctionsForServer::auth(QString log, QString pass)
{
    Q_UNUSED(log);
    Q_UNUSED(pass);
    return QString("Succesfully auth").toUtf8();
}

QByteArray FunctionsForServer::reg(QString log, QString pass, QString mail)
{
    Q_UNUSED(log);
    Q_UNUSED(pass);
    Q_UNUSED(mail);
    return QString("Succesfully auth").toUtf8();
}

QByteArray FunctionsForServer::gradientDescent(QString learningRate, QString maxIterations, QString precision)
{
    Q_UNUSED(learningRate);
    Q_UNUSED(maxIterations);
    Q_UNUSED(precision);
    return QString("Result: 123").toUtf8();
}
