#ifndef DashboardView_hpp
#define DashboardView_hpp

#include <string>

#include "AbstractView.hpp"

class DashboardView : public AbstractView {
private:
    GtkWidget *projects_ending_soon_tree_view;
    GtkWidget *projects_ending_soon_scrolled_window;
    GtkListStore *projects_ending_soon_list_store;

    friend void project_ending_soon_update(GtkWidget *widget, DashboardView *dv);
    friend void projects_ending_soon_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, DashboardView *dv);

    void setup_projects_ending_soon();
    void fill_projects_ending_soon();

public:
    DashboardView();
    ~DashboardView();
};

#endif /* DashboardView_hpp */
