#include <gtk/gtk.h>

#include "ProjectsView.hpp"

ProjectsView::ProjectsView() {
    main_widget = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    gtk_grid_insert_row(GTK_GRID(main_widget), 0);
    gtk_grid_insert_column(GTK_GRID(main_widget), 0);

    GtkWidget *pv = gtk_label_new("projects view");

    gtk_grid_attach(GTK_GRID(main_widget), pv, 0, 1, 1, 1);
}
