#ifndef AbstractView_hpp
#define AbstractView_hpp

#include <gtk/gtk.h>

class AbstractView {
protected:
    GtkWidget *main_widget;

    virtual void setup_list_store();
    virtual void setup_list_view();
    virtual void setup_form_sidebar();

public:
    AbstractView() {};
    ~AbstractView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* AbstractView_hpp */
