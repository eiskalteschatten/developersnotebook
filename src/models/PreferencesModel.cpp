#include <string>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"


PreferencesModel::PreferencesModel() {
    table_name = (char *)"PREFERENCES";
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::initialize() {
    char *error_message = 0;
    std::string sql = "CREATE TABLE " + (std::string)table_name + "(" +
                      "ID INT PRIMARY  KEY     NOT NULL," +
                      "WINDOW_WIDTH    INT    NOT NULL," +
                      "WINDOW_HEIGHT   INT    NOT NULL," +
                      ");";
}


// Setters

void PreferencesModel::set_window_width(const int &new_width) {
    window_width = new_width;
}

void PreferencesModel::set_window_height(const int &new_height) {
    window_height = new_height;
}
