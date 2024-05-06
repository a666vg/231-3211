#include "database.h"

Database* Database::p_instance = nullptr;
DatabaseDestroyer Database::destroyer;

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.sqlite");

    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
}

void Database::createTable()
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE users "
               "(userLogin TEXT PRIMARY KEY UNIQUE NOT NULL, "
               "userPassword TEXT NOT NULL, "
               "userEmail TEXT UNIQUE NOT NULL, "
               "userPrivilege TEXT NOT NULL);");
}

Database::~Database()
{
    db.close();
}

Database& Database::getInstance()
{
    if (!p_instance)
    {
        p_instance = new Database();
        p_instance->createTable();
    }

    return* p_instance;
}

QSqlDatabase& Database::getDatabase()
{
    return db;
}

DatabaseDestroyer::~DatabaseDestroyer()
{
    delete p_instance;
}

void DatabaseDestroyer::initialize(Database* p)
{
    p_instance = p;
}

bool Database::queryToDatabase(QSqlQuery* q)
{
    if (!q->exec())
    {
        qDebug() << q->lastError().text();

        return false;
    }
    else
    {
        return true;
    }
}
