#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include <gtk/gtk.h>

class ProjectsView {
private:
    GtkWidget *main_widget;

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* ProjectsView_hpp */
