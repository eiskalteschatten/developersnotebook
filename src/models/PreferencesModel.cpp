#include <string>
#include <cstring>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"

const int default_window_width = 1000;
const int default_window_height = 700;


int select_callback(void *data, int argc, char **argv, char **as_col_name) {
    int i;

    if (PreferencesModel* const preferences_model = static_cast<PreferencesModel*>(data)) {
        for(i = 0; i<argc; i++){
            if (strcmp(as_col_name[i], "window_width") == 0) {
                preferences_model->window_width = argv[i] ? atoi(argv[i]) : default_window_width;
            }
            else if (strcmp(as_col_name[i], "window_height") == 0) {
                preferences_model->window_height = argv[i] ? atoi(argv[i]) : default_window_height;
            }
            else if (strcmp(as_col_name[i], "window_maximized") == 0) {
                preferences_model->window_maximized = (argv[i] && atoi(argv[i]) == 1) ? true : false;
            }
        }
    }

    return 0;
}

PreferencesModel::PreferencesModel() {
    char *error_message = 0;
    int connection;

    id         = 1; // id is 1 because there is only ever 1 row
    table_name = (char *)"preferences";
    table_size = 3;

    database_struct = new DatabaseStruct[table_size];
    database_struct[0] = {"window_width", "INT", "NOT NULL", std::to_string(default_window_width)};
    database_struct[1] = {"window_height", "INT", "NOT NULL", std::to_string(default_window_height)};
    database_struct[2] = {"window_maximized", "INT", "NOT NULL", "0"};

    initialize_db();

    std::string sql = "SELECT * FROM " + (std::string)table_name + " WHERE ID=" + std::to_string(id) + ";";

    connection = sqlite3_exec(connection_manager->get_db(), sql.c_str(), &select_callback, static_cast<PreferencesModel*>(this), &error_message);

    if(connection != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message);
    }
}

PreferencesModel::~PreferencesModel() {

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

void PreferencesModel::set_window_maximized(const bool maximized) {
    window_maximized = maximized;
    int int_value = window_maximized ? 1 : 0;
    update_single_int("window_maximized", int_value);
}
