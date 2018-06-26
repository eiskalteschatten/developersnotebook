#include <string>
#include <vector>
#include <regex>
#include <stdio.h>
#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../db/SqliteConnectionManager.hpp"


AbstractSqliteModel::AbstractSqliteModel() {
	id = 0;
}

AbstractSqliteModel::AbstractSqliteModel(const int &select_id) {
    id = select_id;
}

AbstractSqliteModel::~AbstractSqliteModel() {
}

void AbstractSqliteModel::insert_new_row() {
    try {
        SqliteConnectionManager connection_manager;
        char *error_message = 0;
        int connection;

        std::string insert_sql_columns;
        std::string insert_sql_values;
        std::vector<SqliteSchema::ColumnSchema> table_columns = table_schema->columns;

        for (unsigned int c = 0; c < table_columns.size(); c++) {
            insert_sql_columns += table_columns[c].column_name;
            insert_sql_values  += table_columns[c].default_value.empty() ? "\"\"" : "\"" + table_columns[c].default_value + "\"";

            if ((c + 1) < table_columns.size()) {
                insert_sql_columns += ",";
                insert_sql_values  += ",";
            }
        }

        std::string insert_sql = "INSERT INTO " + table_schema->table_name +
                                 " (" + insert_sql_columns + ")" +
                                 " VALUES (" + insert_sql_values + ");";

        connection = sqlite3_exec(connection_manager.get_db(), insert_sql.c_str(), NULL, 0, &error_message);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error_message);
            sqlite3_free(error_message);
        }

        id = sqlite3_last_insert_rowid(connection_manager.get_db());
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to save to the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::update_single(const std::string insert_column_name, const std::string &value) {
    try {
        if (!id) {
            insert_new_row();
        }

        SqliteConnectionManager connection_manager;

        char *error_message = 0;
        int connection;
        std::string sql = "UPDATE " + table_schema->table_name +
                          " SET " + (std::string)insert_column_name +
                          " = \"" + text_escape(value) + "\"" +
                          " WHERE id=" + std::to_string(id) + ";";

        connection = sqlite3_exec(connection_manager.get_db(), sql.c_str(), NULL, 0, &error_message);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error_message);
            sqlite3_free(error_message);
        }
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to save to the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::update_single_text(const std::string insert_column_name, const std::string &value) {
    update_single(insert_column_name, value);
}

void AbstractSqliteModel::update_single_int(const std::string insert_column_name, const int &value) {
    update_single(insert_column_name, std::to_string(value));
}

void AbstractSqliteModel::delete_single() {
    try {
        if (!id) {
            fprintf(stderr, "Could not delete the entry because there was no id!");
            return;
        }

        SqliteConnectionManager connection_manager;

        char *error_message = 0;
        int connection;
        std::string sql = "DELETE FROM " + table_schema->table_name +
                          " WHERE id=" + std::to_string(id) + ";";

        connection = sqlite3_exec(connection_manager.get_db(), sql.c_str(), NULL, 0, &error_message);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", error_message);
            sqlite3_free(error_message);
        }
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to delete from the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::select_query(std::string sql) {
    try {
        SqliteConnectionManager connection_manager;

        int connection;
        sqlite3_stmt *stmt;

        connection = sqlite3_prepare_v2(connection_manager.get_db(), sql.c_str(), -1, &stmt, NULL);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(connection_manager.get_db()));
        }

        while ((connection = sqlite3_step(stmt)) == SQLITE_ROW) {
            tableRowMap row;

            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                std::string column_name = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)));
                std::string column_text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                row[column_name]        = column_text;
            }

            full_table.push_back(row);
        }

        sqlite3_finalize(stmt);

        fill_model();
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to set up the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::select_one() {
    try {
        SqliteConnectionManager connection_manager;

        std::string sql = "SELECT * FROM " + table_schema->table_name + " WHERE ID=" + std::to_string(id) + ";";
        int connection;
        sqlite3_stmt *stmt;

        connection = sqlite3_prepare_v2(connection_manager.get_db(), sql.c_str(), -1, &stmt, NULL);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(connection_manager.get_db()));
        }

        while ((connection = sqlite3_step(stmt)) == SQLITE_ROW) {
            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                std::string column_name = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)));
                std::string column_text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                contents[column_name]   = column_text;
            }

            break; // We only want one row. There should only be one with the id, but just be sure.
        }

        sqlite3_finalize(stmt);

        fill_model();
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to set up the database: %s\n", e.what());
    }
}

void AbstractSqliteModel::select_all() {
    std::string sql = "SELECT * FROM " + table_schema->table_name + ";";
    select_query(sql);
}

void AbstractSqliteModel::abstract_save_all() {
    try {
        if (!id) {
            insert_new_row();
        }

        std::string set = "";

        for (auto const &column : contents) {
            set.append(column.first);
            set.append("=\"");
            set.append(text_escape(column.second));
            set.append("\",");
        }

        if (set != "") {
            set = set.substr(0, set.size()-1); // Remove the dangling comma

            SqliteConnectionManager connection_manager;

            char *error_message = 0;
            int connection;
            std::string sql = "UPDATE " + table_schema->table_name +
                              " SET " + set +
                              " WHERE id=" + std::to_string(id) + ";";

            connection = sqlite3_exec(connection_manager.get_db(), sql.c_str(), NULL, 0, &error_message);

            if(connection != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", error_message);
                sqlite3_free(error_message);
            }
        }
        else {
            fprintf(stderr, "There are no contents to save!");
        }
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to save to the database: %s\n", e.what());
    }
}

std::string AbstractSqliteModel::text_escape(std::string text) {
    return std::regex_replace(text, std::regex("\""), "\"\"");
}

// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
