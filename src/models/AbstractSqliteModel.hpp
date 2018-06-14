#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include <string>
#include <vector>
#include <map>

#include "../db/SqliteConnectionManager.hpp"
#include "../db/SqliteSchema.hpp"

typedef std::map<std::string, std::string> tableRowMap;
typedef std::vector<tableRowMap> tableVector;


class AbstractSqliteModel {
protected:
    SqliteSchema::TableSchema *table_schema;

    tableRowMap contents;
    tableVector full_table;

    int id;

    void insert_new_row();
    void update_single(const std::string insert_column_name, const std::string &value, bool update_contents);
    void update_single_text(const std::string insert_column_name, const std::string &value, bool update_contents);
    void update_single_int(const std::string insert_column_name, const int &value, bool update_contents);

public:
    AbstractSqliteModel();
    AbstractSqliteModel(const int &select_id);
    ~AbstractSqliteModel();

    void delete_single();
    void select_one();
    tableVector const& select_all();

    // Getters and setters

    int const& get_id() const {return id;}
    void set_id(const int &new_id);

    tableRowMap const& get_contents() const {return contents;}
    tableVector const& get_full_table() const {return full_table;}
};

#endif /* AbstractSqliteModel_hpp */
