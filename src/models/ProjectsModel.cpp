#include <string>
#include <vector>
#include <regex>
#include <sqlite3.h>

#include "ProjectsModel.hpp"
#include "../db/SqliteSchema.hpp"


ProjectsModel::ProjectsModel() : AbstractSqliteModel() {
	setup();
}

ProjectsModel::ProjectsModel(const int &select_id) : AbstractSqliteModel(select_id) {
	setup();
}

ProjectsModel::ProjectsModel(const tableRowMap &new_contents) {
    contents = new_contents;
    fill_model();

    if (contents.find("id") != contents.end() && contents["id"] != "") {
        std::string fuckvs = contents["id"];
        id = std::stoi(contents["id"]);
    }

    setup();
}

ProjectsModel::~ProjectsModel() {

}

void ProjectsModel::setup() {
	table_schema = &SqliteSchema::projects_table;
}


// Setters

void ProjectsModel::set_name(const std::string new_name, bool update_db) {
    name = new_name;

    if (update_db) {
        update_single_text("name", name);
    }
}

void ProjectsModel::set_start_date(const std::string new_start_date, bool update_db) {
    start_date = new_start_date;

    if (update_db) {
        update_single_text("start_date", start_date);
    }
}

void ProjectsModel::set_end_date(const std::string new_end_date, bool update_db) {
    end_date = new_end_date;

    if (update_db) {
        update_single_text("end_date", end_date);
    }
}

void ProjectsModel::set_url(const std::string new_url, bool update_db) {
    url = new_url;

    if (update_db) {
        update_single_text("url", url);
    }
}

void ProjectsModel::set_notes(const std::string new_notes, bool update_db) {
    notes = new_notes;

    if (update_db) {
        update_single_text("notes", notes);
    }
}

void ProjectsModel::set_is_complete(const bool new_is_complete, bool update_db) {
    int int_value = new_is_complete ? 1 : 0;
    is_complete   = new_is_complete;

    if (update_db) {
        update_single_int("is_complete", int_value);
    }
}

void ProjectsModel::set_date_completed(const std::string new_date_completed, bool update_db) {
    date_completed = new_date_completed;

    if (update_db) {
        update_single_text("date_completed", date_completed);
    }
}

void ProjectsModel::set_date_created(const std::string new_date_created, bool update_db) {
    date_created = new_date_created;

    if (update_db) {
        update_single_text("date_created", date_created);
    }
}

void ProjectsModel::fill_model() {
    name           = contents["name"];
    start_date     = contents["start_date"];
    end_date       = contents["end_date"];
    url            = contents["url"];
    notes          = contents["notes"];
    is_complete    = contents["is_complete"] == "1" ? true : false;
    date_completed = contents["date_completed"];
    date_created   = contents["date_created"];
}

void ProjectsModel::save_all() {
    contents["name"]           = name;
    contents["start_date"]     = start_date;
    contents["end_date"]       = end_date;
    contents["url"]            = url;
    contents["notes"]          = notes;
    contents["is_complete"]    = is_complete ? "1" : "0";
    contents["date_completed"] = date_completed;
    contents["date_created"]   = date_created;

    abstract_save_all();
}

void ProjectsModel::truncate_notes() {
    notes = std::regex_replace(notes, std::regex("\\n"), " ");
    notes = std::regex_replace(notes, std::regex("\\r"), "");

    if (notes != "" && notes.length() >= 50) {
        notes = notes.substr(0, 47) + "...";
    }
}

void ProjectsModel::get_projects_ending_soon() {
    try {
        SqliteConnectionManager connection_manager;

        std::string sql = "SELECT * FROM " + table_schema->table_name +
                          " WHERE end_date IS NOT NULL";
                          " ORDER BY date(end_date) DESC;";
        int connection;
        sqlite3_stmt *stmt;

        connection = sqlite3_prepare_v2(connection_manager.get_db(), sql.c_str(), -1, &stmt, NULL);

        if(connection != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(connection_manager.get_db()));
        }

        while ((connection = sqlite3_step(stmt)) == SQLITE_ROW) {
            tableRowMap row;

            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                std::string column_name = std::string(reinterpret_cast<const char*>(sqlite3_column_name(stmt, i)));
                std::string column_text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                row[column_name]        = column_text;
            }

            full_table.push_back(row);
        }

        sqlite3_finalize(stmt);

        fill_model();
    }
    catch(const std::exception& e) {
        fprintf(stderr, "An exception occured while trying to set up the database: %s\n", e.what());
    }
}
