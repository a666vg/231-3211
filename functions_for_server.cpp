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
        return vigenereEncrypt(dataList.at(0), dataList.at(1));
    }
    else if (nameOfFunc == "sha256") // Если градиентый спуск
    {
        return sha256(dataList.at(0).toStdString());
    }
    else if (nameOfFunc == "splineMethod") // Если градиентый спуск
    {
        return splineMethod(dataList.at(0), dataList.at(1), dataList.at(2));
    }
    else if (nameOfFunc == "gradientDescent") // Если градиентый спуск
    {
        return gradientDescent(dataList.at(0), dataList.at(1), dataList.at(2));
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

QByteArray FunctionsForServer::vigenereEncrypt(const QString& text, const QString& key)
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

QChar FunctionsForServer::shiftChar(QChar c, int shift)
{
    if (c.isUpper())
    {
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

/* QByteArray FunctionsForServer::sha256(const QString& text)
{
    return QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha256).toHex();
} */

uint32_t FunctionsForServer::rotr(uint32_t x, uint32_t n)
{
    return (x >> n) | (x << (32 - n));
}

uint32_t FunctionsForServer::choose(uint32_t e, uint32_t f, uint32_t g)
{
    return (e & f) ^ (~e & g);
}

uint32_t FunctionsForServer::majority(uint32_t a, uint32_t b, uint32_t c)
{
    return (a & b) ^ (a & c) ^ (b & c);
}

uint32_t FunctionsForServer::sig0(uint32_t x)
{
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

uint32_t FunctionsForServer::sig1(uint32_t x)
{
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

std::vector<uint8_t> FunctionsForServer::pad_message(const std::string& message)
{
    uint64_t bit_len = message.size() * 8;
    std::vector<uint8_t> padded_message(message.begin(), message.end());
    padded_message.push_back(0x80);

    while ((padded_message.size() * 8) % 512 != 448)
    {
        padded_message.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i)
    {
        padded_message.push_back(bit_len >> (i * 8));
    }

    return padded_message;
}

std::array<uint32_t, 8> FunctionsForServer::compute_hash(const std::vector<uint8_t>& padded_message)
{
    std::array<uint32_t, 8> hash_values = initial_hash_values;

    for (size_t i = 0; i < padded_message.size(); i += 64)
    {
        std::array<uint32_t, 64> w = {0};
        for (size_t j = 0; j < 16; ++j)
        {
            w[j] = (padded_message[i + 4 * j] << 24) |
                   (padded_message[i + 4 * j + 1] << 16) |
                   (padded_message[i + 4 * j + 2] << 8) |
                   padded_message[i + 4 * j + 3];
        }

        for (size_t j = 16; j < 64; ++j)
        {
            w[j] = sig1(w[j - 2]) + w[j - 7] + sig0(w[j - 15]) + w[j - 16];
        }

        uint32_t a = hash_values[0];
        uint32_t b = hash_values[1];
        uint32_t c = hash_values[2];
        uint32_t d = hash_values[3];
        uint32_t e = hash_values[4];
        uint32_t f = hash_values[5];
        uint32_t g = hash_values[6];
        uint32_t h = hash_values[7];

        for (size_t j = 0; j < 64; ++j)
        {
            uint32_t temp1 = h + (rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25)) + choose(e, f, g) + k[j] + w[j];
            uint32_t temp2 = (rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22)) + majority(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hash_values[0] += a;
        hash_values[1] += b;
        hash_values[2] += c;
        hash_values[3] += d;
        hash_values[4] += e;
        hash_values[5] += f;
        hash_values[6] += g;
        hash_values[7] += h;
    }

    return hash_values;
}

QByteArray FunctionsForServer::sha256(const std::string& message)
{
    std::vector<uint8_t> padded_message = pad_message(message);
    std::array<uint32_t, 8> hash_values = compute_hash(padded_message);

    std::ostringstream oss;
    for (auto val : hash_values)
    {
        oss << std::hex << std::setw(8) << std::setfill('0') << val;
    }

    return QByteArray::fromStdString(oss.str());
}

QByteArray FunctionsForServer::splineMethod(const QString& pointA, const QString& pointB, const QString& pointC)
{
    QVector<QPointF> dataPoints;
    dataPoints.append(toPoint(pointA));
    dataPoints.append(toPoint(pointB));
    dataPoints.append(toPoint(pointC));

    QVector<QPointF> splineCoefficients;

    QVector<double> h(dataPoints.size() - 1);
    for (int i = 0; i < h.size(); ++i)
    {
        h[i] = dataPoints[i + 1].x() - dataPoints[i].x();
    }

    QVector<double> alpha(h.size());
    for (int i = 1; i < alpha.size(); ++i)
    {
        alpha[i] = 3 * (dataPoints[i + 1].y() - dataPoints[i].y()) / h[i] -
                   3 * (dataPoints[i].y() - dataPoints[i - 1].y()) / h[i - 1];
    }

    QVector<double> l(dataPoints.size());
    QVector<double> mu(dataPoints.size());
    QVector<double> z(dataPoints.size());
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < l.size() - 1; ++i)
    {
        l[i] = 2 * (dataPoints[i + 1].x() - dataPoints[i - 1].x()) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    QVector<double> b(dataPoints.size());
    QVector<double> c(dataPoints.size());
    QVector<double> d(dataPoints.size());
    l[dataPoints.size() - 1] = 1;
    z[dataPoints.size() - 1] = 0;
    c[dataPoints.size() - 1] = 0;

    for (int j = dataPoints.size() - 2; j >= 0; --j)
    {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (dataPoints[j + 1].y() - dataPoints[j].y()) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    splineCoefficients.reserve(dataPoints.size() - 1);
    for (int i = 0; i < dataPoints.size() - 1; ++i)
    {
        splineCoefficients.append(QPointF(b[i], c[i]));
    }

    QString result;
    for (QPointF p : splineCoefficients)
    {
        result.append(QString::number(p.x()));
        result.append(',');
        result.append(QString::number(p.y()));
        result.append(' ');
    }

    return result.toUtf8();
}

QPointF FunctionsForServer::toPoint(const QString& point)
{
    QStringList parts = point.split(',');
    double x = parts[0].toDouble();
    double y = parts[1].toDouble();

    return QPointF(x, y);
}

QByteArray FunctionsForServer::gradientDescent(const QString& learningRate, const QString& maxIterations, const QString& precision)
{
    double x = 0;

    for (int i = 0; i < maxIterations.toInt(); ++i)
    {
        double gradient = 2 * x; // Используемая функция - x^2 => Градиент = 2x
        double newX = x - learningRate.toDouble() * gradient;

        if (qAbs(newX - x) < precision.toDouble())
        {
            break;
        }

        x = newX;
    }

    return QString::number(x).toUtf8();
}
