#include <string>
#include <stdio.h>
#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../db/SqliteConnectionManager.hpp"


AbstractSqliteModel::AbstractSqliteModel() {
    AbstractSqliteModel(1);
}

AbstractSqliteModel::AbstractSqliteModel(const int &select_id) {
    id = select_id;
}

AbstractSqliteModel::~AbstractSqliteModel() {
    delete table_schema;
}

void AbstractSqliteModel::fill_contents() {
    try {
        SqliteConnectionManager *connection_manager = new SqliteConnectionManager();

        std::string sql = "SELECT * FROM " + table_schema->table_name + " WHERE ID=" + std::to_string(id) + ";";
        int connection;
        sqlite3_stmt *stmt;

        connection = sqlite3_prepare_v2(connection_manager->get_db(), sql.c_str(), -1, &stmt, NULL);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(connection_manager->get_db()));
        }

        while ((connection = sqlite3_step(stmt)) == SQLITE_ROW) {
            // i = 1 to skip the "id" column
            for (int i = 1; i < sqlite3_column_count(stmt); i++) {
                std::string column_name = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)));
                std::string column_text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                contents[column_name] = column_text;
            }

            break; // We only want one row. There should only be one with the id, but just be sure.
        }

        sqlite3_finalize(stmt);

        delete connection_manager;
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to set up the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::insert_new_row() {
    try {
        std::string insert_sql = "INSERT OR IGNORE INTO " + table_schema->table_name +
                                 " (" + insert_sql_columns + ")" +
                                 " VALUES (" + insert_sql_values + ");";

        connection = sqlite3_exec(connection_manager->get_db(), insert_sql.c_str(), NULL, 0, &error_message);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error_message);
            sqlite3_free(error_message);
        }
        delete connection_manager;
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to save to the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::update_single(const std::string insert_column_name, const std::string &value, bool update_contents) {
    try {
        SqliteConnectionManager *connection_manager = new SqliteConnectionManager();

        char *error_message = 0;
        int connection;
        std::string sql = "UPDATE " + table_schema->table_name +
                          " SET " + (std::string)insert_column_name +
                          " = " + value +
                          " WHERE id=" + std::to_string(id) + ";";

        connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), NULL, 0, &error_message);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error_message);
            sqlite3_free(error_message);
        }

        if (update_contents) {
            contents[insert_column_name] = value;
        }

        delete connection_manager;
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to save to the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::update_single_text(const std::string insert_column_name, const std::string &value, bool update_contents) {
    update_single(insert_column_name, value, update_contents);
}

void AbstractSqliteModel::update_single_int(const std::string insert_column_name, const int &value, bool update_contents) {
    update_single(insert_column_name, std::to_string(value), update_contents);

}


// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
