#include <stdio.h>
#include <sqlite3.h>
#include <iostream>

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
    delete []database_struct;
}

void AbstractSqliteModel::initialize_db() {
    char *error_message = 0;
    int connection;
    int i;

    std::string create_sql = "CREATE TABLE IF NOT EXISTS " +
                             (std::string)table_name +
                            "(id INT PRIMARY KEY  NOT NULL,";

    std::string insert_sql_columns = "id, ";
    std::string insert_sql_values  = std::to_string(id) + ", ";

    for (i = 0; i < table_size; i++) {
        create_sql += database_struct[i].column_name + " ";
        create_sql += database_struct[i].type + " ";
        create_sql += database_struct[i].null_status;

        insert_sql_columns += database_struct[i].column_name;
        insert_sql_values  += database_struct[i].default_value;

        if ((i + 1) < table_size) {
            create_sql         += ",";
            insert_sql_columns += ",";
            insert_sql_values  += ",";
        }
    }

    create_sql += ");";

    std::string insert_sql = "INSERT OR IGNORE INTO " + (std::string)table_name +
                             " (" + insert_sql_columns + ")" +
                             " VALUES (" + insert_sql_values + ");";

    connection = sqlite3_exec(connection_manager->get_db(), create_sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }

    connection = sqlite3_exec(connection_manager->get_db(), insert_sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}

void AbstractSqliteModel::update_single_int(const char *insert_column_name, const int &value) {
    char *error_message = 0;
    int connection;
    std::string sql = "UPDATE " + (std::string)table_name +
                      " SET " + (std::string)insert_column_name +
                      " = " + std::to_string(value) +
                      " WHERE id=" + std::to_string(id) + ";";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}

// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
