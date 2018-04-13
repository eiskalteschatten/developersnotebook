#include <string>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"


static int create_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

static int select_callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

PreferencesModel::PreferencesModel() {
    char *error_message = 0;
    int connection;

    id = 1; // id is 1 because there is only ever 1 row
    table_name = (char *)"preferences";
    window_width = 1000;
    window_height = 700;

    initialize();

    std::string sql = "SELECT * FROM " + (std::string)table_name + " WHERE ID=" + std::to_string(id) + ";";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), select_callback, 0, &error_message);

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
