#include <cstdlib>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MainWindow.hpp"

GtkWidget *window;

// The menu items that should be hidden in macOS
GtkWidget *menubar;
GtkWidget *file_quit_mi;
GtkWidget *preferences_mi;
GtkWidget *about_mi;
GtkWidget *help_mi;


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

        GtkosxApplication *osx_app = gtkosx_application_get();
        gtkosx_application_set_menu_bar(osx_app, GTK_MENU_SHELL(menubar));
        gtkosx_application_set_help_menu(osx_app, GTK_MENU_ITEM(help_mi));
        gtkosx_application_set_window_menu(osx_app, NULL);

        // Application Menu
        GtkWidget *separator_mi_app_menu_1 = gtk_separator_menu_item_new();

        gtkosx_application_insert_app_menu_item(osx_app, about_mi, 0);
        gtkosx_application_insert_app_menu_item(osx_app, separator_mi_app_menu_1, 1);
        gtkosx_application_insert_app_menu_item(osx_app, preferences_mi, 2);

        gtkosx_application_set_use_quartz_accelerators(osx_app, true);
    #endif
}

void MainWindow::setupMenuBar() {
    GtkWidget *box;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    menubar = gtk_menu_bar_new();

    // Accelerators
    GtkAccelGroup *accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    // Define Submenus
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *edit_menu = gtk_menu_new();
    GtkWidget *help_menu = gtk_menu_new();

    // Define File menu
    GtkWidget *file_mi        = gtk_menu_item_new_with_label("File");
    GtkWidget *close_mi       = gtk_menu_item_new_with_label("Close");
    GtkWidget *separator_mi_1 = gtk_separator_menu_item_new();
    file_quit_mi              = gtk_menu_item_new_with_label("Quit");

    // Define Edit menu
    preferences_mi = gtk_menu_item_new_with_label("Preferences");
    GtkWidget *edit_mi        = gtk_menu_item_new_with_label("Edit");

    // Define Help menu
    about_mi = gtk_menu_item_new_with_label("About");
    help_mi  = gtk_menu_item_new_with_label("Help");

    // Setup submenus
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_mi), edit_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_mi), help_menu);

    // Setup file menu
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi_1);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit_mi);
    gtk_widget_add_accelerator(close_mi, "activate", accel_group, GDK_KEY_w, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(file_quit_mi, "activate", accel_group, GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);

    // Setup Edit menu
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), preferences_mi);
    gtk_widget_add_accelerator(preferences_mi, "activate", accel_group, GDK_KEY_comma, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_mi);

    // Setup Help menu
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_mi);


    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(file_quit_mi), "activate", G_CALLBACK(quit_activated), NULL);
}
