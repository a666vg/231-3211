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

/**
 * @brief Forward declaration of the Database class.
 */
class Database;

/**
 * @brief Class responsible for destroying the Database instance.
 */
class DatabaseDestroyer
{
private:
    Database* p_instance; ///< Pointer to the Database instance

public:
    /**
     * @brief Destructor.
     */
    ~DatabaseDestroyer();

    /**
     * @brief Initializes the DatabaseDestroyer with a Database instance.
     * @param p Pointer to the Database instance.
     */
    void initialize(Database* p);
};

/**
 * @brief Singleton class for managing the database.
 */
class Database
{
private:
    static Database* p_instance; ///< Pointer to the single instance of the Database
    static DatabaseDestroyer destroyer; ///< Instance of DatabaseDestroyer for cleanup
    QSqlDatabase db; ///< Qt SQL Database instance

    /**
     * @brief Private constructor to prevent multiple instances.
     */
    Database();

    /**
     * @brief Destructor.
     */
    ~Database();

    /**
     * @brief Deleted copy constructor.
     */
    Database(const Database&) = delete;

    /**
     * @brief Deleted assignment operator.
     */
    void operator= (const Database&) = delete;

    friend class DatabaseDestroyer; ///< DatabaseDestroyer is a friend class

public:
    /**
     * @brief Creates a table in the database.
     */
    void createTable();

    /**
     * @brief Gets the single instance of the Database.
     * @return Reference to the Database instance.
     */
    static Database& getInstance();

    /**
     * @brief Gets the Qt SQL Database instance.
     * @return Reference to the QSqlDatabase instance.
     */
    QSqlDatabase& getDatabase();

    /**
     * @brief Executes a query on the database.
     * @param q Pointer to the QSqlQuery object.
     * @return True if the query was successful, false otherwise.
     */
    bool queryToDatabase(QSqlQuery* q);
};

#endif // DATABASE_H
