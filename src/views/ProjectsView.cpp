#include <map>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstring>
#include <gtk/gtk.h>

#include "ProjectsView.hpp"
#include "../models/ProjectsModel.hpp"
#include "../util/Modal.hpp"

enum {
    ID_COLUMN,
    NAME_COLUMN,
    START_DATE_COLUMN,
    END_DATE_COLUMN,
    URL_COLUMN,
    NOTES_COLUMN,
    IS_COMPLETE_COLUMN,
    DATE_COMPLETED_COLUMN,
    DATE_CREATED_COLUMN,
    N_COLUMNS
};

enum {
    SORT_NAME_COLUMN,
    SORT_START_DATE_COLUMN,
    SORT_END_DATE_COLUMN,
    SORT_URL_COLUMN,
    SORT_NOTES_COLUMN,
    SORT_IS_COMPLETE_COLUMN,
    SORT_DATE_COMPLETED_COLUMN
};


// Friends

void save_project(GtkWidget *widget, ProjectsView *pv) {
    GtkTreeModel *model = nullptr;
    GtkTreeIter tree_iter;

    // Now datetime object
    auto now               = std::time(nullptr);
    struct std::tm *now_tm = std::localtime(&now);
    std::string now_str    = pv->format_date_time(now_tm);

    // Form values
    int id                     = -1;
    gchar *id_char             = nullptr;
    const gchar *name          = gtk_entry_get_text(GTK_ENTRY(pv->project_name_input));
    bool is_complete           = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pv->is_complete_checkbox));
    std::string date_completed = is_complete ? now_str : "";

    GtkTextIter start;
    GtkTextIter end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pv->notes_input));

    gtk_text_buffer_get_bounds(buffer, &start, &end);

    const gchar *notes = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    if (name && !name[0]) {
        Modal modal("No Project Name", "You must enter a project name to create a new project.", pv->main_window);
        modal.show_error_modal();
        return;
    }

    // Start date calendar values
    guint start_year;
    guint start_month;
    guint start_day;

    gtk_calendar_get_date(GTK_CALENDAR(pv->start_date_input), &start_year, &start_month, &start_day);

    std::string start_date_str = start_day == 0 ? "" : pv->format_date(&start_year, &start_month, &start_day);

    // End date calendar values
    guint end_year;
    guint end_month;
    guint end_day;

    gtk_calendar_get_date(GTK_CALENDAR(pv->end_date_input), &end_year, &end_month, &end_day);

    std::string end_date_str = end_day == 0 ? "" : pv->format_date(&end_year, &end_month, &end_day);

    // Start saving
    if (gtk_tree_selection_get_selected(pv->select, &model, &tree_iter)) {
        gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id_char, -1);
        id = std::stoi(id_char);
        g_free(id_char);
    }

    ProjectsModel *projects_model = id != -1 ? new ProjectsModel(id) : new ProjectsModel();

    if (id == -1) {
        projects_model->set_date_created(now_str, FALSE);
        pv->prepend_to_list_store(&tree_iter);
    }

    projects_model->set_name(name, FALSE);
    projects_model->set_start_date(start_date_str, FALSE);
    projects_model->set_end_date(end_date_str, FALSE);
    projects_model->set_url(std::string(gtk_entry_get_text(GTK_ENTRY(pv->url_input))), FALSE);
    projects_model->set_notes(notes, FALSE);
    projects_model->set_is_complete(is_complete, FALSE);
    projects_model->set_date_completed(date_completed, FALSE);

    projects_model->save_all();

    projects_model->truncate_notes();

    pv->set_list_store(projects_model, &tree_iter);
    pv->select_row_in_list_view(&tree_iter);

    delete projects_model;
}

void delete_project(GtkWidget *widget, ProjectsView *pv) {
    Modal modal("Delete Project", "Are you sure you want to delete the selected project?", pv->main_window);
    int result = modal.show_confirm_modal("Delete Project", "Cancel");

    switch(result) {
        case MODAL_RESPONSE_ACCEPT: {
            int id              = -1;
            gchar *id_char      = nullptr;
            GtkTreeModel *model = nullptr;
            GtkTreeIter tree_iter;

            if (gtk_tree_selection_get_selected(pv->select, &model, &tree_iter)) {
                gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id_char, -1);
                id = std::stoi(id_char);
                g_free(id_char);
            }

            if (!gtk_tree_selection_get_selected(pv->select, &model, &tree_iter) || id == -1) {
                Modal modal("No Project Selected", "No project was selected to delete.", pv->main_window);
                modal.show_error_modal();
                break;
            }

            ProjectsModel projects_model(id);
            projects_model.delete_single();

            pv->remove_from_list_store(&tree_iter);
        } break;
        default:
        break;
    }
}

