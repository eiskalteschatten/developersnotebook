#include <sqlite3.h>

#include "AbstractSqliteModel.hpp"
#include "../SqliteConnectionManager.hpp"


AbstractSqliteModel::AbstractSqliteModel() {
    connection_manager = SqliteConnectionManager::getInstance();
}

AbstractSqliteModel::~AbstractSqliteModel() {
    delete connection_manager;
}

void AbstractSqliteModel::set_id(const int &new_id) {
    id = new_id;
}
