#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <cstring>
#include <gtk/gtk.h>


#include "ProjectsView.hpp"
#include "../models/ProjectsModel.hpp"

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


void save_project(GtkWidget *widget, ProjectsView *pv) {
    // TODO: Get id from selected element in the list view.
    //       If something is selected, pass it to the ProjectsModel constructor, otherwise don't pass any id to create a new entry

    bool is_complete           = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pv->is_complete_checkbox));
    auto now                   = std::chrono::system_clock::now();
    std::time_t now_time       = std::chrono::system_clock::to_time_t(now);
    std::string now_str        = std::string(std::ctime(&now_time));
    std::string date_completed = is_complete ? now_str : "";

    // if (id) {
    //     ProjectsModel projects_model(id);
    // }
    // else {
        ProjectsModel projects_model;
        projects_model.set_date_created(now_str);
    //}

    projects_model.set_name(std::string(gtk_entry_get_text(GTK_ENTRY(pv->project_name_input))));
    projects_model.set_start_date(std::string(gtk_entry_get_text(GTK_ENTRY(pv->start_date_input))));
    projects_model.set_end_date(std::string(gtk_entry_get_text(GTK_ENTRY(pv->end_date_input))));
    projects_model.set_is_complete(is_complete);
    projects_model.set_date_completed(date_completed);

    pv->prepend_to_list_store();

    delete widget;
    delete pv;
}


ProjectsView::ProjectsView() {
    main_widget = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    setup_list_view();
    setup_form_sidebar();

    // Attach everything to the panes
    gtk_paned_add1(GTK_PANED(main_widget), list_view);
    gtk_paned_pack2(GTK_PANED(main_widget), form_grid, FALSE, FALSE);
}

ProjectsView::~ProjectsView() {
}

void ProjectsView::setup_list_store() {
    ProjectsModel projects_model;

    list_store = gtk_list_store_new(N_COLUMNS,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_BOOLEAN,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING);


    const tableVector &contents = projects_model.select_all();

    for (auto const &row : contents) {
        append_to_list_store();
        set_list_store(row);
    }
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

void ProjectsView::append_to_list_store() {
    gtk_list_store_append(GTK_LIST_STORE(list_store), &tree_iter);
}

void ProjectsView::prepend_to_list_store() {
    gtk_list_store_prepend(GTK_LIST_STORE(list_store), &tree_iter);
}

void ProjectsView::set_list_store(const tableRowMap &row) {
    bool is_complete = std::strncmp(row.at("is_complete").c_str(), "0", 1) != 0;

    gtk_list_store_set(GTK_LIST_STORE(list_store), &tree_iter, NAME_COLUMN, row.at("name").c_str(),
                                                               START_DATE_COLUMN, row.at("start_date").c_str(),
                                                               END_DATE_COLUMN, row.at("end_date").c_str(),
                                                               IS_COMPLETE_COLUMN, is_complete,
                                                               DATE_COMPLETED_COLUMN, row.at("date_completed").c_str(),
                                                               DATE_CREATED_COLUMN, row.at("date_created").c_str(),
                                                               -1);
}

void ProjectsView::setup_form_sidebar() {
    const int grid_spacing        = 10;
    const int field_margin_bottom = 15;
    const gchar *placeholder_date = "DD-MM-YYYY";

    form_grid = gtk_grid_new();
    g_object_set(form_grid, "hexpand", TRUE, NULL);

    gtk_grid_set_column_spacing(GTK_GRID(form_grid), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(form_grid), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(form_grid), grid_spacing);

    // Project Name
    GtkWidget *project_name_label = gtk_label_new("Project Name");
    gtk_widget_set_halign(project_name_label, GTK_ALIGN_START);

    project_name_input = gtk_entry_new();
    g_object_set(project_name_input, "hexpand", TRUE, NULL);
    gtk_widget_set_margin_bottom(project_name_input, field_margin_bottom);

    gtk_grid_insert_row(GTK_GRID(form_grid), 0);
    gtk_grid_insert_row(GTK_GRID(form_grid), 1);
    gtk_grid_attach(GTK_GRID(form_grid), project_name_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(form_grid), project_name_input, 0, 1, 1, 1);


    // Start Date
    GtkWidget *start_date_label = gtk_label_new("Start Date");
    gtk_widget_set_halign(start_date_label, GTK_ALIGN_START);

    start_date_input = gtk_entry_new();
    g_object_set(start_date_input, "hexpand", TRUE, NULL);
    gtk_widget_set_margin_bottom(start_date_input, field_margin_bottom);
    gtk_entry_set_placeholder_text(GTK_ENTRY(start_date_input), placeholder_date);

    gtk_grid_insert_row(GTK_GRID(form_grid), 2);
    gtk_grid_insert_row(GTK_GRID(form_grid), 3);
    gtk_grid_attach(GTK_GRID(form_grid), start_date_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(form_grid), start_date_input, 0, 3, 1, 1);


    // End Date
    GtkWidget *end_date_label = gtk_label_new("End Date");
    gtk_widget_set_halign(end_date_label, GTK_ALIGN_START);

    end_date_input = gtk_entry_new();
    g_object_set(end_date_input, "hexpand", TRUE, NULL);
    gtk_widget_set_margin_bottom(end_date_input, field_margin_bottom);
    gtk_entry_set_placeholder_text(GTK_ENTRY(end_date_input), placeholder_date);

    gtk_grid_insert_row(GTK_GRID(form_grid), 4);
    gtk_grid_insert_row(GTK_GRID(form_grid), 5);
    gtk_grid_attach(GTK_GRID(form_grid), end_date_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(form_grid), end_date_input, 0, 5, 1, 1);


    // Is Complete
    is_complete_checkbox = gtk_check_button_new_with_label("Project is completed");
    gtk_widget_set_margin_bottom(is_complete_checkbox, field_margin_bottom);

    gtk_grid_insert_row(GTK_GRID(form_grid), 6);
    gtk_grid_attach(GTK_GRID(form_grid), is_complete_checkbox, 0, 6, 1, 1);

    // Save Button
    GtkWidget *save_button = gtk_button_new_with_label("Save Project");
    gtk_widget_set_halign(save_button, GTK_ALIGN_START);
    g_object_set(save_button, "hexpand", FALSE, NULL);
    g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save_project), this);


    gtk_grid_insert_row(GTK_GRID(form_grid), 7);
    gtk_grid_attach(GTK_GRID(form_grid), save_button, 0, 7, 1, 1);

}

