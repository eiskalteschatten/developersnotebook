#ifndef ProjectsModel_hpp
#define ProjectsModel_hpp

#include <string>

#include "AbstractSqliteModel.hpp"


class ProjectsModel : public AbstractSqliteModel {
private:
    std::string name;
    std::string start_date;
    std::string end_date;
    std::string url;
    std::string notes;
    bool is_complete;
    std::string date_completed;
    std::string date_created;

    void fill_model();

public:
    ProjectsModel();
    ProjectsModel(const int &select_id);
    ~ProjectsModel();

    void setup();
    void save_all();
    void truncate_notes();

    // Getters and setters

    void set_name(const std::string new_name, bool update_db);
    std::string const get_name() const { return name; }

    void set_start_date(const std::string new_start_date, bool update_db);
    std::string const get_start_date() const { return start_date; }

    void set_end_date(const std::string new_end_date, bool update_db);
    std::string const get_end_date() const { return end_date; }

    void set_url(const std::string new_url, bool update_db);
    std::string const get_url() const { return url; }

    void set_notes(const std::string new_notes, bool update_db);
    std::string const get_notes() const { return notes; }

    void set_is_complete(const bool new_is_complete, bool update_db);
    bool const get_is_complete() const { return is_complete; }

    void set_date_completed(const std::string new_date_completed, bool update_db);
    std::string const get_date_completed() const { return date_completed; }

    void set_date_created(const std::string new_date_created, bool update_db);
    std::string const get_date_created() const { return date_created; }
};

#endif /* ProjectsModel_hpp */
