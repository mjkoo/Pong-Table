#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

#include <sqlite.h>

class Database
{
public:
    Database(std::string filename);
    virtual ~Database();

    bool login(std::string name, std::string password);
    bool create(std::string name, std::string password);
    std::vector<std::string> getStandings();
    void recordWin(std::string name);
    void recordLoss(std::string name);
    void recordTie(std::string name);

private:
    sqlite *db_; 
};

#endif /* DATABASE_H_ */