void create_new_project_static(GtkWidget *widget, ProjectsView *pv) {
    pv->create_new_project();
}

void list_selection_changed(GtkTreeSelection *selection, ProjectsView *pv) {
    GtkTreeIter tree_iter;
    GtkTreeModel *model   = nullptr;
    gchar *id             = nullptr;

    if (gtk_tree_selection_get_selected(selection, &model, &tree_iter)) {
        gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id, -1);

        ProjectsModel *projects_model = new ProjectsModel(std::stoi(id));
        projects_model->select_one();

        pv->fill_in_sidebar(projects_model);

        g_free(id);
        delete projects_model;

        gtk_widget_set_sensitive(pv->delete_toolbar_button, TRUE);
    }
    else {
        pv->empty_sidebar();
        gtk_widget_set_sensitive(pv->delete_toolbar_button, FALSE);
    }
}

void clear_start_date_selection(GtkWidget *widget, ProjectsView *pv) {
    pv->reset_calender(pv->start_date_input);
}

void clear_end_date_selection(GtkWidget *widget, ProjectsView *pv) {
    pv->reset_calender(pv->end_date_input);
}


// Class

ProjectsView::ProjectsView(GtkWidget *window) : AbstractView(window) {
    main_widget = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);

    setup_list_view();
    setup_list_view_toolbar();
    setup_form_sidebar();

    // Attach everything to the panes
    gtk_paned_pack1(GTK_PANED(main_widget), list_view_grid, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED(main_widget), form_scrolled_window, FALSE, FALSE);

    empty_sidebar();

    select = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_view));
    gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
    g_signal_connect(G_OBJECT(select), "changed", G_CALLBACK(list_selection_changed), this);
}

ProjectsView::~ProjectsView() {
}

void ProjectsView::setup_list_store() {
    GtkTreeIter tree_iter;
    ProjectsModel all_projects;

    list_store = gtk_list_store_new(N_COLUMNS,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING,
                                    G_TYPE_BOOLEAN,
                                    G_TYPE_STRING,
                                    G_TYPE_STRING);


    all_projects.select_all();
    const tableVector &contents = all_projects.get_full_table();

    for (auto const &row_map : contents) {
        ProjectsModel *row = new ProjectsModel(row_map);
        row->truncate_notes();
        append_to_list_store(&tree_iter);
        set_list_store(row, &tree_iter);
        delete row;
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

    // ID Column
    {
        GtkTreeViewColumn *id_column = gtk_tree_view_column_new_with_attributes("Id", text_renderer, "text", ID_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), id_column);
        gtk_tree_view_column_set_visible(id_column, FALSE);
    }

    // Is Complete Column
    {
        GtkTreeViewColumn *is_complete_column = gtk_tree_view_column_new_with_attributes("", toggle_renderer, "active", IS_COMPLETE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), is_complete_column);
        gtk_tree_view_column_set_sort_column_id(is_complete_column, SORT_IS_COMPLETE_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_IS_COMPLETE_COLUMN, sort_by_boolean, GINT_TO_POINTER(IS_COMPLETE_COLUMN), NULL);
    }

    // Name Column
    {
        GtkTreeViewColumn *name_column = gtk_tree_view_column_new_with_attributes("Name", text_renderer, "text", NAME_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), name_column);
        gtk_tree_view_column_set_sort_column_id(name_column, SORT_NAME_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_NAME_COLUMN, sort_by_string, GINT_TO_POINTER(NAME_COLUMN), NULL);
    }

    // Start Date Column
    {
        GtkTreeViewColumn *start_date_column = gtk_tree_view_column_new_with_attributes("Start Date", text_renderer, "text", START_DATE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), start_date_column);
        gtk_tree_view_column_set_sort_column_id(start_date_column, SORT_START_DATE_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_START_DATE_COLUMN, sort_by_date, GINT_TO_POINTER(START_DATE_COLUMN), NULL);
    }

    // End Date Column
    {
        GtkTreeViewColumn *end_date_column = gtk_tree_view_column_new_with_attributes("End Date", text_renderer, "text", END_DATE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), end_date_column);
        gtk_tree_view_column_set_sort_column_id(end_date_column, SORT_END_DATE_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_END_DATE_COLUMN, sort_by_date, GINT_TO_POINTER(END_DATE_COLUMN), NULL);
    }

    // Date Completed Column
    {
        GtkTreeViewColumn *date_completed_column = gtk_tree_view_column_new_with_attributes("Completion Date", text_renderer, "text", DATE_COMPLETED_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), date_completed_column);
        gtk_tree_view_column_set_sort_column_id(date_completed_column, SORT_DATE_COMPLETED_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_DATE_COMPLETED_COLUMN, sort_by_date, GINT_TO_POINTER(DATE_COMPLETED_COLUMN), NULL);
    }

    // URL Column
    {
        GtkTreeViewColumn *url_column = gtk_tree_view_column_new_with_attributes("URL", text_renderer, "text", URL_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), url_column);
        gtk_tree_view_column_set_sort_column_id(url_column, SORT_URL_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_URL_COLUMN, sort_by_string, GINT_TO_POINTER(URL_COLUMN), NULL);
    }

    // Notes Column
    {
        GtkTreeViewColumn *notes_column = gtk_tree_view_column_new_with_attributes("Notes", text_renderer, "text", NOTES_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), notes_column);
        gtk_tree_view_column_set_sort_column_id(notes_column, SORT_NOTES_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), SORT_NOTES_COLUMN, sort_by_string, GINT_TO_POINTER(NOTES_COLUMN), NULL);
    }

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

    toolbar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    // New button
    {
        new_toolbar_button = gtk_button_new_from_icon_name("document-new", GTK_ICON_SIZE_SMALL_TOOLBAR);
        gtk_button_set_relief(GTK_BUTTON(new_toolbar_button), GTK_RELIEF_NONE);
        g_object_set(new_toolbar_button, "hexpand", FALSE, NULL);
        g_signal_connect(G_OBJECT(new_toolbar_button), "clicked", G_CALLBACK(create_new_project_static), this);
        gtk_box_pack_start(GTK_BOX(toolbar_box), new_toolbar_button, FALSE, FALSE, 0);
    }

    // Delete button
    {
        delete_toolbar_button = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_SMALL_TOOLBAR);
        gtk_button_set_relief(GTK_BUTTON(delete_toolbar_button), GTK_RELIEF_NONE);
        g_object_set(delete_toolbar_button, "hexpand", FALSE, NULL);
        g_signal_connect(G_OBJECT(delete_toolbar_button), "clicked", G_CALLBACK(delete_project), this);
        gtk_box_pack_start(GTK_BOX(toolbar_box), delete_toolbar_button, FALSE, FALSE, 0);
        gtk_widget_set_sensitive(delete_toolbar_button, FALSE);
    }

    gtk_grid_attach(GTK_GRID(list_view_grid), toolbar_box, 0, 1, 1, 1);
}

