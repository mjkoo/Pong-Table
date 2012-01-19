#include "Database.h"

using namespace std;

Database::Database(string filename)
{
    char *errMsg;
    db_ = sqlite_open(filename.c_str(), 0666, &errMsg);
    sqlite_freemem(errMsg);
}

Database::~Database()
{
    sqlite_close(db_);
}

bool
Database::teamExists(std::string teamName)
{
    return false;
}
