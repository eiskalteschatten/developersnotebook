#include <stdio.h>
#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../SqliteConnectionManager.hpp"


AbstractSqliteModel::AbstractSqliteModel() {
    connection_manager = SqliteConnectionManager::get_instance();
}

AbstractSqliteModel::~AbstractSqliteModel() {
    delete connection_manager;
    delete table_name;
}


// Setters

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
