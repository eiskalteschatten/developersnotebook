#include <vector>
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

enum {
    SORT_NAME_COLUMN,
    SORT_START_DATE_COLUMN,
    SORT_END_DATE_COLUMN,
    SORT_IS_COMPLETE_COLUMN,
    SORT_DATE_COMPLETED_COLUMN
};


// Friends

void save_project(GtkWidget *widget, ProjectsView *pv) {
    bool is_complete           = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pv->is_complete_checkbox));
    auto now                   = std::chrono::system_clock::now();
    std::time_t now_time       = std::chrono::system_clock::to_time_t(now);
    std::string now_str        = std::string(std::ctime(&now_time));
    std::string date_completed = is_complete ? now_str : "";
    int id                     = -1;
    gchar *id_char             = nullptr;
    GtkTreeModel *model        = nullptr;
    GtkTreeIter tree_iter;

    if (gtk_tree_selection_get_selected(pv->select, &model, &tree_iter)) {
        gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id_char, -1);
        id = std::stoi(id_char);
    }

    ProjectsModel *projects_model = id != -1 ? new ProjectsModel(id) : new ProjectsModel();

    if (id == -1) {
        projects_model->set_date_created(now_str);
        pv->prepend_to_list_store(&tree_iter);
    }

    const ProjectsRow row = {
        std::to_string(projects_model->get_id()).c_str(),
        gtk_entry_get_text(GTK_ENTRY(pv->project_name_input)),
        gtk_entry_get_text(GTK_ENTRY(pv->start_date_input)),
        gtk_entry_get_text(GTK_ENTRY(pv->end_date_input)),
        is_complete,
        date_completed.c_str(),
        now_str.c_str()
    };

    projects_model->set_name(row.name);
    projects_model->set_start_date(row.start_date);
    projects_model->set_end_date(row.end_date);
    projects_model->set_is_complete(is_complete);
    projects_model->set_date_completed(date_completed);

    pv->set_list_store(row, &tree_iter);
    pv->select_row_in_list_view(&tree_iter);

    delete projects_model;
}

void delete_project(GtkWidget *widget, ProjectsView *pv) {

}

void list_selection_changed(GtkTreeSelection *selection, ProjectsView *pv) {
    GtkTreeIter tree_iter;
    GtkTreeModel *model   = nullptr;
    gchar *id             = nullptr;
    gchar *name           = nullptr;
    gchar *start_date     = nullptr;
    gchar *end_date       = nullptr;
    gboolean is_complete;

    if (gtk_tree_selection_get_selected(selection, &model, &tree_iter)) {
        gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id,
                                              NAME_COLUMN, &name,
                                              START_DATE_COLUMN, &start_date,
                                              END_DATE_COLUMN, &end_date,
                                              IS_COMPLETE_COLUMN, &is_complete,
                                              -1);

        const ProjectsRow row = {
            id,
            name,
            start_date,
            end_date,
            is_complete != 0
        };

        pv->fill_in_sidebar(row);

        g_free(id);
        g_free(name);
        g_free(start_date);
        g_free(end_date);
    }
}


// Class

ProjectsView::ProjectsView() {
    main_widget = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    setup_list_view();
    setup_list_view_toolbar();
    setup_form_sidebar();

    // Attach everything to the panes
    gtk_paned_pack1(GTK_PANED(main_widget), list_view_grid, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED(main_widget), form_grid, FALSE, FALSE);

    empty_sidebar();

    select = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_view));
    gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
    g_signal_connect(G_OBJECT(select), "changed", G_CALLBACK(list_selection_changed), this);
}

ProjectsView::~ProjectsView() {
}

void ProjectsView::setup_list_store() {
    GtkTreeIter tree_iter;
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

    for (auto const &row_map : contents) {
        const ProjectsRow row = convert_table_row_map_to_struct(row_map);
        append_to_list_store(&tree_iter);
        set_list_store(row, &tree_iter);
    }
}

