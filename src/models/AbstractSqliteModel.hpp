#ifndef AbstractSqliteModel_hpp
#define AbstractSqliteModel_hpp

#include "../SqliteConnectionManager.hpp"

class AbstractSqliteModel {
private:
    SqliteConnectionManager *connection_manager;

    char *table_name;
    int id;

public:
    AbstractSqliteModel();
    ~AbstractSqliteModel();

    char *getTableName() const {return table_name;}

    int const& getId() const {return id;}
    void setId(const int &new_id);
};

#endif /* AbstractSqliteModel_hpp */
