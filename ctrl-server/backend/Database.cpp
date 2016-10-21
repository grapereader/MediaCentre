#include "Database.h"

#include <exception>

namespace vmc
{
    Database::Database(std::string const &host, int port, std::string const &user, std::string const &pass,
        std::string const &database, bool createTables, bool createDatabase)
        : connection(false)
    {
        this->connection.connect(NULL, host.c_str(), user.c_str(), pass.c_str());

        if (!this->connection.select_db(database))
        {
            if (!createDatabase) throw std::exception();
            if (this->connection.create_db(database))
            {
                this->connection.select_db(database);
            }
            else
            {
                throw std::exception();
            }
        }
    }

    sql::Query Database::query(std::string const &queryString)
    {
        return this->connection.query(queryString);
    }

    sql::SimpleResult Database::execute(std::string const &queryString, sql::SQLQueryParms *params)
    {
        auto query = this->query(queryString);
        if (params != NULL)
        {
            return query.execute(*params);
        }
        return query.execute();
    }

    sql::UseQueryResult Database::use(std::string const &queryString, sql::SQLQueryParms *params)
    {
        auto query = this->query(queryString);
        if (params != NULL)
        {
            return query.use(*params);
        }
        return query.use();
    }

    sql::StoreQueryResult Database::store(std::string const &queryString, sql::SQLQueryParms *params)
    {
        auto query = this->query(queryString);
        if (params != NULL)
        {
            return query.store(*params);
        }
        return query.store();
    }

    namespace database
    {
        std::string const *host;
        int port;
        std::string const *user;
        std::string const *pass;
        std::string const *database;
        bool createDatabase;
        bool createTables;

        void initDatabase(std::string const &host, int port, std::string const &user, std::string const &pass,
            std::string const &database, bool createDatabase, bool createTables)
        {
            database::host = new std::string(host);
            database::port = port;
            database::user = new std::string(user);
            database::pass = new std::string(pass);
            database::database = new std::string(database);
            database::createDatabase = createDatabase;
            database::createTables = createTables;
        }

        std::unique_ptr<Database> getDatabase()
        {
            return std::unique_ptr<Database>(
                new Database(*host, port, *user, *pass, *database, createTables, createDatabase));
        }
    }
}
