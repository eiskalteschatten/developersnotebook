#ifndef PreferencesModel_hpp
#define PreferencesModel_hpp

#include <string>

#include "AbstractSqliteModel.hpp"


class PreferencesModel : public AbstractSqliteModel {
private:
    int window_width;
    int window_height;
    bool window_maximized;

    void fill_model();

public:
    PreferencesModel();
    PreferencesModel(const int &select_id);
    ~PreferencesModel();

    void setup();
    void abstract_set_value(const std::string &column_name, const std::string &value, bool update_db);

    // Getters and setters

    void set_window_width(const int &new_width, bool update_db);
    int const get_window_width() const { return window_width; }

    void set_window_height(const int &new_height, bool update_db);
    int const get_window_height() const { return window_height; }

    void set_window_maximized(const bool maximized, bool update_db);
    bool const get_window_maximized() const { return window_maximized; }
};

#endif /* PreferencesModel_hpp */
