#include "Database.h"

#include <exception>

namespace vmc
{
    Database::Database(std::string const &host, int port, std::string const &user, std::string const &pass,
        std::string const &database, bool createDatabase)
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

    void loadParams(sql::SQLQueryParms &sqlParams, std::initializer_list<sql::SQLTypeAdapter> params)
    {
        for (auto it = params.begin(); it != params.end(); it++)
        {
            sqlParams << *it;
        }
    }

    sql::SimpleResult Database::execute(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params)
    {
        auto query = this->query(queryString);
        if (params.size() > 0)
        {
            sql::SQLQueryParms sqlParams(&query);
            loadParams(sqlParams, params);
            return query.execute(sqlParams);
        }
        return query.execute();
    }

    sql::UseQueryResult Database::use(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params)
    {
        auto query = this->query(queryString);
        if (params.size() > 0)
        {
            sql::SQLQueryParms sqlParams(&query);
            loadParams(sqlParams, params);
            return query.use(sqlParams);
        }
        return query.use();
    }

    sql::StoreQueryResult Database::store(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params)
    {
        auto query = this->query(queryString);
        if (params.size() > 0)
        {
            sql::SQLQueryParms sqlParams(&query);
            loadParams(sqlParams, params);
            return query.store(sqlParams);
        }
        return query.store();
    }

    namespace database
    {
        namespace conf
        {
            std::string const *host;
            int port;
            std::string const *user;
            std::string const *pass;
            std::string const *database;
            bool createDatabase;
        }

        void initDatabase(std::string const &host, int port, std::string const &user, std::string const &pass,
            std::string const &database, bool createDatabase)
        {
            conf::host = new std::string(host);
            conf::port = port;
            conf::user = new std::string(user);
            conf::pass = new std::string(pass);
            conf::database = new std::string(database);
            conf::createDatabase = createDatabase;
        }

        std::unique_ptr<Database> getDatabase()
        {
            return std::unique_ptr<Database>(new Database(*conf::host, conf::port, *conf::user, *conf::pass,
                *conf::database, conf::createDatabase));
        }
    }
}
