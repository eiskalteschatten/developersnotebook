#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include <string>

#include "../SqliteConnectionManager.hpp"

class AbstractSqliteModel {
protected:
    SqliteConnectionManager *connection_manager;

    struct DatabaseStruct {
        std::string column_name;
        std::string type;
        std::string null_status;
        std::string default_value;
    };

    DatabaseStruct *database_struct;
    short table_size;

    char *table_name;
    int id;

    void initialize_db();
    void update_single_int(const char *insert_column_name, const int &value);

public:
    AbstractSqliteModel();
    ~AbstractSqliteModel();


    // Getters and setters

    char *get_table_name() const {return table_name;}

    int const& get_id() const {return id;}
    void set_id(const int &new_id);
};

#endif /* AbstractSqliteModel_hpp */
