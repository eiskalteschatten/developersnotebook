#include <string>
#include <vector>
#include <sqlite3.h>

#include "SqliteSchema.hpp"
#include "SqliteConnectionManager.hpp"

typedef struct {
    std::string column_name;
    std::string type;
    std::string null_status;
    std::string default_value;
} ColumnSchema;

typedef struct {
    std::string table_name;
    std::vector<ColumnSchema> columns;
} TableSchema;


const static TableSchema preferences_table {
    "preferences",
    {
        {"window_width", "INT", "NOT NULL", "-1"},
        {"window_height", "INT", "NOT NULL", "-1"},
        {"window_maximized", "INT", "NOT NULL", "0"}
    }
};


const static std::vector<TableSchema> all_tables {
	preferences_table
};


static int null_callback(void *data, int argc, char **argv, char **as_col_name) {
    return 0;
}

void SqliteSchema::setup_db() {
    SqliteConnectionManager *connection_manager;
    char *error_message = 0;
    int connection;
    unsigned int i;

    connection_manager = SqliteConnectionManager::get_instance();

    for (i = 0; i < all_tables.size(); i++) {
        TableSchema table = all_tables[i];
        std::vector<ColumnSchema> table_columns = table.columns;

        std::string create_sql = "CREATE TABLE IF NOT EXISTS " +
                                 table.table_name +
                                 "(id INT PRIMARY KEY  NOT NULL,";

        std::string insert_sql_columns = "id, ";
        std::string insert_sql_values  = "1, ";

        for (i = 0; i < table_columns.size(); i++) {
            create_sql += table_columns[i].column_name + " ";
            create_sql += table_columns[i].type + " ";
            create_sql += table_columns[i].null_status;

            insert_sql_columns += table_columns[i].column_name;
            insert_sql_values  += table_columns[i].default_value;

            if ((i + 1) < table_columns.size()) {
                create_sql         += ",";
                insert_sql_columns += ",";
                insert_sql_values  += ",";
            }
        }

        create_sql += ");";

        std::string insert_sql = "INSERT OR IGNORE INTO " + table.table_name +
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
}
