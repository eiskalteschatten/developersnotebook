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

void ProjectsModel::set_name(const std::string name, bool update_db) {
    abstract_set_value("name", name, update_db);
}

void ProjectsModel::set_start_date(const std::string start_date, bool update_db) {
    abstract_set_value("start_date", start_date, update_db);
}

void ProjectsModel::set_end_date(const std::string end_date, bool update_db) {
    abstract_set_value("end_date", end_date, update_db);
}

void ProjectsModel::set_url(const std::string url, bool update_db) {
    abstract_set_value("url", url, update_db);
}

void ProjectsModel::set_notes(const std::string notes, bool update_db) {
    abstract_set_value("notes", notes, update_db);
}

void ProjectsModel::set_is_complete(const bool is_complete, bool update_db) {
    int int_value = is_complete ? 1 : 0;
    abstract_set_value("is_complete", std::to_string(int_value), update_db);
}

void ProjectsModel::set_date_completed(const std::string date_completed, bool update_db) {
    abstract_set_value("date_completed", date_completed, update_db);
}

void ProjectsModel::set_date_created(const std::string date_created, bool update_db) {
    abstract_set_value("date_created", date_created, update_db);
}

void ProjectsModel::abstract_set_value(const std::string &column_name, const std::string &value, bool update_db) {
    if (update_db) {
        update_single_text(column_name, value, true);
    }
    else {
        contents[column_name] = value;
    }
}
