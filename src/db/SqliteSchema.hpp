#ifndef SqliteSchema_hpp
#define SqliteSchema_hpp

class SqliteSchema {
private:
    SqliteSchema();

public:
    typedef struct {
        std::string column_name;
        std::string type;
        std::string null_status;
        std::string default_value;
    } ColumnSchema;

    typedef struct {
        std::string table_name;
        std::vector<ColumnSchema> columns;
        bool create_first_row;
    } TableSchema;

    static TableSchema preferences_table;
    static TableSchema projects_table;

    static std::vector<TableSchema> all_tables;

    static void setup_db();
};

#endif /* SqliteSchema_hpp */
