#include <string>
#include <vector>
#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../db/SqliteSchema.hpp"

const int default_window_width = 1000;
const int default_window_height = 700;


PreferencesModel::PreferencesModel() : AbstractSqliteModel(1) {
	setup();
}

PreferencesModel::PreferencesModel(const int &select_id) : AbstractSqliteModel(select_id) {
	setup();
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::setup() {
	table_schema = &SqliteSchema::preferences_table;

    select_one();

	if (get_window_width() == -1) {
		set_window_width(default_window_width, true);
	}

	if (get_window_height() == -1) {
		set_window_height(default_window_height, true);
	}
}


// Setters

void PreferencesModel::set_window_width(const int &new_width, bool update_db) {
    window_width = new_width;

    if (update_db) {
        update_single_int("window_width", window_width);
    }
}

void PreferencesModel::set_window_height(const int &new_height, bool update_db) {
    window_height = new_height;

    if (update_db) {
        update_single_int("window_height", window_height);
    }
}

void PreferencesModel::set_window_maximized(const bool new_maximized, bool update_db) {
    int int_value    = new_maximized ? 1 : 0;
    window_maximized = new_maximized;

    if (update_db) {
        update_single_int("window_maximized", int_value);
    }
}

void PreferencesModel::fill_model() {
    window_width     = std::stoi(contents["window_width"]);
    window_height    = std::stoi(contents["window_height"]);
    window_maximized = contents["window_maximized"] == "1" ? true : false;
}

void PreferencesModel::save_all() {
    contents["window_width"]     = std::to_string(window_width);
    contents["window_height"]    = std::to_string(window_height);
    contents["window_maximized"] = window_maximized ? "1" : "0";

    abstract_save_all();
}
