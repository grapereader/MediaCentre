/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
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
