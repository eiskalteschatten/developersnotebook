#ifndef AbstractView_hpp
#define AbstractView_hpp

#include <gtk/gtk.h>

typedef std::map<std::string, std::string> tableRowMap;
typedef std::vector<tableRowMap> tableVector;


class AbstractView {
protected:
    GtkWidget *main_widget;

public:
    AbstractView() {};
    ~AbstractView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* AbstractView_hpp */