void ProjectsView::setup_list_view() {
    setup_list_store();

    list_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    list_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    g_object_set(list_scrolled_window, "hexpand", TRUE, NULL);
    g_object_set(list_scrolled_window, "vexpand", TRUE, NULL);
    gtk_widget_set_halign(list_scrolled_window, GTK_ALIGN_FILL);
    gtk_widget_set_valign(list_scrolled_window, GTK_ALIGN_FILL);
    gtk_container_add(GTK_CONTAINER(list_scrolled_window), list_view);

    GtkCellRenderer *text_renderer = gtk_cell_renderer_text_new();
    GtkCellRenderer *toggle_renderer = gtk_cell_renderer_toggle_new();

    GtkTreeViewColumn *id_column = gtk_tree_view_column_new_with_attributes("Id", text_renderer, "text", ID_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), id_column);
    gtk_tree_view_column_set_visible(id_column, FALSE);

    GtkTreeViewColumn *is_complete_column = gtk_tree_view_column_new_with_attributes("", toggle_renderer, "active", IS_COMPLETE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), is_complete_column);
    gtk_tree_view_column_set_sort_column_id(is_complete_column, SORT_IS_COMPLETE_COLUMN);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_IS_COMPLETE_COLUMN, sort_by_boolean, GINT_TO_POINTER(IS_COMPLETE_COLUMN), NULL);

    GtkTreeViewColumn *name_column = gtk_tree_view_column_new_with_attributes("Name", text_renderer, "text", NAME_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), name_column);
    gtk_tree_view_column_set_sort_column_id(name_column, SORT_NAME_COLUMN);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_NAME_COLUMN, sort_by_string, GINT_TO_POINTER(NAME_COLUMN), NULL);

    GtkTreeViewColumn *start_date_column = gtk_tree_view_column_new_with_attributes("Start Date", text_renderer, "text", START_DATE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), start_date_column);
    gtk_tree_view_column_set_sort_column_id(start_date_column, SORT_START_DATE_COLUMN);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_START_DATE_COLUMN, sort_by_string, GINT_TO_POINTER(START_DATE_COLUMN), NULL);

    GtkTreeViewColumn *end_date_column = gtk_tree_view_column_new_with_attributes("End Date", text_renderer, "text", END_DATE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), end_date_column);
    gtk_tree_view_column_set_sort_column_id(end_date_column, SORT_END_DATE_COLUMN);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_END_DATE_COLUMN, sort_by_string, GINT_TO_POINTER(END_DATE_COLUMN), NULL);

    GtkTreeViewColumn *date_completed_column = gtk_tree_view_column_new_with_attributes("Completion Date", text_renderer, "text", DATE_COMPLETED_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), date_completed_column);
    gtk_tree_view_column_set_sort_column_id(date_completed_column, SORT_DATE_COMPLETED_COLUMN);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_DATE_COMPLETED_COLUMN, sort_by_string, GINT_TO_POINTER(DATE_COMPLETED_COLUMN), NULL);


    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_store), SORT_IS_COMPLETE_COLUMN, GTK_SORT_ASCENDING);
}

void ProjectsView::setup_list_view_toolbar() {
    list_view_grid = gtk_grid_new();
    g_object_set(list_view_grid, "hexpand", TRUE, NULL);
    g_object_set(list_view_grid, "vexpand", TRUE, NULL);
    gtk_widget_set_halign(list_view_grid, GTK_ALIGN_FILL);
    gtk_widget_set_valign(list_view_grid, GTK_ALIGN_FILL);

    gtk_grid_insert_row(GTK_GRID(list_view_grid), 0);
    gtk_grid_insert_row(GTK_GRID(list_view_grid), 1);

    gtk_grid_attach(GTK_GRID(list_view_grid), list_scrolled_window, 0, 0, 1, 1);

    GtkWidget *toolbar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    GtkWidget *new_toolbar_button = gtk_button_new_from_icon_name("document-new", GTK_ICON_SIZE_SMALL_TOOLBAR);
    g_object_set(new_toolbar_button, "hexpand", FALSE, NULL);

    gtk_box_pack_start(GTK_BOX(toolbar_box), new_toolbar_button, FALSE, FALSE, 0);

    gtk_grid_attach(GTK_GRID(list_view_grid), toolbar_box, 0, 1, 1, 1);
}

