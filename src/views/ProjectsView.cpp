#include <gtk/gtk.h>

#include "ProjectsView.hpp"

ProjectsView::ProjectsView() {
    main_widget = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    GtkWidget *pv = gtk_label_new("projects list view");
    GtkWidget *pv2 = gtk_label_new("projects form view");

    // Setup form grid
    GtkWidget *form_grid = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    gtk_grid_insert_row(GTK_GRID(form_grid), 0);
    gtk_grid_insert_row(GTK_GRID(form_grid), 1);
    gtk_grid_insert_column(GTK_GRID(form_grid), 1);

    gtk_grid_attach(GTK_GRID(form_grid), pv2, 0, 1, 1, 1);

    // Attach everything to the panes
    gtk_paned_add1(GTK_PANED(main_widget), pv);
    gtk_paned_pack2(GTK_PANED(main_widget), form_grid, FALSE, FALSE);
}
