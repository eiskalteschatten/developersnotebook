#include <gtk/gtk.h>

#include "HomeView.hpp"
#include "../constants.hpp"

HomeView::HomeView() {
    const int grid_spacing = 35;

    main_widget = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);
    gtk_grid_set_column_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(main_widget), grid_spacing);

    gtk_grid_insert_row(GTK_GRID(main_widget), 0);
    gtk_grid_insert_column(GTK_GRID(main_widget), 0);

    GtkWidget *title  = gtk_label_new(Constants::application_name.c_str());
    GtkWidget *slogan = gtk_label_new(Constants::application_slogan.c_str());

    gtk_grid_attach(GTK_GRID(main_widget), title, 0, 1, 1, 1);
}
