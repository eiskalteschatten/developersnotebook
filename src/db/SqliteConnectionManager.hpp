#ifndef SqliteConnectionManager_hpp
#define SqliteConnectionManager_hpp

#include <sqlite3.h>

class SqliteConnectionManager {
private:
    sqlite3 *db = nullptr;

public:
    SqliteConnectionManager();
    ~SqliteConnectionManager();

    sqlite3* get_db() {return db;};
};

#endif /* SqliteConnectionManager_hpp */
