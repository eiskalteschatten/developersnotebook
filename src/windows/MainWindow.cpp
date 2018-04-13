#include <gtk/gtk.h>

#include "MainWindow.hpp"
#include "MenuBar.hpp"
#include "../views/HomeView.hpp"
#include "../views/ProjectsView.hpp"
#include "../models/PreferencesModel.hpp"

GtkWidget *window;
GtkWidget *grid;


void MainWindow::activate(GtkApplication *app, gpointer user_data) {
    int window_width;
    int window_height;

    PreferencesModel *preferences_model = new PreferencesModel();
    window_width = preferences_model->get_window_width();
    window_height = preferences_model->get_window_height();

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Developer's Notebook");
    gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    setup_grid();
    setup_stack();

    MenuBar *menubar_obj = new MenuBar(window);
    GtkWidget *menubar   = menubar_obj->get_menu_bar();
    gtk_grid_attach(GTK_GRID(grid), menubar, 0, 0, 2, 1);

    gtk_widget_show_all(window);

    menubar_obj->setup_macos_menu_bar();
}

void MainWindow::setup_grid() {
    // Grid
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
    HomeView *home_view         = new HomeView();
    GtkWidget *home_view_widget = home_view->get_widget();

    ProjectsView *projects_view     = new ProjectsView();
    GtkWidget *projects_view_widget = projects_view->get_widget();

    // Stack
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_homogeneous(GTK_STACK(stack), TRUE);
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);

    // Sidebar
    GtkWidget *sidebar = gtk_stack_sidebar_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));
    gtk_widget_set_size_request(sidebar, 128, -1);
    gtk_widget_set_vexpand(sidebar, TRUE);

    // Add the elements to the stack
    gtk_stack_add_titled(GTK_STACK(stack), home_view_widget, "home", "Home");
    gtk_stack_add_titled(GTK_STACK(stack), projects_view_widget, "projects", "Projects");

    gtk_grid_attach(GTK_GRID(grid), sidebar, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), stack, 1, 1, 1, 1);
}
