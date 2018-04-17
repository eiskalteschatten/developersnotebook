#include <string>
#include <vector>
#include <sqlite3.h>

#include "ProjectModel.hpp"
#include "../db/SqliteSchema.hpp"


ProjectModel::ProjectModel() : AbstractSqliteModel(1) {
	setup();
}

ProjectModel::ProjectModel(const int &select_id) : AbstractSqliteModel(select_id) {
	setup();
}

ProjectModel::~ProjectModel() {

}

void ProjectModel::setup() {
	table_schema = &SqliteSchema::projects_table;
	fill_contents();
}


// Setters

void ProjectModel::set_name(const std::string name) {
    update_single_text("name", name, true);
}

void ProjectModel::set_start_date(const std::string start_date) {
    update_single_text("start_date", start_date, true);
}

void ProjectModel::set_end_date(const std::string end_date) {
    update_single_text("end_date", end_date, true);
}

void ProjectModel::set_is_complete(const bool is_complete) {
    int int_value = is_complete ? 1 : 0;
    update_single_int("is_complete", int_value, true);
}

void ProjectModel::set_date_completed(const std::string date_completed) {
    update_single_text("date_completed", date_completed, true);
}

void ProjectModel::set_date_created(const std::string date_created) {
    update_single_text("date_created", date_created, true);
}
