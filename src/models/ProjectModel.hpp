#ifndef ProjectModel_hpp
#define ProjectModel_hpp

#include <string>

#include "AbstractSqliteModel.hpp"


class ProjectModel : public AbstractSqliteModel {
private:

public:
    ProjectModel();
    ProjectModel(const int &select_id);
    ~ProjectModel();

    void setup();

    // Getters and setters

    void set_window_width(const int &new_width);
    int const get_window_width() const {
        if (contents.find("window_width") != contents.end()) {
            return std::stoi(contents.at("window_width"));
        }

        return 1;
    }

    void set_window_height(const int &new_height);
    int const get_window_height() const {
        if (contents.find("window_width") != contents.end()) {
            return std::stoi(contents.at("window_height"));
        }

        return 1;
    }

    void set_window_maximized(const bool maximized);
    bool const get_window_maximized() const {
        if (contents.find("window_maximized") != contents.end()) {
            return std::stoi(contents.at("window_maximized")) == 1 ? true : false;
        }

        return false;
    }
};

#endif /* ProjectModel_hpp */
