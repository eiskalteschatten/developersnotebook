#include <stdio.h>
#include <sqlite3.h>

#include "SqliteConnectionManager.hpp"

extern char *PATH_TO_DB;

SqliteConnectionManager* SqliteConnectionManager::instance = 0;


SqliteConnectionManager* SqliteConnectionManager::getInstance() {
    if (instance == 0) {
        instance = new SqliteConnectionManager();
    }

    return instance;
}

SqliteConnectionManager::SqliteConnectionManager() {
    int connection = sqlite3_open(PATH_TO_DB, &db);

    if (connection) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

SqliteConnectionManager::~SqliteConnectionManager() {
    sqlite3_close(db);
    delete instance;
}
