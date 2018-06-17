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

void PreferencesModel::set_window_width(const int &width, bool update_db) {
    abstract_set_value("window_width", std::to_string(width), update_db);
}

void PreferencesModel::set_window_height(const int &height, bool update_db) {
    abstract_set_value("window_height", std::to_string(height), update_db);
}

void PreferencesModel::set_window_maximized(const bool maximized, bool update_db) {
    int int_value = maximized ? 1 : 0;
    abstract_set_value("window_maximized", std::to_string(int_value), update_db);
}

void PreferencesModel::abstract_set_value(const std::string &column_name, const std::string &value, bool update_db) {
    if (update_db) {
        update_single_text(column_name, value, true);
    }
    else {
        contents[column_name] = value;
    }
}
