#include <stdio.h>
#include <sqlite3.h>

#include "../constants.hpp"
#include "SqliteConnectionManager.hpp"


SqliteConnectionManager::SqliteConnectionManager() {
    int connection = sqlite3_open(Constants::path_to_db.c_str(), &db);

    if (connection) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
}

SqliteConnectionManager::~SqliteConnectionManager() {
    sqlite3_close(db);
}
