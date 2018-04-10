#include <cstdlib>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MainWindow.hpp"

GtkWidget *window;
GtkWidget *menubar;
GtkWidget *file_quit_mi;

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) {
    exit(0);
}

void MainWindow::activate(GtkApplication *app, gpointer user_data) {
    // GtkWidget *button;
    // GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Developer's Notebook");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    setupMenuBar();

    // button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    // gtk_container_add(GTK_CONTAINER(window), button_box);

    // button = gtk_button_new_with_label("Hello World");
    // g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    // gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);

    #ifdef __APPLE__
        gtk_widget_hide(GTK_WIDGET(file_quit_mi));
        gtk_widget_hide(menubar);
    #endif
}

void MainWindow::setupMenuBar() {
    GtkWidget *separator_mi = gtk_separator_menu_item_new();
    GtkWidget *box;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    menubar = gtk_menu_bar_new();

    // Define Submenus
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *edit_menu = gtk_menu_new();
    GtkWidget *help_menu = gtk_menu_new();

    // Define File menu
    GtkWidget *file_mi  = gtk_menu_item_new_with_label("File");
    GtkWidget *close_mi = gtk_menu_item_new_with_label("Close");
    file_quit_mi        = gtk_menu_item_new_with_label("Quit");

    // Define Edit menu
    GtkWidget *edit_mi  = gtk_menu_item_new_with_label("Edit");

    // Define Help menu
    GtkWidget *help_mi  = gtk_menu_item_new_with_label("Help");

    // Setup submenus
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_mi), edit_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_mi), help_menu);

    // Setup file menu
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);

    // Setup Edit menu
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_mi);

    // Setup Help menu
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_mi);


    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(file_quit_mi), "activate", G_CALLBACK(quit_activated), NULL);

    #ifdef __APPLE__
        GtkosxApplication *osx_app = gtkosx_application_get();
        gtkosx_application_set_menu_bar(osx_app, GTK_MENU_SHELL(menubar));
        gtkosx_application_set_window_menu(osx_app, NULL);
    #endif
}
