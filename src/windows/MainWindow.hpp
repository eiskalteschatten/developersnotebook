#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <gtk/gtk.h>

class MainWindow: public GtkWidget {
private:
    void setupMenuBar();

public:
    MainWindow();
    virtual ~MainWindow() {};

    GtkWidget *window;
};

#endif /* MainWindow_hpp */
