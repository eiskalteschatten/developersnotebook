#include <string>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"


PreferencesModel::PreferencesModel() {
    table_name = (char *)"PREFERENCES";
    window_width = 1000;
    window_height = 700;

    initialize();
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::initialize() {
    std::string sql = "CREATE TABLE IF NOT EXISTS " + (std::string)table_name + "(" +
                      "ID INT PRIMARY  KEY     NOT NULL," +
                      "WINDOW_WIDTH    INT    NOT NULL," +
                      "WINDOW_HEIGHT   INT    NOT NULL," +
                      ");";

    execute_sql(sql);
}


// Setters

void PreferencesModel::set_window_width(const int &new_width) {
    window_width = new_width;
}

void PreferencesModel::set_window_height(const int &new_height) {
    window_height = new_height;
}
