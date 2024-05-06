#include "functions_for_server.h"
#include "database.h"

QByteArray FunctionsForServer::parse(QString data)
{
    // data = NameOfFunc&Param1&Param2&Param3 => return NameOfFunc(Param1, Param2, Param3)
    QStringList dataList = data.split(QLatin1Char('&')); // Деление строки по символу '&'
    QString nameOfFunc = dataList.front(); // Название функции

    dataList.pop_front(); // Удаление из списка элемента с названием функции
    dataList.replaceInStrings(QRegularExpression("\\r\\n$"), QString()); // Обрезка лишних символов

    if (nameOfFunc == "auth") // Если авторизация
    {
        return auth(dataList.at(0), dataList.at(1));
    }
    else if (nameOfFunc == "reg") // Если регистрация
    {
        return reg(dataList.at(0), dataList.at(1), dataList.at(2));
    }
    else if (nameOfFunc == "vigenereEncrypt") // Если градиентый спуск
    {
        return vigenereEncrypt();
    }
    else if (nameOfFunc == "sha256") // Если градиентый спуск
    {
        return sha256();
    }
    else if (nameOfFunc == "splineMethod") // Если градиентый спуск
    {
        return splineMethod();
    }
    else if (nameOfFunc == "gradientDescent") // Если градиентый спуск
    {
        return gradientDescent();
    }
    else if (nameOfFunc == "\xFF\xFB\x1F\xFF\xFB \xFF\xFB\x18\xFF\xFB'\xFF\xFD\x01\xFF\xFB\x03\xFF\xFD\x03")
    {
        return QString("").toUtf8(); // Игнорирование мусорного сообщения
    }
    else // Если другое
    {
        return QString("Error while parsing\r\n").toUtf8(); // Сообщение об ошибке
    }
}

QByteArray FunctionsForServer::auth(QString log, QString pass)
{
    QSqlQuery* query = new QSqlQuery;
    query->prepare("SELECT * FROM users WHERE userLogin = :userLogin AND userPassword = :userPassword");
    query->bindValue(":userLogin", log);
    query->bindValue(":userPassword", pass);

    if (!Database::getInstance().queryToDatabase(query))
    {
        return query->lastError().text().toUtf8();
    }

    if (query->first())
    {
        return QString("Successfully auth\r\n").toUtf8();
    }

    return QString("Wrong login or password\r\n").toUtf8();
}

QByteArray FunctionsForServer::reg(QString log, QString pass, QString mail)
{
    QSqlQuery* query = new QSqlQuery;
    query->prepare("INSERT INTO users (userLogin, userPassword, userEmail, userPrivilege) "
                   "VALUES (:userLogin, :userPassword, :userEmail, :userPrivilege)");
    query->bindValue(":userLogin", log);
    query->bindValue(":userPassword", pass);
    query->bindValue(":userEmail", mail);
    query->bindValue(":userPrivilege", QString("default"));

    if (!Database::getInstance().queryToDatabase(query))
    {
        return query->lastError().text().toUtf8(); // Ну ладно, на самом деле Анжелина хорошая и умная
    }
    else
    {
        return QString("Successfully reg\r\n").toUtf8();
    }
}

QByteArray FunctionsForServer::vigenereEncrypt()
{
    return QString("Vigenere encrypt function\r\n").toUtf8();
}

QByteArray FunctionsForServer::sha256()
{
    return QString("Sha-256 function\r\n").toUtf8();
}

QByteArray FunctionsForServer::splineMethod()
{
    return QString("Spline method function\r\n").toUtf8();
}

QByteArray FunctionsForServer::gradientDescent()
{
    return QString("Gradient descent function\r\n").toUtf8();
}
