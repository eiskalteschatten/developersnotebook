#include <cstring>
#include <gtk/gtk.h>

#include "MainWindow.hpp"
#include "MenuBar.hpp"
#include "../constants.hpp"
#include "../views/DashboardView.hpp"
#include "../views/ProjectsView.hpp"
#include "../models/PreferencesModel.hpp"


// Friends

void refresh_all_sub_views(GtkWidget *stack, GdkEvent *event, MainWindow *mw) {
    const gchar *stack_child_name = gtk_stack_get_visible_child_name(GTK_STACK(stack));

    if (strcmp(stack_child_name, "dashboard") == 0) {
        mw->get_dashboard_view()->refresh_all_sub_views();
    }
}


// Class

MainWindow::MainWindow() {

}

MainWindow::~MainWindow() {
    g_free(window);
    g_free(grid);
}

void MainWindow::activate(GtkApplication *app, MainWindow *mw) {
    PreferencesModel *preferences_model = new PreferencesModel();
    int window_width                    = preferences_model->get_window_width();
    int window_height                   = preferences_model->get_window_height();
    bool window_maximized               = preferences_model->get_window_maximized();

    mw->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(mw->window), Constants::application_name.c_str());
    gtk_window_set_position(GTK_WINDOW(mw->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(mw->window), window_width, window_height);

    #ifndef __APPLE__
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        const char *icon_path = std::strcat(cwd, Constants::application_icon_path.c_str());
        gtk_window_set_icon_from_file(GTK_WINDOW(mw->window), icon_path, NULL);
    #endif

    if (window_maximized) {
        gtk_window_maximize(GTK_WINDOW(mw->window));
    }

    mw->setup_grid();
    mw->setup_stack();

    MenuBar *menubar_obj = new MenuBar(mw);
    GtkWidget *menubar   = menubar_obj->get_menu_bar();
    gtk_grid_attach(GTK_GRID(mw->grid), menubar, 0, 0, 2, 1);

    gtk_widget_show_all(mw->window);

    menubar_obj->setup_macos_menu_bar();

    g_signal_connect(mw->window, "delete_event", G_CALLBACK(mw->save_and_close_window), NULL);
}

void MainWindow::setup_grid() {
    grid = gtk_grid_new();

    gtk_grid_insert_row(GTK_GRID(grid), 0);
    gtk_grid_insert_row(GTK_GRID(grid), 1);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);

    gtk_widget_set_valign(grid, GTK_ALIGN_FILL);

    gtk_container_add(GTK_CONTAINER(window), grid);
}

void MainWindow::setup_stack() {
    // Views for the stack
    dashboard_view                   = new DashboardView(this);
    GtkWidget *dashboard_view_widget = dashboard_view->get_widget();

    projects_view                   = new ProjectsView(window);
    GtkWidget *projects_view_widget = projects_view->get_widget();

    // Stack
    stack = gtk_stack_new();
    gtk_stack_set_homogeneous(GTK_STACK(stack), TRUE);
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);

    // Sidebar
    GtkWidget *sidebar = gtk_stack_sidebar_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));
    gtk_widget_set_size_request(sidebar, 128, -1);
    gtk_widget_set_vexpand(sidebar, TRUE);

    // Add the elements to the stack
    gtk_stack_add_titled(GTK_STACK(stack), dashboard_view_widget, "dashboard", "Dashboard");
    gtk_stack_add_titled(GTK_STACK(stack), projects_view_widget, "projects", "Projects");

    gtk_grid_attach(GTK_GRID(grid), sidebar, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), stack, 1, 1, 1, 1);

    g_signal_connect(stack, "notify::visible-child", G_CALLBACK(refresh_all_sub_views), this);
}

void MainWindow::save_and_close_window(GtkWidget *window) {
    int width;
    int height;
    PreferencesModel *preferences_model = new PreferencesModel();

    if (gtk_window_is_maximized(GTK_WINDOW(window))) {
        preferences_model->set_window_maximized(true, false);
    }
    else {
        gtk_window_get_size(GTK_WINDOW(window), &width, &height);

        preferences_model->set_window_width(width, false);
        preferences_model->set_window_height(height, false);
        preferences_model->set_window_maximized(false, false);
    }

    preferences_model->save_all();

    gtk_widget_destroy(window);
}

void MainWindow::switch_stack(const gchar *child_name) {
    GtkWidget *stack_child_widget = gtk_stack_get_child_by_name(GTK_STACK(stack), child_name);
    gtk_stack_set_visible_child(GTK_STACK(stack), stack_child_widget);
}
