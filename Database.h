#ifndef DATABASE_H_
#define DATABASE_H_

#include <string>
#include <vector>

#include <sqlite.h>

typedef std::vector<std::string> row_t;
typedef std::vector<row_t> table_t;

class Database
{
public:
    Database(std::string filename);
    virtual ~Database();

    bool login(std::string name, std::string password);
    bool create(std::string name, std::string password);
    table_t getStandings();

    void recordWin(std::string name);
    void recordLoss(std::string name);
    void recordTie(std::string name);

private:
    table_t select(std::string query);
    bool executeCommand(std::string query);
    

private:
    sqlite *db_; 
};

#endif /* DATABASE_H_ */

