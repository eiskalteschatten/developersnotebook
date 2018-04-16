#ifndef AbstractView_hpp
#define AbstractView_hpp

#include <gtk/gtk.h>

class AbstractView {
protected:
    GtkWidget *main_widget = nullptr;

public:
    AbstractView() {};
    ~AbstractView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* AbstractView_hpp */
