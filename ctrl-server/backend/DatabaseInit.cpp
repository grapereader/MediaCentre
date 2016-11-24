#include "DatabaseInit.h"

#include "vmc-libserver/Database.h"

#include "tables/Users.h"

namespace vmc
{
    namespace database
    {
        void initTables()
        {
            std::unique_ptr<Database> db = database::getDatabase();

            db->execute(std::string(USERS_TABLE));
        }
    }
}
