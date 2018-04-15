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

    // Getters and setters

    int const get_window_width() const {return std::stoi(contents.at("window_width"));}
    void set_window_width(const int &new_width);

    int const get_window_height() const {return std::stoi(contents.at("window_height"));}
    void set_window_height(const int &new_height);

    bool const get_window_maximized() const {return std::stoi(contents.at("window_maximized")) == 1 ? true : false;}
    void set_window_maximized(const bool maximized);
};

#endif /* PreferencesModel_hpp */
