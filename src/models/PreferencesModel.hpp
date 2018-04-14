#ifndef PreferencesModel_hpp
#define PreferencesModel_hpp

#include "AbstractSqliteModel.hpp"

class PreferencesModel : public AbstractSqliteModel {

friend int select_callback(void *data, int argc, char **argv, char **azColName);

private:
    void initialize();

    int window_width;
    int window_height;
    bool window_maximized;

public:
    PreferencesModel();
    PreferencesModel(int &select_id);
    ~PreferencesModel();

    // Getters and setters

    int const& get_window_width() const {return window_width;}
    void set_window_width(const int &new_width);

    int const& get_window_height() const {return window_height;}
    void set_window_height(const int &new_height);

    bool const get_window_maximized() const {return window_maximized;}
    void set_window_maximized(const bool maximized);
};

#endif /* PreferencesModel_hpp */
