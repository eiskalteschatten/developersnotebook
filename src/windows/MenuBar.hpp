#ifndef MenuBar_hpp
#define MenuBar_hpp

#include <gtk/gtk.h>

class MenuBar {
private:
    GtkWidget *window;
    GdkModifierType primary_mask_key;
    GtkAccelGroup *accel_group;

    // The menu items that should be hidden in macOS
    GtkWidget *menubar;
    GtkWidget *file_quit_mi;
    // GtkWidget *preferences_mi;
    GtkWidget *about_mi;
    GtkWidget *help_mi;

    // The "View" menu items that correspond to the main views
    GtkWidget *dashboard_mi;
    GtkWidget *projects_mi;

    static void close_window(GSimpleAction *action, GVariant *parameter, gpointer app);
    static void quit_app(GSimpleAction *action, GVariant *parameter, gpointer app);

    void setup_file_menu();
    void setup_edit_menu();
    void setup_view_menu();
    void setup_help_menu();

public:
    MenuBar(GtkWidget *window);
    ~MenuBar();

    GtkWidget *get_menu_bar() {return menubar;}

    void setup_macos_menu_bar();
};

#endif /* MenuBar_hpp */
