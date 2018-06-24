#ifndef MainWindow_hpp
#define MainWindow_hpp

#include "../views/DashboardView.hpp"
#include "../views/ProjectsView.hpp"


class MainWindow {
private:
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *stack;

    DashboardView *dashboard_view;
    ProjectsView *projects_view;

    void setup_grid();
    void setup_stack();
    static void save_window(GtkWidget *window, gpointer user_data);

public:
    MainWindow();
    ~MainWindow();

    static void activate(GtkApplication *app, MainWindow *mw);
    void switch_stack(const gchar *child_name);

    GtkWidget *get_window() { return window; }

    DashboardView *get_dashboard_view() { return dashboard_view; }
    ProjectsView *get_projects_view() { return projects_view; }
};

#endif /* MainWindow_hpp */
