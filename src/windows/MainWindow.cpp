#include <cstdlib>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "MainWindow.hpp"
#include "AboutDialog.hpp"

GtkWidget *window;
GtkWidget *main_box;

// The menu items that should be hidden in macOS
GtkWidget *menubar;
GtkWidget *file_quit_mi;
GtkWidget *preferences_mi;
GtkWidget *about_mi;
GtkWidget *help_mi;


static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

void MainWindow::close_window(GSimpleAction *action, GVariant *parameter, gpointer app) {
    gtk_widget_destroy(GTK_WIDGET(window));
}

void MainWindow::quit_app(GSimpleAction *action, GVariant *parameter, gpointer app) {
    exit(0);
}

void MainWindow::activate(GtkApplication *app, gpointer user_data) {
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Developer's Notebook");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    setup_stack();
    setup_menu_bar();

    gtk_widget_show_all(window);

    setup_macos_menu_bar();
}

void MainWindow::setup_menu_bar() {
    GdkModifierType primary_mask_key = GDK_CONTROL_MASK;

    // Override the primary modifier key for macOS
    #ifdef __APPLE__
        primary_mask_key = GDK_META_MASK;
    #endif

    gtk_container_add(GTK_CONTAINER(window), main_box);

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
    g_signal_connect(G_OBJECT(close_mi), "activate", G_CALLBACK(close_window), NULL);
    gtk_widget_add_accelerator(close_mi, "activate", accel_group, GDK_KEY_w, primary_mask_key, GTK_ACCEL_VISIBLE);
    g_signal_connect(G_OBJECT(file_quit_mi), "activate", G_CALLBACK(quit_app), NULL);
    gtk_widget_add_accelerator(file_quit_mi, "activate", accel_group, GDK_KEY_q, primary_mask_key, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_mi);

    // Setup Edit menu
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), preferences_mi);
    gtk_widget_add_accelerator(preferences_mi, "activate", accel_group, GDK_KEY_comma, primary_mask_key, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_mi);

    // Setup Help menu
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_mi);
    g_signal_connect(G_OBJECT(about_mi), "activate", G_CALLBACK(AboutDialog::activate), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_mi);


    gtk_box_pack_start(GTK_BOX(main_box), menubar, FALSE, FALSE, 0);

}

void MainWindow::setup_macos_menu_bar() {
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
    #endif
}


void MainWindow::setup_stack() {
    // Stack
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_homogeneous(GTK_STACK(stack), TRUE);
    gtk_widget_set_hexpand(stack, TRUE);

    // Sidebar
    GtkWidget *sidebar = gtk_stack_sidebar_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));
    gtk_widget_set_size_request(sidebar, 128, -1);

    GtkWidget *stack1 = gtk_label_new("stack1");
    GtkWidget *stack2 = gtk_label_new("stack2");

    // Add the elements to the stack
    gtk_stack_add_titled(GTK_STACK(stack), stack1, "home", "Home");
    gtk_stack_add_titled(GTK_STACK(stack), stack2, "projects", "Projects");

    // Grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_insert_row(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    gtk_grid_attach(GTK_GRID(grid), sidebar, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), stack, 1, 0, 1, 1);

    gtk_box_pack_start(GTK_BOX(main_box), grid, TRUE, TRUE, 0);
}
