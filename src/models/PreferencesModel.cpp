#include <sqlite3.h>

#include "PreferencesModel.hpp"
#include "../SqliteConnectionManager.hpp"


PreferencesModel::PreferencesModel() {
    table_name = (char *)"PREFERENCES";
}

PreferencesModel::~PreferencesModel() {

}

void PreferencesModel::initialize() {
    char *error_message = 0;
    // char sql[] = { "CREATE TABLE ",
    //                table_name,
    //                "(",
    //                "ID INT PRIMARY  KEY     NOT NULL,",
    //                "WINDOW_WIDTH    INT    NOT NULL,",
    //                "WINDOW_HEIGHT   INT    NOT NULL,",
    //                ");",
    //              };
}
