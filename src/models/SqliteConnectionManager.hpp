#ifndef SqliteConnectionManager_hpp
#define SqliteConnectionManager_hpp

class SqliteConnectionManager {
private:
    SqliteConnectionManager();

    static SqliteConnectionManager *instance;
    sqlite3 *db;

public:
    static SqliteConnectionManager *getInstance();
};

#endif /* SqliteConnectionManager_hpp */