void ProjectsView::append_to_list_store(GtkTreeIter *tree_iter) {
    gtk_list_store_append(GTK_LIST_STORE(list_store), tree_iter);
}

void ProjectsView::prepend_to_list_store(GtkTreeIter *tree_iter) {
    gtk_list_store_prepend(GTK_LIST_STORE(list_store), tree_iter);
}

void ProjectsView::remove_from_list_store(GtkTreeIter *tree_iter) {
    gtk_list_store_remove(GTK_LIST_STORE(list_store), tree_iter);
}

void ProjectsView::set_list_store(const ProjectsModel *row, GtkTreeIter *tree_iter) {
    const std::string id_str = std::to_string(row->get_id());

    gtk_list_store_set(GTK_LIST_STORE(list_store), tree_iter, ID_COLUMN, id_str.c_str(),
                                                              NAME_COLUMN, row->get_name().c_str(),
                                                              START_DATE_COLUMN, row->get_start_date().c_str(),
                                                              END_DATE_COLUMN, row->get_end_date().c_str(),
                                                              URL_COLUMN, row->get_url().c_str(),
                                                              NOTES_COLUMN, row->get_notes().c_str(),
                                                              IS_COMPLETE_COLUMN, row->get_is_complete(),
                                                              DATE_COMPLETED_COLUMN, row->get_date_completed().c_str(),
                                                              DATE_CREATED_COLUMN, row->get_date_created().c_str(),
                                                              -1);
}

void ProjectsView::select_row_in_list_view(GtkTreeIter *tree_iter) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_view));
    gtk_tree_selection_select_iter(selection, tree_iter);
}

