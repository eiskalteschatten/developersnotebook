#ifndef MainWindow_hpp
#define MainWindow_hpp

#include "../views/DashboardView.hpp"
#include "../views/ProjectsView.hpp"


class MainWindow {
private:
    std::string path_to_exec;

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *stack;

    DashboardView *dashboard_view;
    ProjectsView *projects_view;

    friend void refresh_all_sub_views(GtkWidget *stack, GdkEvent *event, MainWindow *mw);

    void setup_grid();
    void setup_stack();

public:
    MainWindow(std::string path);
    ~MainWindow();

    static void activate(GtkApplication *app, MainWindow *mw);
    static void save_and_close_window(GtkWidget *window);
    void switch_stack(const gchar *child_name);

    std::string const& get_path_to_exec() const { return path_to_exec; }

    GtkWidget *get_window() { return window; }

    DashboardView *get_dashboard_view() { return dashboard_view; }
    ProjectsView *get_projects_view() { return projects_view; }
    GtkWidget *get_stack() { return stack; }
};

#endif /* MainWindow_hpp */
