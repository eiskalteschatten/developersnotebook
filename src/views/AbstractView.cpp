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

void AbstractView::show_error_modal(const gchar *error) {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window),
                                               flags,
                                               GTK_MESSAGE_ERROR,
                                               GTK_BUTTONS_CLOSE,
                                               error);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
