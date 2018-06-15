#include <ctime>
#include <sstream>
#include <iomanip>

#include "AbstractView.hpp"

AbstractView::AbstractView() {}

AbstractView::AbstractView(GtkWidget *window) {
    main_window = window;
}

AbstractView::~AbstractView() {
    g_free(main_window);
    g_free(main_widget);
}

gint AbstractView::sort_by_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gint ret = 0;
    gchar *string1;
    gchar *string2;
    gint sortcol = GPOINTER_TO_INT(user_data);

    gtk_tree_model_get(model, a, sortcol, &string1, -1);
    gtk_tree_model_get(model, b, sortcol, &string2, -1);

    if (
        (string1 == NULL || string2 == NULL) &&
        !(string1 == NULL && string2 == NULL)
    ) {
        ret = (string1 == NULL) ? -1 : 1;
    }
    else if (!(string1 == NULL && string2 == NULL)) {
        ret = g_utf8_collate(string1, string2);
    }

    g_free(string1);
    g_free(string2);

    return ret;
}

gint AbstractView::sort_by_boolean(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gboolean bool1;
    gboolean bool2;
    gint sortcol = GPOINTER_TO_INT(user_data);

    gtk_tree_model_get(model, a, sortcol, &bool1, -1);
    gtk_tree_model_get(model, b, sortcol, &bool2, -1);

    if (!bool1 && bool2) {
        return -1;
    }
    else if (bool1 && !bool2) {
        return 1;
    }

    return 0;
}

std::string AbstractView::format_date(const guint *year, const guint *month, const guint *day) {
    struct tm date_tm = {0};

    date_tm.tm_year = *year - 1900;
    date_tm.tm_mon  = *month;
    date_tm.tm_mday = *day;

    return format_date(&date_tm);
}

std::string AbstractView::format_date(const tm *date_tm) {
    std::stringstream ss;
    ss << std::put_time(date_tm, "%a, %d %B %Y");
    return ss.str();
}

std::string AbstractView::format_date_time(const tm *date_tm) {
    std::stringstream ss;
    ss << std::put_time(date_tm, "%a, %d %B %Y %T");
    return ss.str();
}

void AbstractView::show_error_modal(const gchar *error) {
    GtkWidget *image = gtk_image_new_from_icon_name("dialog-error", GTK_ICON_SIZE_DIALOG);
    GtkWidget *label = gtk_label_new(error);
    GtkWidget *hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(hbox), label, TRUE, FALSE, 0);

    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog    = gtk_dialog_new_with_buttons("",
                                                       GTK_WINDOW(main_window),
                                                       flags,
                                                       "OK",
                                                       GTK_RESPONSE_OK,
                                                       NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_box_pack_start(GTK_BOX(content_area), hbox, TRUE, FALSE, 0);
    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
