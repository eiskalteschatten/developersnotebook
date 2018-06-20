#ifndef ProjectsView_hpp
#define ProjectsView_hpp

#include "AbstractView.hpp"

typedef struct {
    const gchar *id;
    const gchar *name;
    const gchar *start_date;
    const gchar *end_date;
    const gchar *url;
    const gchar *notes;
    const bool is_complete;
    const gchar *date_completed;
    const gchar *date_created;

    void truncate_notes() {
        std::string notes_str = std::string(notes);
        notes_str             = std::regex_replace(notes_str, std::regex("\\n"), " ");
        notes_str             = std::regex_replace(notes_str, std::regex("\\r"), "");

        if (notes_str != "" && notes_str.length() >= 50) {
            notes_str = notes_str.substr(0, 47) + "...";
        }

        notes = notes_str.c_str();
    }
} ProjectsRow;


class ProjectsView : public AbstractView {
private:
    GtkWidget *list_view_grid;
    GtkWidget *list_scrolled_window;
    GtkWidget *list_view;
    GtkWidget *form_grid;
    GtkWidget *form_scrolled_window;
    GtkListStore *list_store;
    GtkTreeSelection *select;

    // Tree View Toolbar
    GtkWidget *toolbar_box;
    GtkWidget *new_toolbar_button;
    GtkWidget *delete_toolbar_button;

    // Form
    GtkWidget *project_name_input;
    GtkWidget *start_date_input;
    GtkWidget *start_date_clear_button;
    GtkWidget *end_date_input;
    GtkWidget *end_date_clear_button;
    GtkWidget *url_input;
    GtkWidget *notes_input;
    GtkWidget *is_complete_checkbox;
    GtkWidget *save_button;
    GtkWidget *delete_button;

    friend void save_project(GtkWidget *widget, ProjectsView *pv);
    friend void delete_project(GtkWidget *widget, ProjectsView *pv);
    friend void create_new_project(GtkWidget *widget, ProjectsView *pv);
    friend void list_selection_changed(GtkTreeSelection *selection, ProjectsView *pv);
    friend void clear_start_date_selection(GtkWidget *widget, ProjectsView *pv);
    friend void clear_end_date_selection(GtkWidget *widget, ProjectsView *pv);

    void setup_list_store();
    void setup_list_view();
    void setup_list_view_toolbar();
    void append_to_list_store(GtkTreeIter *tree_iter);
    void prepend_to_list_store(GtkTreeIter *tree_iter);
    void remove_from_list_store(GtkTreeIter *tree_iter);
    void set_list_store(const ProjectsRow &row, GtkTreeIter *tree_iter);
    void select_row_in_list_view(GtkTreeIter *tree_iter);
    void setup_form_sidebar();
    void empty_sidebar();
    void fill_in_sidebar(const ProjectsRow &row);
    ProjectsRow convert_table_row_map_to_struct(const tableRowMap &map);

public:
    ProjectsView(GtkWidget *window);
    ~ProjectsView();

    GtkWidget *get_list_view() {return list_view;}
    GtkWidget *get_form_grid() {return form_grid;}
};

#endif /* ProjectsView_hpp */
