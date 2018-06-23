#ifndef MainWindow_hpp
#define MainWindow_hpp

#include "../views/DashboardView.hpp"
#include "../views/ProjectsView.hpp"


class MainWindow {
private:
    GtkWidget *window;
    GtkWidget *grid;

    GtkWidget *stack;
    GtkWidget *dashboard_view_widget;
    GtkWidget *projects_view_widget;

    DashboardView *dashboard_view;
    ProjectsView *projects_view;

    void setup_grid();
    void setup_stack();
    static void save_window(GtkWidget *window, gpointer user_data);

public:
    MainWindow();
    ~MainWindow();

    static void activate(GtkApplication *app, MainWindow *mw);

    GtkWidget *get_window() { return window; }
    GtkWidget *get_stack() { return stack; }
    GtkWidget *get_dashboard_view_widget() { return dashboard_view_widget; }
    GtkWidget *get_projects_view_widget() { return projects_view_widget; }

    DashboardView *get_dashboard_view() { return dashboard_view; }
    ProjectsView *get_projects_view() { return projects_view; }
};

#endif /* MainWindow_hpp */