void ProjectsView::setup_form_sidebar() {
    const int grid_spacing        = 10;
    const int field_margin_bottom = 10;

    form_grid = gtk_grid_new();
    g_object_set(form_grid, "hexpand", TRUE, NULL);

    gtk_grid_set_column_spacing(GTK_GRID(form_grid), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(form_grid), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(form_grid), grid_spacing);


    // Project Name
    {
        GtkWidget *project_name_label = gtk_label_new("Project Name");
        gtk_widget_set_halign(project_name_label, GTK_ALIGN_START);

        project_name_input = gtk_entry_new();
        g_object_set(project_name_input, "hexpand", TRUE, NULL);
        gtk_widget_set_margin_bottom(project_name_input, field_margin_bottom);

        gtk_grid_insert_row(GTK_GRID(form_grid), 0);
        gtk_grid_insert_row(GTK_GRID(form_grid), 1);
        gtk_grid_attach(GTK_GRID(form_grid), project_name_label, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(form_grid), project_name_input, 0, 1, 1, 1);
    }

    // Start Date
    {
        GtkWidget *start_date_label = gtk_label_new("Start Date");
        gtk_widget_set_halign(start_date_label, GTK_ALIGN_START);

        start_date_input = gtk_calendar_new();
        g_object_set(start_date_input, "hexpand", TRUE, NULL);

        gtk_grid_insert_row(GTK_GRID(form_grid), 2);
        gtk_grid_insert_row(GTK_GRID(form_grid), 3);
        gtk_grid_attach(GTK_GRID(form_grid), start_date_label, 0, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(form_grid), start_date_input, 0, 3, 1, 1);
    }

    // Clear start date selection button
    {
        start_date_clear_button = gtk_button_new_with_label("Clear Selection");
        gtk_widget_set_halign(start_date_clear_button, GTK_ALIGN_END);
        g_object_set(start_date_clear_button, "hexpand", FALSE, NULL);
        gtk_widget_set_margin_bottom(start_date_clear_button, field_margin_bottom);
        g_signal_connect(G_OBJECT(start_date_clear_button), "clicked", G_CALLBACK(clear_start_date_selection), this);

        gtk_grid_insert_row(GTK_GRID(form_grid), 4);
        gtk_grid_attach(GTK_GRID(form_grid), start_date_clear_button, 0, 4, 1, 1);
    }

    // End Date
    {
        GtkWidget *end_date_label = gtk_label_new("End Date");
        gtk_widget_set_halign(end_date_label, GTK_ALIGN_START);

        end_date_input = gtk_calendar_new();
        g_object_set(end_date_input, "hexpand", TRUE, NULL);

        gtk_grid_insert_row(GTK_GRID(form_grid), 5);
        gtk_grid_insert_row(GTK_GRID(form_grid), 6);
        gtk_grid_attach(GTK_GRID(form_grid), end_date_label, 0, 5, 1, 1);
        gtk_grid_attach(GTK_GRID(form_grid), end_date_input, 0, 6, 1, 1);
    }

    // Clear end date selection button
    {
        end_date_clear_button = gtk_button_new_with_label("Clear Selection");
        gtk_widget_set_halign(end_date_clear_button, GTK_ALIGN_END);
        g_object_set(end_date_clear_button, "hexpand", FALSE, NULL);
        gtk_widget_set_margin_bottom(end_date_clear_button, field_margin_bottom);
        g_signal_connect(G_OBJECT(end_date_clear_button), "clicked", G_CALLBACK(clear_end_date_selection), this);

        gtk_grid_insert_row(GTK_GRID(form_grid), 7);
        gtk_grid_attach(GTK_GRID(form_grid), end_date_clear_button, 0, 7, 1, 1);
    }


    // URL
    {
        GtkWidget *url_label = gtk_label_new("URL");
        gtk_widget_set_halign(url_label, GTK_ALIGN_START);

        url_input = gtk_entry_new();
        g_object_set(url_input, "hexpand", TRUE, NULL);
        gtk_widget_set_margin_bottom(url_input, field_margin_bottom);

        gtk_grid_insert_row(GTK_GRID(form_grid), 8);
        gtk_grid_insert_row(GTK_GRID(form_grid), 9);
        gtk_grid_attach(GTK_GRID(form_grid), url_label, 0, 8, 1, 1);
        gtk_grid_attach(GTK_GRID(form_grid), url_input, 0, 9, 1, 1);
    }


    // Notes
    {
        GtkWidget *notes_label = gtk_label_new("Notes");
        gtk_widget_set_halign(notes_label, GTK_ALIGN_START);

        notes_input = gtk_text_view_new();

        GtkWidget *notes_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        g_object_set(notes_scrolled_window, "hexpand", TRUE, NULL);
        gtk_container_add(GTK_CONTAINER(notes_scrolled_window), notes_input);

        gtk_widget_set_size_request(notes_input, -1, 75);
        gtk_widget_set_size_request(notes_scrolled_window, -1, 75);
        gtk_widget_set_margin_bottom(notes_scrolled_window, field_margin_bottom);

        gtk_grid_insert_row(GTK_GRID(form_grid), 10);
        gtk_grid_insert_row(GTK_GRID(form_grid), 11);
        gtk_grid_attach(GTK_GRID(form_grid), notes_label, 0, 10, 1, 1);
        gtk_grid_attach(GTK_GRID(form_grid), notes_scrolled_window, 0, 11, 1, 1);
    }


    // Is Complete
    {
        is_complete_checkbox = gtk_check_button_new_with_label("Project is completed");
        gtk_widget_set_margin_bottom(is_complete_checkbox, field_margin_bottom);

        gtk_grid_insert_row(GTK_GRID(form_grid), 12);
        gtk_grid_attach(GTK_GRID(form_grid), is_complete_checkbox, 0, 12, 1, 1);
    }


    // Button Grid
    {
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
        delete_button = gtk_button_new_from_icon_name("edit-delete", GTK_ICON_SIZE_BUTTON);
        gtk_widget_set_halign(delete_button, GTK_ALIGN_END);
        g_object_set(delete_button, "hexpand", TRUE, NULL);
        g_signal_connect(G_OBJECT(delete_button), "clicked", G_CALLBACK(delete_project), this);

        gtk_grid_insert_column(GTK_GRID(button_grid), 1);
        gtk_grid_attach(GTK_GRID(button_grid), delete_button, 1, 0, 1, 1);


        // Add the button grid to the form grid
        gtk_grid_insert_row(GTK_GRID(form_grid), 13);
        gtk_grid_attach(GTK_GRID(form_grid), button_grid, 0, 13, 1, 1);
    }


    // Setup the scrollbar
    {
        form_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        g_object_set(form_scrolled_window, "hexpand", TRUE, NULL);
        g_object_set(form_scrolled_window, "vexpand", TRUE, NULL);
        gtk_widget_set_halign(form_scrolled_window, GTK_ALIGN_FILL);
        gtk_widget_set_valign(form_scrolled_window, GTK_ALIGN_FILL);
        gtk_widget_set_size_request(form_scrolled_window, 300, -1);
        gtk_container_add(GTK_CONTAINER(form_scrolled_window), form_grid);
    }
}

