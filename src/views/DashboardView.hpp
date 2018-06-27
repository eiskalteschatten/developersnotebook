#ifndef DashboardView_hpp
#define DashboardView_hpp

#include <string>

#include "AbstractView.hpp"

class DashboardView : public AbstractView {
private:
    GtkWidget *projects_ending_soon_tree_view;
    GtkWidget *projects_ending_soon_scrolled_window;
    GtkListStore *projects_ending_soon_list_store;

    friend void projects_ending_soon_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, DashboardView *dv);

    void setup_projects_ending_soon();
    void fill_projects_ending_soon();

public:
    DashboardView();
    ~DashboardView();

    void refresh_all_sub_views();
};

#endif /* DashboardView_hpp */
