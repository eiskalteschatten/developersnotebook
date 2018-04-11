#include <cstdlib>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MenuBar.hpp"
#include "AboutDialog.hpp"


void MenuBar::close_window(GSimpleAction *action, GVariant *parameter, gpointer app) {
    // gtk_widget_destroy(GTK_WIDGET(window));
    // close top window
}

void MenuBar::quit_app(GSimpleAction *action, GVariant *parameter, gpointer app) {
    exit(0);
}

MenuBar::MenuBar(GtkWidget *window) : window(window) {
    primary_mask_key = GDK_CONTROL_MASK;

    // Override the primary modifier key for macOS
    #ifdef __APPLE__
        primary_mask_key = GDK_META_MASK;
    #endif

    menubar = gtk_menu_bar_new();

    // Accelerators
    accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    setup_file_menu();
    setup_edit_menu();
    setup_projects_menu();
    setup_help_menu();
}

MenuBar::~MenuBar() {
    delete window;
    delete accel_group;
    delete menubar;
    delete file_quit_mi;
    delete preferences_mi;
    delete about_mi;
    delete help_mi;
}

void MenuBar::setup_file_menu() {
    GtkWidget *file_menu      = gtk_menu_new();
    GtkWidget *file_mi        = gtk_menu_item_new_with_label("File");
    GtkWidget *save_mi        = gtk_menu_item_new_with_label("Save");
    GtkWidget *separator_mi_1 = gtk_separator_menu_item_new();
    GtkWidget *close_mi       = gtk_menu_item_new_with_label("Close");
    GtkWidget *separator_mi_2 = gtk_separator_menu_item_new();
    file_quit_mi              = gtk_menu_item_new_with_label("Quit");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_mi);
    gtk_widget_add_accelerator(save_mi, "activate", accel_group, GDK_KEY_s, primary_mask_key, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi_1);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi_2);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit_mi);
    g_signal_connect(G_OBJECT(close_mi), "activate", G_CALLBACK(close_window), NULL);
    gtk_widget_add_accelerator(close_mi, "activate", accel_group, GDK_KEY_w, primary_mask_key, GTK_ACCEL_VISIBLE);

    g_signal_connect(G_OBJECT(file_quit_mi), "activate", G_CALLBACK(quit_app), NULL);
    gtk_widget_add_accelerator(file_quit_mi, "activate", accel_group, GDK_KEY_q, primary_mask_key, GTK_ACCEL_VISIBLE);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);
}

void MenuBar::setup_edit_menu() {
    GtkWidget *edit_menu = gtk_menu_new();
    preferences_mi       = gtk_menu_item_new_with_label("Preferences");
    GtkWidget *edit_mi   = gtk_menu_item_new_with_label("Edit");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_mi), edit_menu);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), preferences_mi);
    gtk_widget_add_accelerator(preferences_mi, "activate", accel_group, GDK_KEY_comma, primary_mask_key, GTK_ACCEL_VISIBLE);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_mi);
}

void MenuBar::setup_projects_menu() {
    GtkWidget *projects_menu           = gtk_menu_new();
    GtkWidget *projects_new_project_mi = gtk_menu_item_new_with_label("New Project");
    GtkWidget *projects_mi             = gtk_menu_item_new_with_label("Projects");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(projects_mi), projects_menu);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(projects_menu), projects_new_project_mi);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), projects_mi);
}

void MenuBar::setup_help_menu() {
    GtkWidget *help_menu = gtk_menu_new();
    about_mi             = gtk_menu_item_new_with_label("About");
    help_mi              = gtk_menu_item_new_with_label("Help");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_mi), help_menu);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_mi);
    g_signal_connect(G_OBJECT(about_mi), "activate", G_CALLBACK(AboutDialog::activate), NULL);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_mi);
}

void MenuBar::setup_macos_menu_bar() {
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

        g_object_unref(osx_app);
    #endif
}
