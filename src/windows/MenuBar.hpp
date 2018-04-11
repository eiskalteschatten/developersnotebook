#ifndef MenuBar_hpp
#define MenuBar_hpp

#include <gtk/gtk.h>

class MenuBar {
private:
    GtkWidget *window;

    // The menu items that should be hidden in macOS
    GtkWidget *menubar;
    GtkWidget *file_quit_mi;
    GtkWidget *preferences_mi;
    GtkWidget *about_mi;
    GtkWidget *help_mi;

    static void close_window(GSimpleAction *action, GVariant *parameter, gpointer app);
    static void quit_app(GSimpleAction *action, GVariant *parameter, gpointer app);

public:
    MenuBar(GtkWidget *main_window);
    ~MenuBar();

    GtkWidget *get_menu_bar() {return menubar;}

    void setup_macos_menu_bar();
};

#endif /* MenuBar_hpp */
