#ifndef ProjectsModel_hpp
#define ProjectsModel_hpp

#include <string>

#include "AbstractSqliteModel.hpp"


class ProjectsModel : public AbstractSqliteModel {
private:

public:
    ProjectsModel();
    ProjectsModel(const int &select_id);
    ~ProjectsModel();

    void setup();

    // Getters and setters

    void set_name(const std::string name);
    std::string const get_name() const {
        if (contents.find("name") != contents.end()) {
            return contents.at("name");
        }

        return "";
    }

    void set_start_date(const std::string start_date);
    std::string const get_start_date() const {
        if (contents.find("start_date") != contents.end()) {
            return contents.at("start_date");
        }

        return "";
    }

    void set_end_date(const std::string end_date);
    std::string const get_end_date() const {
        if (contents.find("end_date") != contents.end()) {
            return contents.at("end_date");
        }

        return "";
    }

    void set_url(const std::string url);
    std::string const get_url() const {
        if (contents.find("url") != contents.end()) {
            return contents.at("url");
        }

        return "";
    }

    void set_notes(const std::string notes);
    std::string const get_notes() const {
        if (contents.find("notes") != contents.end()) {
            return contents.at("notes");
        }

        return "";
    }

    void set_is_complete(const bool maximized);
    bool const get_is_complete() const {
        if (contents.find("is_complete") != contents.end()) {
            return std::stoi(contents.at("is_complete")) == 1 ? true : false;
        }

        return false;
    }

    void set_date_completed(const std::string date_completed);
    std::string const get_date_completed() const {
        if (contents.find("date_completed") != contents.end()) {
            return contents.at("date_completed");
        }

        return "";
    }

    void set_date_created(const std::string date_created);
    std::string const get_date_created() const {
        if (contents.find("date_created") != contents.end()) {
            return contents.at("date_created");
        }

        return "";
    }
};

#endif /* ProjectsModel_hpp */
