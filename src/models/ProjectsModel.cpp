#include <string>
#include <vector>
#include <sqlite3.h>

#include "ProjectsModel.hpp"
#include "../db/SqliteSchema.hpp"


ProjectsModel::ProjectsModel() : AbstractSqliteModel() {
	setup();
}

ProjectsModel::ProjectsModel(const int &select_id) : AbstractSqliteModel(select_id) {
	setup();
}

ProjectsModel::~ProjectsModel() {

}

void ProjectsModel::setup() {
	table_schema = &SqliteSchema::projects_table;
}


// Setters

void ProjectsModel::set_name(const std::string name) {
    update_single_text("name", name, true);
}

void ProjectsModel::set_start_date(const std::string start_date) {
    update_single_text("start_date", start_date, true);
}

void ProjectsModel::set_end_date(const std::string end_date) {
    update_single_text("end_date", end_date, true);
}

void ProjectsModel::set_url(const std::string url) {
    update_single_text("url", url, true);
}

void ProjectsModel::set_notes(const std::string notes) {
    update_single_text("notes", notes, true);
}

void ProjectsModel::set_is_complete(const bool is_complete) {
    int int_value = is_complete ? 1 : 0;
    update_single_int("is_complete", int_value, true);
}

void ProjectsModel::set_date_completed(const std::string date_completed) {
    update_single_text("date_completed", date_completed, true);
}

void ProjectsModel::set_date_created(const std::string date_created) {
    update_single_text("date_created", date_created, true);
}
