#include <stdio.h>
#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../SqliteConnectionManager.hpp"


static int create_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}


AbstractSqliteModel::AbstractSqliteModel() {
    connection_manager = SqliteConnectionManager::get_instance();
}

AbstractSqliteModel::~AbstractSqliteModel() {
    delete connection_manager;
    delete table_name;
}

int AbstractSqliteModel::execute_sql(std::string &sql) {
    char *error_message = 0;
    int connection;

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), create_callback, 0, &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }

    return connection;
}


// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
