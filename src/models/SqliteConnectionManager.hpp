#ifndef SqliteConnectionManager_hpp
#define SqliteConnectionManager_hpp

class SqliteConnectionManager {
private:
    SqliteConnectionManager();

    static SqliteConnectionManager *instance;
    sqlite3 *db;

public:
    ~SqliteConnectionManager();

    static SqliteConnectionManager *getInstance();
};

#endif /* SqliteConnectionManager_hpp */
