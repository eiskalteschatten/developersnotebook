#include <cstdlib>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MenuBar.hpp"
#include "MainWindow.hpp"
#include "AboutDialog.hpp"


// Friends

void new_project(GSimpleAction *action, MenuBar *mb) {
    MainWindow *mw = mb->main_window_obj;
    mw->switch_stack("projects");
    mw->get_projects_view()->create_new_project();
}

void close_window(GSimpleAction *action, MenuBar *mb) {
    mb->main_window_obj->save_and_close_window(mb->main_window);
}

void quit_app(GSimpleAction *action, MenuBar *mb) {
    mb->main_window_obj->save_and_close_window(mb->main_window);
    exit(0);
}

void switch_stack_dashboard(GSimpleAction *action, MenuBar *mb) {
    mb->main_window_obj->switch_stack("dashboard");
}

void switch_stack_projects(GSimpleAction *action, MenuBar *mb) {
    mb->main_window_obj->switch_stack("projects");
}


// Class

MenuBar::MenuBar(MainWindow *new_main_window_obj) {
    main_window_obj  = new_main_window_obj;
    main_window      = main_window_obj->get_window();
    primary_mask_key = GDK_CONTROL_MASK;

    // Override the primary modifier key for macOS
    #ifdef __APPLE__
        primary_mask_key = GDK_META_MASK;
    #endif

    menubar = gtk_menu_bar_new();

    // Accelerators
    accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(main_window), accel_group);

    setup_file_menu();
    #ifdef __APPLE__
        setup_edit_menu();
    #endif
    setup_view_menu();
    setup_help_menu();
}

MenuBar::~MenuBar() {
}

void MenuBar::setup_file_menu() {
    GtkWidget *file_menu      = gtk_menu_new();
    GtkWidget *file_mi        = gtk_menu_item_new_with_label("File");
    GtkWidget *new_menu       = gtk_menu_new();
    GtkWidget *new_mi         = gtk_menu_item_new_with_label("New");
    GtkWidget *new_project_mi = gtk_menu_item_new_with_label("New Project");
    GtkWidget *separator_mi_1 = gtk_separator_menu_item_new();
    GtkWidget *close_mi       = gtk_menu_item_new_with_label("Close");
    GtkWidget *separator_mi_2 = gtk_separator_menu_item_new();
    file_quit_mi              = gtk_menu_item_new_with_label("Quit");

    // Setup submenus
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(new_mi), new_menu);

    // Setup New submenu
    gtk_menu_shell_append(GTK_MENU_SHELL(new_menu), new_project_mi);
    g_signal_connect(G_OBJECT(new_project_mi), "activate", G_CALLBACK(new_project), this);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi_1);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), close_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator_mi_2);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit_mi);
    g_signal_connect(G_OBJECT(close_mi), "activate", G_CALLBACK(close_window), this);
    gtk_widget_add_accelerator(close_mi, "activate", accel_group, GDK_KEY_w, primary_mask_key, GTK_ACCEL_VISIBLE);

    g_signal_connect(G_OBJECT(file_quit_mi), "activate", G_CALLBACK(quit_app), this);
    gtk_widget_add_accelerator(file_quit_mi, "activate", accel_group, GDK_KEY_q, primary_mask_key, GTK_ACCEL_VISIBLE);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);
}

void MenuBar::setup_edit_menu() {
    GtkWidget *edit_menu = gtk_menu_new();
    // preferences_mi       = gtk_menu_item_new_with_label("Preferences");
    GtkWidget *edit_mi   = gtk_menu_item_new_with_label("Edit");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_mi), edit_menu);

    // Setup menu items
    // gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), preferences_mi);
    // gtk_widget_add_accelerator(preferences_mi, "activate", accel_group, GDK_KEY_comma, primary_mask_key, GTK_ACCEL_VISIBLE);

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_mi);
}

void MenuBar::setup_view_menu() {
    GtkWidget *view_menu = gtk_menu_new();
    GtkWidget *view_mi   = gtk_menu_item_new_with_label("View");

    dashboard_mi = gtk_menu_item_new_with_label("Dashboard");
    projects_mi  = gtk_menu_item_new_with_label("Projects");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(view_mi), view_menu);

    // Setup menu items

    // Dashboard
    {
        gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), dashboard_mi);
        gtk_widget_add_accelerator(dashboard_mi, "activate", accel_group, GDK_KEY_1, primary_mask_key, GTK_ACCEL_VISIBLE);
        g_signal_connect(G_OBJECT(dashboard_mi), "activate", G_CALLBACK(switch_stack_dashboard), this);
    }

    // Projects
    {
        gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), projects_mi);
        gtk_widget_add_accelerator(projects_mi, "activate", accel_group, GDK_KEY_2, primary_mask_key, GTK_ACCEL_VISIBLE);
        g_signal_connect(G_OBJECT(projects_mi), "activate", G_CALLBACK(switch_stack_projects), this);
    }

    #ifdef __APPLE__
        GtkWidget *separator_mi_1 = gtk_separator_menu_item_new();
        gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), separator_mi_1);
    #endif

    // Add the menu to the menu shell
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view_mi);
}

void MenuBar::setup_help_menu() {
    GtkWidget *help_menu            = gtk_menu_new();
    about_mi                        = gtk_menu_item_new_with_label("About");
    GtkWidget *check_for_updates_mi = gtk_menu_item_new_with_label("Check for Updates");
    help_mi                         = gtk_menu_item_new_with_label("Help");

    // Setup submenu
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_mi), help_menu);

    // Setup menu items
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), check_for_updates_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_mi);
    g_signal_connect(G_OBJECT(about_mi), "activate", G_CALLBACK(AboutDialog::activate), main_window);

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
        // gtkosx_application_insert_app_menu_item(osx_app, preferences_mi, 2);

        g_object_unref(osx_app);
    #endif
}
