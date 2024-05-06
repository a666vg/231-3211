#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>

class Database;

class DatabaseDestroyer
{
private:
    Database* p_instance;

public:
    ~DatabaseDestroyer();
    void initialize(Database* p);
};

class Database
{
private:
    static Database* p_instance;
    static DatabaseDestroyer destroyer;
    QSqlDatabase db;

    Database();
    ~Database();
    Database(const Database&) = delete;
    void operator= (const Database&) = delete;
    friend class DatabaseDestroyer;

public:
    void createTable(); // Создание таблицы
    static Database& getInstance(); // Открытие базы данных, если не открыта
    QSqlDatabase& getDatabase();
    bool queryToDatabase(QSqlQuery* q); // Запрос базе данных
};

#endif // DATABASE_H
