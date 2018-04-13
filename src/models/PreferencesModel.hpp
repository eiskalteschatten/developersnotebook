#ifndef PreferencesModel_hpp
#define PreferencesModel_hpp

#include "AbstractSqliteModel.hpp"

class PreferencesModel : public AbstractSqliteModel {
private:
    void initialize();

    int window_width;
    int window_height;

public:
    PreferencesModel();
    ~PreferencesModel();

    // Getters and setters

    int const& get_window_width() const {return window_width;}
    void set_window_width(const int &new_width);

    int const& get_window_height() const {return window_height;}
    void set_window_height(const int &new_height);
};

#endif /* PreferencesModel_hpp */
