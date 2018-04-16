#include <stdio.h>
#include <sqlite3.h>

#include "SqliteConnectionManager.hpp"

extern char *PATH_TO_DB;


SqliteConnectionManager::SqliteConnectionManager() {
    int connection = sqlite3_open(PATH_TO_DB, &db);

    if (connection) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
}

SqliteConnectionManager::~SqliteConnectionManager() {
    sqlite3_close(db);
}
