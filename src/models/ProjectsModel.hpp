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
    std::string date_complete;
    std::string date_created;

    void fill_model();
    void abstract_set_value(const std::string &column_name, const std::string &value, bool update_db);

public:
    ProjectsModel();
    ProjectsModel(const int &select_id);
    ~ProjectsModel();

    void setup();
    void truncate_notes();

    // Getters and setters

    void set_name(const std::string name, bool update_db);
    std::string const get_name() const { return name; }

    void set_start_date(const std::string start_date, bool update_db);
    std::string const get_start_date() const { return start_date; }

    void set_end_date(const std::string end_date, bool update_db);
    std::string const get_end_date() const { return end_date; }

    void set_url(const std::string url, bool update_db);
    std::string const get_url() const { return url; }

    void set_notes(const std::string notes, bool update_db);
    std::string const get_notes() const { return notes; }

    void set_is_complete(const bool is_complete, bool update_db);
    bool const get_is_complete() const { return is_complete; }

    void set_date_completed(const std::string date_completed, bool update_db);
    std::string const get_date_completed() const { return date_complete; }

    void set_date_created(const std::string date_created, bool update_db);
    std::string const get_date_created() const { return date_created; }
};

#endif /* ProjectsModel_hpp */
