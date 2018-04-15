#ifndef SqliteConnectionManager_hpp
#define SqliteConnectionManager_hpp

#include <sqlite3.h>

class SqliteConnectionManager {
private:
    SqliteConnectionManager();

    static SqliteConnectionManager *instance;
    sqlite3 *db;

public:
    ~SqliteConnectionManager();

    static SqliteConnectionManager *get_instance();
    sqlite3* get_db() {return db;};
};

#endif /* SqliteConnectionManager_hpp */
