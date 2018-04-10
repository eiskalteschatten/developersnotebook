#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <gtk/gtk.h>

class MainWindow {
private:
    MainWindow();

    static void quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app);

public:
    static void activate(GtkApplication *app, gpointer user_data);
    static void setup_menu_bar();
};

#endif /* MainWindow_hpp */
