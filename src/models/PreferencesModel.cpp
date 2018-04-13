#include <string>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"


static int create_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

PreferencesModel::PreferencesModel() {
    table_name = (char *)"preferences";
    window_width = 1000;
    window_height = 700;

    initialize();
}

PreferencesModel::PreferencesModel(int &select_id) {
    table_name = (char *)"preferences";
    window_width = 1000;
    window_height = 700;

    initialize();
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::initialize() {
    char *error_message = 0;
    int connection;
    std::string sql = "CREATE TABLE IF NOT EXISTS " + (std::string)table_name + "(" +
                      "ID INT PRIMARY  KEY     NOT NULL," +
                      "WINDOW_WIDTH    INT    NOT NULL," +
                      "WINDOW_HEIGHT   INT    NOT NULL" +
                      ");";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), create_callback, 0, &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}


// Setters

void PreferencesModel::set_window_width(const int &new_width) {
    window_width = new_width;
}

void PreferencesModel::set_window_height(const int &new_height) {
    window_height = new_height;
}
