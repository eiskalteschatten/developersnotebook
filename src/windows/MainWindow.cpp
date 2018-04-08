#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MainWindow.hpp"

GtkWidget *menubar;
GtkWidget *file_quit_menu_item;

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

void MainWindow::activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    // GtkWidget *button;
    // GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Developer's Notebook");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    setupMenuBar(window);


    // button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    // gtk_container_add(GTK_CONTAINER(window), button_box);

    // button = gtk_button_new_with_label("Hello World");
    // g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    // gtk_container_add(GTK_CONTAINER(button_box), button);

    gtk_widget_show_all(window);

    #ifdef __APPLE__
        //GtkWidget *file_quit_menu_item = lookup_widget(GTK_WIDGET(menubar), "/menubar/File/Quit");
        gtk_widget_hide(GTK_WIDGET(file_quit_menu_item));

        gtk_widget_hide(menubar);
    #endif
}

void MainWindow::setupMenuBar(GtkWidget *window) {
    GtkWidget *box;

    GtkWidget *file_menu;
    GtkWidget *file_mi;
    GtkWidget *close_mi;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    menubar   = gtk_menu_bar_new();
    file_menu = gtk_menu_new();

    file_mi  = gtk_menu_item_new_with_label("File");
    close_mi = gtk_menu_item_new_with_label("Close");
    file_quit_menu_item  = gtk_menu_item_new_with_label("Quit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit_menu_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    #ifdef __APPLE__
        GtkosxApplication *osx_app = gtkosx_application_get();
        gtkosx_application_set_menu_bar(osx_app, GTK_MENU_SHELL(menubar));
        gtkosx_application_set_window_menu(osx_app, NULL);
    #endif
}
