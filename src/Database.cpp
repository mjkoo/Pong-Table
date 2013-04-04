#include "Database.h"

#include <iostream>

#include <assert.h>

using namespace std;

Database::Database(const string& filename)
  : db_(NULL)
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
Database::login(const string& name, const string& password)
{
    /* Bad, SQL Injection */
    string query;
    table_t table;

    query = "select password from teams where name='" + name + "';";
    table = select(query);
    
    return !table.empty() && table[0][0] == password;
}

bool
Database::create(const string& name, const string& password)
{
    /* Bad, SQL Injection */
    string query;

    query = "insert into teams(name, password) values('" + name +
        "', '" + password + "');";
    cout << query << endl;
    return executeCommand(query);
}

table_t
Database::select(const string& query)
{
    int i, n;
    const char *tail, **values, **colname;
    char *errmsg;
    sqlite_vm *vm;
    table_t ret;

    if (sqlite_compile(db_, query.c_str(), &tail, &vm, &errmsg) != SQLITE_OK) {
        sqlite_freemem(errmsg);
        return ret;
    }
   
    while (sqlite_step(vm, &n, &values, &colname) == SQLITE_ROW) {
        row_t row;
        for (i = 0; i < n; i++)
            row.push_back(string(values[i]));
        ret.push_back(row);
    }

    sqlite_finalize(vm, &errmsg);
    sqlite_freemem(errmsg);

    return ret;
}

bool
Database::executeCommand(const string& query)
{
    int n;
    const char *tail, **value, **colname;
    char *errmsg;
    sqlite_vm *vm;
    bool ret = false;

    if (sqlite_compile(db_, query.c_str(), &tail, &vm, &errmsg) != SQLITE_OK) {
        sqlite_freemem(errmsg);
        return false;
    }
   
    ret = sqlite_step(vm, &n, &value, &colname) == SQLITE_DONE;

    sqlite_finalize(vm, &errmsg);
    sqlite_freemem(errmsg);

    return ret;
}

