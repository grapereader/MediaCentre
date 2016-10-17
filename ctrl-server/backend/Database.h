#ifndef DATABASE_H
#define DATABASE_H

#include <mysql++.h>
#include <memory>
#include <string>

namespace vmc
{
    namespace sql = mysqlpp;

    class Database
    {
    public:
        Database(std::string const &host, int port, std::string const &user, std::string const &pass,
            std::string const &database, bool createDatabase = true, bool createTables = true);
        sql::Query query(std::string const &queryString);
        sql::SimpleResult execute(std::string const &queryString, sql::SQLQueryParms *params = NULL);
        sql::UseQueryResult use(std::string const &queryString, sql::SQLQueryParms *params = NULL);
        sql::StoreQueryResult store(std::string const &queryString, sql::SQLQueryParms *params = NULL);

    private:
        sql::Connection connection;
    };
}

#endif
