#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <gtk/gtk.h>

class MainWindow {
private:
    MainWindow();

    static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app);
    static void setup_menu_bar();
    static void setup_macos_menu_bar();

public:
    static void activate(GtkApplication *app, gpointer user_data);
};

#endif /* MainWindow_hpp */
