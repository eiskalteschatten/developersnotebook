#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include <string>

#include "../SqliteConnectionManager.hpp"

class AbstractSqliteModel {
protected:
    SqliteConnectionManager *connection_manager;

    char *table_name;
    int id;

public:
    AbstractSqliteModel();
    ~AbstractSqliteModel();

    int execute_sql(std::string &sql);


    // Getters and setters

    char *get_table_name() const {return table_name;}

    int const& get_id() const {return id;}
    void set_id(const int &new_id);
};

#endif /* AbstractSqliteModel_hpp */
