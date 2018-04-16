#ifndef MenuBar_hpp
#define MenuBar_hpp

#include <gtk/gtk.h>

class MenuBar {
private:
    GtkWidget *window = nullptr;
    GdkModifierType primary_mask_key;
    GtkAccelGroup *accel_group = nullptr;

    // The menu items that should be hidden in macOS
    GtkWidget *menubar = nullptr;
    GtkWidget *file_quit_mi = nullptr;
    GtkWidget *preferences_mi = nullptr;
    GtkWidget *about_mi = nullptr;
    GtkWidget *help_mi = nullptr;

    static void close_window(GSimpleAction *action, GVariant *parameter, gpointer app);
    static void quit_app(GSimpleAction *action, GVariant *parameter, gpointer app);

    void setup_file_menu();
    void setup_edit_menu();
    void setup_projects_menu();
    void setup_help_menu();

public:
    MenuBar(GtkWidget *window);
    ~MenuBar();

    GtkWidget *get_menu_bar() {return menubar;}

    void setup_macos_menu_bar();
};

#endif /* MenuBar_hpp */
