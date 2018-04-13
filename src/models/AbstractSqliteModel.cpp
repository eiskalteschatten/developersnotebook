#include <stdio.h>
#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../SqliteConnectionManager.hpp"

static int null_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

AbstractSqliteModel::AbstractSqliteModel() {
    connection_manager = SqliteConnectionManager::get_instance();
}

AbstractSqliteModel::~AbstractSqliteModel() {
    delete connection_manager;
    delete table_name;
}

void AbstractSqliteModel::update_single_int(const char *insert_column_name, const int &value) {
    char *error_message = 0;
    int connection;
    std::string sql = "UPDATE " + (std::string)table_name +
                      " SET " + (std::string)insert_column_name +
                      " = " + std::to_string(value) +
                      " WHERE id=" + std::to_string(id) + ";";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}

// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
