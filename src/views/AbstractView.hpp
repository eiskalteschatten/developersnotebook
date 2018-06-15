#ifndef AbstractView_hpp
#define AbstractView_hpp

#include <vector>
#include <map>
#include <string>
#include <gtk/gtk.h>

typedef std::map<std::string, std::string> tableRowMap;
typedef std::vector<tableRowMap> tableVector;


class AbstractView {
protected:
    GtkWidget *main_window;
    GtkWidget *main_widget;

    static gint sort_by_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data);
    static gint sort_by_boolean(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data);

    std::string format_date(const guint *year, const guint *month, const guint *day);
    void show_error_modal(const gchar *error);

public:
    AbstractView();
    AbstractView(GtkWidget *window);
    ~AbstractView();

    GtkWidget *get_widget() {return main_widget;}
};

#endif /* AbstractView_hpp */
