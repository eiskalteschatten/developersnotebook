#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include <string>
#include <vector>
#include <map>

#include "../db/SqliteConnectionManager.hpp"
#include "../db/SqliteSchema.hpp"


class AbstractSqliteModel {
protected:
    SqliteSchema::TableSchema *table_schema;

    std::map<std::string, std::string> contents;

    int id;

    void fill_contents();
    void update_single(const std::string insert_column_name, const std::string &value, bool update_contents);
    void update_single_text(const std::string insert_column_name, const std::string &value, bool update_contents);
    void update_single_int(const std::string insert_column_name, const int &value, bool update_contents);

public:
    AbstractSqliteModel();
    AbstractSqliteModel(const int &select_id);
    ~AbstractSqliteModel();

    void insert_new_row();

    // Getters and setters

    int const& get_id() const {return id;}
    void set_id(const int &new_id);
};

#endif /* AbstractSqliteModel_hpp */
