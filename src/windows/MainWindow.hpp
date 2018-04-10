#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <gtk/gtk.h>

class MainWindow {
private:
    MainWindow();

    static void close_window(GSimpleAction *action, GVariant *parameter, gpointer app);
    static void quit_app(GSimpleAction *action, GVariant *parameter, gpointer app);

    static void setup_grid();
    static void setup_stack();

    static void setup_menu_bar();
    static void setup_macos_menu_bar();

public:
    static void activate(GtkApplication *app, gpointer user_data);
};

#endif /* MainWindow_hpp */
