#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

typedef struct {
    gchar *id;
    gchar *name;
    gchar *start_date;
    gchar *end_date;
    bool is_complete;
    gchar *date_completed;
    gchar *date_created;
} ProjectsRow;


class ProjectsView : public AbstractView {
private:
    GtkWidget *list_view;
    GtkWidget *form_grid;
    GtkListStore *list_store;
    GtkTreeSelection *select;

    // Form
    GtkWidget *project_name_input;
    GtkWidget *start_date_input;
    GtkWidget *end_date_input;
    GtkWidget *is_complete_checkbox;

    friend void save_project(GtkWidget *widget, ProjectsView *pv);
    friend void list_selection_changed(GtkTreeSelection *selection, gpointer data, ProjectsView *pv);

    void setup_list_store();
    void setup_list_view();
    void append_to_list_store(GtkTreeIter *tree_iter);
    void prepend_to_list_store(GtkTreeIter *tree_iter);
    void set_list_store(const tableRowMap &row, GtkTreeIter *tree_iter);
    void select_row_in_list_view(GtkTreeIter *tree_iter);
    void setup_form_sidebar();
    void fill_in_sidebar(const ProjectsRow &row);

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
