#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

class ProjectsView : public AbstractView {
private:
    GtkWidget *list_view;
    GtkWidget *form_grid;
    GtkListStore *list_store;

    void setup_list_store();
    void setup_list_view();

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