void ProjectsView::create_new_project() {
    gtk_tree_selection_unselect_all(select);
    gtk_widget_grab_focus(project_name_input);
}

void ProjectsView::empty_sidebar() {
    tableRowMap row_map;

    row_map["name"]           = "";
    row_map["start_date"]     = "";
    row_map["end_date"]       = "";
    row_map["url"]            = "";
    row_map["notes"]          = "";
    row_map["is_complete"]    = "";
    row_map["date_completed"] = "";
    row_map["date_created"]   = "";

    ProjectsModel *row = new ProjectsModel(row_map);
    fill_in_sidebar(row);
    delete row;

    gtk_button_set_label(GTK_BUTTON(save_button), "Create New Project");
    gtk_widget_set_sensitive(delete_button, FALSE);
}

void ProjectsView::fill_in_sidebar(const ProjectsModel *row) {
    gtk_entry_set_text(GTK_ENTRY(project_name_input), row->get_name().c_str());
    gtk_entry_set_text(GTK_ENTRY(url_input), row->get_url().c_str());
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(is_complete_checkbox), row->get_is_complete());

    if (row->get_start_date() != "") {
        std::string date_str  = row->get_start_date();
        std::tm start_date_tm = get_date_from_string(&date_str);
        guint year            = start_date_tm.tm_year + 1900;

        gtk_calendar_select_month(GTK_CALENDAR(start_date_input), start_date_tm.tm_mon, year);
        gtk_calendar_select_day(GTK_CALENDAR(start_date_input), start_date_tm.tm_mday);
    }
    else {
        reset_calender(start_date_input);
    }

    if (row->get_end_date() != "") {
        std::string date_str = row->get_end_date();
        std::tm end_date_tm  = get_date_from_string(&date_str);
        guint year           = end_date_tm.tm_year + 1900;

        gtk_calendar_select_month(GTK_CALENDAR(end_date_input), end_date_tm.tm_mon, year);
        gtk_calendar_select_day(GTK_CALENDAR(end_date_input), end_date_tm.tm_mday);
    }
    else {
        reset_calender(end_date_input);
    }


    GtkTextIter start;
    GtkTextIter end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(notes_input));
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    gtk_text_buffer_delete(buffer, &start, &end);

    if (row->get_notes() != "") {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(notes_input));
        gtk_text_buffer_get_start_iter(buffer, &start);
        gtk_text_buffer_insert(buffer, &start, row->get_notes().c_str(), -1);
    }

    gtk_button_set_label(GTK_BUTTON(save_button), "Save Project");
    gtk_widget_set_sensitive(delete_button, TRUE);
}
