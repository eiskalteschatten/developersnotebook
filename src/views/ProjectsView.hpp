#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

typedef struct {
    const gchar *id;
    const gchar *name;
    const gchar *start_date;
    const gchar *end_date;
    const bool is_complete;
    const gchar *date_completed;
    const gchar *date_created;
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
    GtkWidget *save_button;

    friend void save_project(GtkWidget *widget, ProjectsView *pv);
    friend void list_selection_changed(GtkTreeSelection *selection, ProjectsView *pv);

    void setup_list_store();
    void setup_list_view();
    void append_to_list_store(GtkTreeIter *tree_iter);
    void prepend_to_list_store(GtkTreeIter *tree_iter);
    void set_list_store(const ProjectsRow &row, GtkTreeIter *tree_iter);
    void select_row_in_list_view(GtkTreeIter *tree_iter);
    void setup_form_sidebar();
    void fill_in_sidebar(const ProjectsRow &row);
    ProjectsRow convert_table_row_map_to_struct(const tableRowMap &map);

public:
    ProjectsView();
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
