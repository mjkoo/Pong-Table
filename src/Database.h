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
    explicit Database(const std::string& filename);
    virtual ~Database();

    bool login(const std::string& name, const std::string& password);
    bool create(const std::string& name, const std::string& password);
    table_t getStandings();

    void recordWin(const std::string& name);
    void recordLoss(const std::string& name);
    void recordTie(const std::string& name);

private:
    table_t select(const std::string& query);
    bool executeCommand(const std::string& query);
    
private:
    sqlite *db_; 

    Database(const Database&);
    Database& operator=(const Database&);
};

#endif /* DATABASE_H_ */