void ProjectsView::append_to_list_store(GtkTreeIter *tree_iter) {
    gtk_list_store_append(GTK_LIST_STORE(list_store), tree_iter);
}

void ProjectsView::prepend_to_list_store(GtkTreeIter *tree_iter) {
    gtk_list_store_prepend(GTK_LIST_STORE(list_store), tree_iter);
}

void ProjectsView::set_list_store(const ProjectsRow &row, GtkTreeIter *tree_iter) {
    gtk_list_store_set(GTK_LIST_STORE(list_store), tree_iter, ID_COLUMN, row.id,
                                                              NAME_COLUMN, row.name,
                                                              START_DATE_COLUMN, row.start_date,
                                                              END_DATE_COLUMN, row.end_date,
                                                              IS_COMPLETE_COLUMN, row.is_complete,
                                                              DATE_COMPLETED_COLUMN, row.date_completed,
                                                              DATE_CREATED_COLUMN, row.date_created,
                                                              -1);
}

void ProjectsView::select_row_in_list_view(GtkTreeIter *tree_iter) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_view));
    gtk_tree_selection_select_iter(selection, tree_iter);
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


    // Button Grid
    GtkWidget *button_grid = gtk_grid_new();
    g_object_set(button_grid, "hexpand", TRUE, NULL);
    gtk_grid_insert_row(GTK_GRID(button_grid), 0);


    // Create New Project / Save Button
    save_button = gtk_button_new_with_label("Create New Project");
    gtk_widget_set_halign(save_button, GTK_ALIGN_START);
    g_object_set(save_button, "hexpand", FALSE, NULL);
    g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save_project), this);

    gtk_grid_insert_column(GTK_GRID(button_grid), 0);
    gtk_grid_attach(GTK_GRID(button_grid), save_button, 0, 0, 1, 1);


    // Delete Button
    delete_button = gtk_button_new_with_label("Delete Project");
    gtk_widget_set_halign(delete_button, GTK_ALIGN_END);
    g_object_set(delete_button, "hexpand", TRUE, NULL);
    g_signal_connect(G_OBJECT(delete_button), "clicked", G_CALLBACK(delete_project), this);

    gtk_grid_insert_column(GTK_GRID(button_grid), 1);
    gtk_grid_attach(GTK_GRID(button_grid), delete_button, 1, 0, 1, 1);


    // Add the button grid to the form grid
    gtk_grid_insert_row(GTK_GRID(form_grid), 7);
    gtk_grid_attach(GTK_GRID(form_grid), button_grid, 0, 7, 1, 1);
}

void ProjectsView::empty_sidebar() {
    const ProjectsRow row = {
        "",
        "",
        "",
        "",
        false
    };

    fill_in_sidebar(row);

    gtk_button_set_label(GTK_BUTTON(save_button), "Create New Project");
    gtk_widget_set_sensitive(delete_button, FALSE);
}

void ProjectsView::fill_in_sidebar(const ProjectsRow &row) {
    gtk_entry_set_text(GTK_ENTRY(project_name_input), row.name);
    gtk_entry_set_text(GTK_ENTRY(start_date_input), row.start_date);
    gtk_entry_set_text(GTK_ENTRY(end_date_input), row.end_date);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(is_complete_checkbox), row.is_complete);

    gtk_button_set_label(GTK_BUTTON(save_button), "Save Project");
    gtk_widget_set_sensitive(delete_button, TRUE);
}

ProjectsRow ProjectsView::convert_table_row_map_to_struct(const tableRowMap &map) {
    bool is_complete = std::strncmp(map.at("is_complete").c_str(), "0", 1) != 0;

    const ProjectsRow row = {
        map.at("id").c_str(),
        map.at("name").c_str(),
        map.at("start_date").c_str(),
        map.at("end_date").c_str(),
        is_complete,
        map.at("date_completed").c_str(),
        map.at("date_created").c_str()
    };

    return row;
}
