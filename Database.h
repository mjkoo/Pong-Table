#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>

#include <sqlite.h>

class Database
{
public:
    Database(std::string filename);
    virtual ~Database();

    bool teamExists(std::string teamName);
    bool checkPassword(std::string teamName, std::string password);
    void setPassword(std::string teamName, std::string password);

private:
    sqlite *db_; 
};

#endif /* DATABASE_H_ */

