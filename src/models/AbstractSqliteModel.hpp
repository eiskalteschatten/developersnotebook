#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include <string>
#include <vector>

#include "../db/SqliteConnectionManager.hpp"
#include "../db/SqliteSchema.hpp"


class AbstractSqliteModel {
protected:
    SqliteConnectionManager *connection_manager;
    SqliteSchema::TableSchema *table_schema;

    int id;

    void update_single_int(const char *insert_column_name, const int &value);

public:
    AbstractSqliteModel();
    ~AbstractSqliteModel();


    // Getters and setters

    int const& get_id() const {return id;}
    void set_id(const int &new_id);
};

#endif /* AbstractSqliteModel_hpp */
