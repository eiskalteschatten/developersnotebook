#ifndef MenuBar_hpp
#define MenuBar_hpp

#include "MainWindow.hpp"
#include <gtk/gtk.h>

typedef struct {
    MainWindow *main_window;
    int stack_child;
} SwitchStackInfo;


class MenuBar {
private:
    MainWindow *main_window_obj;
    GtkWidget *main_window;
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

    friend void close_window(GSimpleAction *action, GtkWidget *window);
    friend void quit_app(GSimpleAction *action, gpointer app);
    friend void switch_stack(GSimpleAction *action, SwitchStackInfo *data);

    void setup_file_menu();
    void setup_edit_menu();
    void setup_view_menu();
    void setup_help_menu();

public:
    MenuBar(MainWindow *new_main_window_obj);
    ~MenuBar();

    GtkWidget *get_menu_bar() {return menubar;}

    void setup_macos_menu_bar();
};

#endif /* MenuBar_hpp */
