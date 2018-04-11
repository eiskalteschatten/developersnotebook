#include <gtk/gtk.h>

#include "ProjectsView.hpp"

enum {
    ID_COLUMN,
    NAME_COLUMN,
    START_DATE_COLUMN,
    END_DATE_COLUMN,
    IS_COMPLETE_COLUMN,
    DATE_COMPLETED_COLUMN,
    DATE_CREATED_COLUMN,
    N_COLUMNS
};


ProjectsView::ProjectsView() {
    main_widget = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    setup_list_view();

    // Setup form grid
    form_grid = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    gtk_grid_insert_row(GTK_GRID(form_grid), 0);
    gtk_grid_insert_row(GTK_GRID(form_grid), 1);
    gtk_grid_insert_column(GTK_GRID(form_grid), 1);

    GtkWidget *pv2 = gtk_label_new("projects form view");
    gtk_grid_attach(GTK_GRID(form_grid), pv2, 0, 1, 1, 1);

    // Attach everything to the panes
    gtk_paned_add1(GTK_PANED(main_widget), list_view);
    gtk_paned_pack2(GTK_PANED(main_widget), form_grid, FALSE, FALSE);
}

void ProjectsView::setup_list_store() {
    list_store = gtk_list_store_new(N_COLUMNS,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_BOOLEAN,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING);

    GtkTreeIter iter1;
    gtk_list_store_append(list_store, &iter1);
    gtk_list_store_set(list_store, &iter1,
                        NAME_COLUMN, "Project X",
                        START_DATE_COLUMN, "start date",
                        END_DATE_COLUMN, "end date",
                        IS_COMPLETE_COLUMN, TRUE,
                        DATE_COMPLETED_COLUMN, "completion date",
                        DATE_CREATED_COLUMN, "created date",
                        -1);
}

void ProjectsView::setup_list_view() {
    setup_list_store();

    list_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    GtkCellRenderer *text_renderer = gtk_cell_renderer_text_new();
    GtkCellRenderer *toggle_renderer = gtk_cell_renderer_toggle_new();

    GtkTreeViewColumn *is_complete_column = gtk_tree_view_column_new_with_attributes("", toggle_renderer, "active", IS_COMPLETE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), is_complete_column);

    GtkTreeViewColumn *name_column = gtk_tree_view_column_new_with_attributes("Name", text_renderer, "text", NAME_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), name_column);

    GtkTreeViewColumn *start_date_column = gtk_tree_view_column_new_with_attributes("Start Date", text_renderer, "text", START_DATE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), start_date_column);

    GtkTreeViewColumn *end_date_column = gtk_tree_view_column_new_with_attributes("End Date", text_renderer, "text", END_DATE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), end_date_column);

    GtkTreeViewColumn *date_completed_column = gtk_tree_view_column_new_with_attributes("Completion Date", text_renderer, "text", DATE_COMPLETED_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), date_completed_column);
}

ProjectsView::~ProjectsView() {
    delete list_view;
    delete form_grid;
    delete list_store;
}
