#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

class ProjectsView : public AbstractView {
private:
    GtkWidget *form_grid;

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
