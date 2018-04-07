#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <gtk/gtk.h>

class MainWindow {
private:
    MainWindow();

public:
    static void activate(GtkApplication *app, gpointer user_data);
    static GtkWidget* setupMenuBar(GtkWidget *window);
};

#endif /* MainWindow_hpp */
