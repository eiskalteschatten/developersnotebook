#ifndef HomeView_hpp
#define HomeView_hpp

#include <gtk/gtk.h>

class HomeView {
private:
    GtkWidget *main_widget;

public:
    HomeView();
    ~HomeView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* HomeView_hpp */
