#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

class ProjectsView : public AbstractView {
private:
    GtkWidget *list_view = nullptr;
    GtkWidget *form_grid = nullptr;
    GtkListStore *list_store = nullptr;

    void setup_list_store();
    void setup_list_view();
    void setup_form_sidebar();
    static void save_project(GtkWidget *widget, gpointer data);

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
