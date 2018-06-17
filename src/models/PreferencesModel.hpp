#ifndef PreferencesModel_hpp
#define PreferencesModel_hpp

#include <string>

#include "AbstractSqliteModel.hpp"


class PreferencesModel : public AbstractSqliteModel {
private:

public:
    PreferencesModel();
    PreferencesModel(const int &select_id);
    ~PreferencesModel();

    void setup();
    void abstract_set_value(const std::string &column_name, const std::string &value, bool update_db);

    // Getters and setters

    void set_window_width(const int &new_width, bool update_db);
    int const get_window_width() const {
        if (contents.find("window_width") != contents.end()) {
            return std::stoi(contents.at("window_width"));
        }

        return 1;
    }

    void set_window_height(const int &new_height, bool update_db);
    int const get_window_height() const {
        if (contents.find("window_width") != contents.end()) {
            return std::stoi(contents.at("window_height"));
        }

        return 1;
    }

    void set_window_maximized(const bool maximized, bool update_db);
    bool const get_window_maximized() const {
        if (contents.find("window_maximized") != contents.end()) {
            return std::stoi(contents.at("window_maximized")) == 1 ? true : false;
        }

        return false;
    }
};

#endif /* PreferencesModel_hpp */
