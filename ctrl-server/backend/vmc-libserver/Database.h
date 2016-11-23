#ifndef DATABASE_H
#define DATABASE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <mysql++.h>
#pragma GCC diagnostic pop
#include <memory>
#include <string>

namespace vmc
{
    namespace sql = mysqlpp;

    class Database
    {
    public:
        Database(std::string const &host, int port, std::string const &user, std::string const &pass,
            std::string const &database, bool createDatabase = true);
        sql::Query query(std::string const &queryString);
        sql::SimpleResult execute(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params = {});
        sql::UseQueryResult use(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params = {});
        sql::StoreQueryResult store(std::string const &queryString, std::initializer_list<sql::SQLTypeAdapter> params = {});

    private:
        sql::Connection connection;
    };

    namespace database
    {
        void initDatabase(std::string const &host, int port, std::string const &user, std::string const &pass,
            std::string const &database, bool createDatabase = true);

        std::unique_ptr<Database> getDatabase();
    }
}

#endif
