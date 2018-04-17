#include <string>
#include <vector>
#include <sqlite3.h>

#include "ProjectModel.hpp"
#include "../db/SqliteSchema.hpp"

const int default_window_width = 1000;
const int default_window_height = 700;


ProjectModel::ProjectModel() : AbstractSqliteModel(1) {
	setup();
}

ProjectModel::ProjectModel(const int &select_id) : AbstractSqliteModel(select_id) {
	setup();
}

ProjectModel::~ProjectModel() {

}

void ProjectModel::setup() {
	table_schema = &SqliteSchema::preferences_table;

	fill_contents();

	if (get_window_width() == -1) {
		set_window_width(default_window_width);
	}

	if (get_window_height() == -1) {
		set_window_height(default_window_height);
	}
}


// Setters

void ProjectModel::set_window_width(const int &width) {
    update_single_int("window_width", width, true);
}

void ProjectModel::set_window_height(const int &height) {
    update_single_int("window_height", height, true);
}

void ProjectModel::set_window_maximized(const bool maximized) {
    int int_value = maximized ? 1 : 0;
    update_single_int("window_maximized", int_value, true);
}
