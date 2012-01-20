#include "Database.h"

#include <iostream>

#include <assert.h>

using namespace std;

Database::Database(string filename)
{
    char *errmsg;
    db_ = sqlite_open(filename.c_str(), 0666, &errmsg);

    assert(db_ != NULL);

    sqlite_freemem(errmsg);
}

Database::~Database()
{
    sqlite_close(db_);
}

bool
Database::login(string name, string password)
{
    int n;
    const char *tail, **value, **colname;
    char *errmsg;
    sqlite_vm *vm;
    bool ret = false;

    /* Bad, SQL Injection */
    string query = "select password from teams where name='" + name + "';";

    if (sqlite_compile(db_, query.c_str(), &tail, &vm, &errmsg) != SQLITE_OK) {
        sqlite_freemem(errmsg);
        return false;
    }
   
    if (sqlite_step(vm, &n, &value, &colname) == SQLITE_ROW)
        ret = password == string(value[0]);

    sqlite_finalize(vm, &errmsg);
    sqlite_freemem(errmsg);

    return ret;
}

bool
Database::create(string name, string password)
{
    int n;
    const char *tail, **value, **colname;
    char *errmsg;
    sqlite_vm *vm;
    bool ret = false;

    /* Bad, SQL Injection */
    string query = "insert into teams(name, password) values('"
        + name + "', '" + password + "');";

    cout << query << endl;

    if (sqlite_compile(db_, query.c_str(), &tail, &vm, &errmsg) != SQLITE_OK) {
        sqlite_freemem(errmsg);
        return false;
    }
   
    ret = sqlite_step(vm, &n, &value, &colname) == SQLITE_DONE;

    sqlite_finalize(vm, &errmsg);
    sqlite_freemem(errmsg);

    return ret;
}
