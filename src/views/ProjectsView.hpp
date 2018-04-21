#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

class ProjectsView : public AbstractView {


private:
    GtkWidget *list_view;
    GtkWidget *form_grid;
    GtkListStore *list_store;

    // Form
    GtkWidget *project_name_input;
    GtkWidget *start_date_input;
    GtkWidget *end_date_input;
    GtkWidget *is_complete_checkbox;

    friend void save_project(GtkWidget *widget, ProjectsView *pv);

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
