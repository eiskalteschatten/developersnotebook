#include "AbstractView.hpp"

AbstractView::~AbstractView() {
}

gint AbstractView::sort_by_string(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data) {
    gint ret = 0;
    gchar *string1, *string2;
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
