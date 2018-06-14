#ifndef AbstractView_hpp
#define AbstractView_hpp

#include <vector>
#include <map>
#include <gtk/gtk.h>

typedef std::map<std::string, std::string> tableRowMap;
typedef std::vector<tableRowMap> tableVector;


class AbstractView {
protected:
    GtkWindow *main_window;
    GtkWidget *main_widget;

    static gint sort_by_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data);
    static gint sort_by_boolean(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data);
    void show_error_modal(const gchar *error);

public:
    AbstractView(GtkWindow *window);
    ~AbstractView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* AbstractView_hpp */
