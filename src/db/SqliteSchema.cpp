#include <string>
#include <vector>
#include <sqlite3.h>

#include "SqliteSchema.hpp"
#include "SqliteConnectionManager.hpp"


SqliteSchema::TableSchema SqliteSchema::preferences_table {
    "preferences",
    {
        {"window_width", "INT", "NOT NULL", "-1"},
        {"window_height", "INT", "NOT NULL", "-1"},
        {"window_maximized", "INT", "NOT NULL", "0"}
    },
    true
};

SqliteSchema::TableSchema SqliteSchema::projects_table {
    "projects",
    {
        {"name", "TEXT", "NULL", ""},
        {"start_date", "TEXT", "NULL", ""},
        {"end_date", "TEXT", "NULL", ""},
        {"url", "TEXT", "NULL", ""},
        {"notes", "TEXT", "NULL", ""},
        {"is_complete", "INT", "NULL", "0"},
        {"date_completed", "TEXT", "NULL", ""},
        {"date_created", "TEXT", "NULL", ""}
    },
    false
};

std::vector<SqliteSchema::TableSchema> SqliteSchema::all_tables {
	SqliteSchema::preferences_table,
    SqliteSchema::projects_table
};


void SqliteSchema::setup_db() {
    try {
        SqliteConnectionManager connection_manager;
        char *error_message = 0;
        int connection;

        for (unsigned int i = 0; i < SqliteSchema::all_tables.size(); i++) {
            SqliteSchema::TableSchema table = SqliteSchema::all_tables[i];
            std::vector<SqliteSchema::ColumnSchema> table_columns = table.columns;

            std::string create_sql = "CREATE TABLE IF NOT EXISTS " +
                                     table.table_name +
                                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,";

            std::string insert_sql_columns = "id, ";
            std::string insert_sql_values  = "1, ";

            for (unsigned int c = 0; c < table_columns.size(); c++) {
                create_sql += table_columns[c].column_name + " ";
                create_sql += table_columns[c].type + " ";
                create_sql += table_columns[c].null_status;

                if (table.create_first_row) {
                    insert_sql_columns += table_columns[c].column_name;
                    insert_sql_values  += table_columns[c].default_value;
                }

                if ((c + 1) < table_columns.size()) {
                    create_sql         += ",";

                    if (table.create_first_row) {
                        insert_sql_columns += ",";
                        insert_sql_values  += ",";
                    }
                }
            }

            create_sql += ");";

            connection = sqlite3_exec(connection_manager.get_db(), create_sql.c_str(), NULL, 0, &error_message);

            if(connection != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", error_message);
                sqlite3_free(error_message);
            }

            if (table.create_first_row) {
                std::string insert_sql = "INSERT OR IGNORE INTO " + table.table_name +
                                         " (" + insert_sql_columns + ")" +
                                         " VALUES (" + insert_sql_values + ");";

                connection = sqlite3_exec(connection_manager.get_db(), insert_sql.c_str(), NULL, 0, &error_message);

                if(connection != SQLITE_OK) {
                    fprintf(stderr, "SQL error: %s\n", error_message);
                    sqlite3_free(error_message);
                }
            }
        }
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to set up the database: %s\n", e.what());
    }
}
