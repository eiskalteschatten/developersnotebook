#include <gtk/gtk.h>

#include "DashboardView.hpp"
#include "../util/Image.hpp"
#include "../constants.hpp"

DashboardView::DashboardView() {
    const int grid_spacing = 35;

    main_widget = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);
    gtk_grid_set_column_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(main_widget), grid_spacing);

    gtk_grid_insert_row(GTK_GRID(main_widget), 0);
    gtk_grid_insert_column(GTK_GRID(main_widget), 0);

    GtkWidget *title_grid = gtk_grid_new();

    gtk_grid_insert_row(GTK_GRID(title_grid), 0);
    gtk_grid_insert_column(GTK_GRID(title_grid), 0);
    gtk_grid_insert_column(GTK_GRID(title_grid), 1);

    Image logo_image("icon128x128", "svg");
    GdkPixbuf *logo_buf = logo_image.get_pixbuf();
    GtkWidget *logo     = gtk_image_new_from_pixbuf(logo_buf);
    g_object_unref(logo_buf);
    gtk_grid_attach(GTK_GRID(title_grid), logo, 0, 0, 1, 2);

    gchar *markup = nullptr;

    GtkWidget *title          = gtk_label_new(NULL);
    const gchar *app_name     = Constants::application_name.c_str();
    const gchar *format_title = "<span font_weight=\"heavy\" font_size=\"xx-large\">\%s</span>";
    markup                    = g_markup_printf_escaped(format_title, app_name);
    gtk_label_set_markup(GTK_LABEL(title), markup);

    g_object_set(title, "hexpand", TRUE, NULL);
    gtk_widget_set_halign(title, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(title_grid), title, 1, 0, 1, 1);

    GtkWidget *slogan          = gtk_label_new(NULL);
    const gchar *app_slogan    = Constants::application_slogan.c_str();
    const gchar *format_slogan = "<span font_size=\"large\">\%s</span>";
    markup                     = g_markup_printf_escaped(format_slogan, app_slogan);
    gtk_label_set_markup(GTK_LABEL(slogan), markup);

    g_object_set(slogan, "hexpand", TRUE, NULL);
    gtk_widget_set_halign(slogan, GTK_ALIGN_START);
    gtk_widget_set_valign(slogan, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(title_grid), slogan, 1, 1, 1, 1);

    g_free(markup);

    gtk_grid_attach(GTK_GRID(main_widget), title_grid, 0, 0, 1, 1);
}
