#include <string>
#include <cstring>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"

const int default_window_width = 1000;
const int default_window_height = 700;


static int null_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int select_callback(void *data, int argc, char **argv, char **azColName) {
    int i;

    if (PreferencesModel* const pm = static_cast<PreferencesModel*>(data)) {
        for(i = 0; i<argc; i++){
            if (strcmp(azColName[i], "window_width") == 0) {
                pm->window_width = argv[i] ? atoi(argv[i]) : default_window_width;
            }
            else if (strcmp(azColName[i], "window_height") == 0) {
                pm->window_height = argv[i] ? atoi(argv[i]) : default_window_height;
            }
        }
    }

    return 0;
}

PreferencesModel::PreferencesModel() {
    char *error_message = 0;
    int connection;

    id = 1; // id is 1 because there is only ever 1 row
    table_name = (char *)"preferences";
    window_height = 12;

    initialize();

    std::string sql = "SELECT * FROM " + (std::string)table_name + " WHERE ID=" + std::to_string(id) + ";";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), &select_callback, static_cast<PreferencesModel*>(this), &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::initialize() {
    char *error_message = 0;
    int connection;
    std::string sql = "CREATE TABLE IF NOT EXISTS " + (std::string)table_name + "(" +
                      "id INT PRIMARY  KEY  NOT NULL," +
                      "window_width    INT  NOT NULL," +
                      "window_height   INT  NOT NULL" +
                      ");";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }

    sql = "INSERT OR IGNORE INTO " + (std::string)table_name +
          " (id, window_width, window_height)" +
          " VALUES (" +
          std::to_string(id) + ", " +
          std::to_string(default_window_width) + ", " +
          std::to_string(default_window_height) +
          ");";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), null_callback, 0, &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}


// Setters

void PreferencesModel::set_window_width(const int &new_width) {
    window_width = new_width;
    update_single_int("window_width", window_width);
}

void PreferencesModel::set_window_height(const int &new_height) {
    window_height = new_height;
    update_single_int("window_height", window_height);
}
