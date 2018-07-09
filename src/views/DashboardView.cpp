#include <gtk/gtk.h>

#include "DashboardView.hpp"
#include "../resources/Image.hpp"
#include "../models/ProjectsModel.hpp"
#include "../windows/MainWindow.hpp"
#include "../constants.hpp"

enum {
    ID_COLUMN,
    NAME_COLUMN,
    END_DATE_COLUMN,
    N_COLUMNS
};

enum {
    SORT_NAME_COLUMN,
    SORT_END_DATE_COLUMN
};


// Friends

void projects_ending_soon_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *col, DashboardView *dv) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter tree_iter;
    MainWindow *mw = static_cast<MainWindow*>(dv->main_window_obj);

    if (gtk_tree_model_get_iter(model, &tree_iter, path)) {
        GtkWidget *stack = mw->get_stack();
        gchar *id;
        gtk_tree_model_get(model, &tree_iter, ID_COLUMN, &id, -1);

        GtkWidget *stack_child_widget = gtk_stack_get_child_by_name(GTK_STACK(stack), "projects");
        gtk_stack_set_visible_child(GTK_STACK(stack), stack_child_widget);

        mw->get_projects_view()->select_row_in_list_view(id);

        g_free(id);
    }
}


// Class


DashboardView::DashboardView(void *window_obj) {
    main_window_obj = window_obj;
    MainWindow *mw  = (MainWindow*)main_window_obj;

    const int grid_spacing = 20;

    main_widget = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);
    gtk_grid_set_column_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(main_widget), grid_spacing);
    gtk_widget_set_name(main_widget, "dashboard-view");

    gtk_grid_insert_row(GTK_GRID(main_widget), 0);
    gtk_grid_insert_row(GTK_GRID(main_widget), 1);
    gtk_grid_insert_column(GTK_GRID(main_widget), 0);

    // Setup grid for application title, logo, etc
    {
        GtkWidget *title_grid = gtk_grid_new();

        gtk_grid_insert_row(GTK_GRID(title_grid), 0);
        gtk_grid_insert_row(GTK_GRID(title_grid), 1);
        gtk_grid_insert_column(GTK_GRID(title_grid), 0);
        gtk_grid_insert_column(GTK_GRID(title_grid), 1);

        gtk_grid_set_column_spacing(GTK_GRID(title_grid), 10);

        // -- Logo
        Image logo_image("icon", "svg", mw->get_path_to_exec(), 100, 100);
        GtkWidget *logo = logo_image.get_image();
        gtk_grid_attach(GTK_GRID(title_grid), logo, 0, 0, 1, 2);

        gchar *markup = nullptr;

        // Title
        GtkWidget *title          = gtk_label_new(NULL);
        const gchar *app_name     = Constants::application_name.c_str();
        const gchar *format_title = "<span font_weight=\"heavy\" font_size=\"xx-large\">\%s</span>";
        markup                    = g_markup_printf_escaped(format_title, app_name);
        gtk_label_set_markup(GTK_LABEL(title), markup);

        g_object_set(title, "hexpand", TRUE, NULL);
        gtk_widget_set_halign(title, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(title_grid), title, 1, 0, 1, 1);

        // Slogan
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

        gtk_grid_attach(GTK_GRID(main_widget), title_grid, 0, 0, 2, 1);
    }

    // Projects Ending Soon
    {
        GtkWidget *projects_ending_soon_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(projects_ending_soon_grid), 10);

        gtk_grid_insert_row(GTK_GRID(projects_ending_soon_grid), 0);
        gtk_grid_insert_row(GTK_GRID(projects_ending_soon_grid), 1);
        gtk_grid_insert_column(GTK_GRID(projects_ending_soon_grid), 0);

        // Title
        GtkWidget *title          = gtk_label_new(NULL);
        const gchar *format_title = "<span font_weight=\"heavy\" font_size=\"x-large\">\%s</span>";
        const gchar *markup       = g_markup_printf_escaped(format_title, "Projects Ending Soon");
        gtk_label_set_markup(GTK_LABEL(title), markup);

        g_object_set(title, "hexpand", TRUE, NULL);
        gtk_widget_set_halign(title, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(projects_ending_soon_grid), title, 0, 0, 1, 1);

        // Tree View
        setup_projects_ending_soon();
        gtk_grid_attach(GTK_GRID(projects_ending_soon_grid), projects_ending_soon_scrolled_window, 0, 1, 1, 1);

        gtk_grid_attach(GTK_GRID(main_widget), projects_ending_soon_grid, 0, 1, 1, 1);
    }
}

void DashboardView::setup_projects_ending_soon() {
    projects_ending_soon_list_store = gtk_list_store_new(N_COLUMNS,
                                                         G_TYPE_STRING,
                                                         G_TYPE_STRING,
                                                         G_TYPE_STRING);

    projects_ending_soon_tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(projects_ending_soon_list_store));

    projects_ending_soon_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    g_object_set(projects_ending_soon_scrolled_window, "hexpand", TRUE, NULL);
    g_object_set(projects_ending_soon_scrolled_window, "vexpand", TRUE, NULL);
    gtk_widget_set_halign(projects_ending_soon_scrolled_window, GTK_ALIGN_FILL);
    gtk_widget_set_valign(projects_ending_soon_scrolled_window, GTK_ALIGN_FILL);
    gtk_container_add(GTK_CONTAINER(projects_ending_soon_scrolled_window), projects_ending_soon_tree_view);

    GtkCellRenderer *text_renderer = gtk_cell_renderer_text_new();

    // ID Column
    {
        GtkTreeViewColumn *id_column = gtk_tree_view_column_new_with_attributes("Id", text_renderer, "text", ID_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(projects_ending_soon_tree_view), id_column);
        gtk_tree_view_column_set_visible(id_column, FALSE);
    }

    // Name Column
    {
        GtkTreeViewColumn *name_column = gtk_tree_view_column_new_with_attributes("Name", text_renderer, "text", NAME_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(projects_ending_soon_tree_view), name_column);
        gtk_tree_view_column_set_sort_column_id(name_column, SORT_NAME_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(projects_ending_soon_list_store), SORT_NAME_COLUMN, sort_by_string, GINT_TO_POINTER(NAME_COLUMN), NULL);
    }

    // End Date Column
    {
        GtkTreeViewColumn *end_date_column = gtk_tree_view_column_new_with_attributes("End Date", text_renderer, "text", END_DATE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(projects_ending_soon_tree_view), end_date_column);
        gtk_tree_view_column_set_sort_column_id(end_date_column, SORT_END_DATE_COLUMN);
        gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(projects_ending_soon_list_store), SORT_END_DATE_COLUMN, sort_by_date, GINT_TO_POINTER(END_DATE_COLUMN), NULL);
    }

    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(projects_ending_soon_list_store), SORT_END_DATE_COLUMN, GTK_SORT_ASCENDING);

    g_signal_connect(projects_ending_soon_tree_view, "row-activated", G_CALLBACK(projects_ending_soon_row_activated), this);
}

void DashboardView::fill_projects_ending_soon() {
    GtkTreeIter tree_iter;
    ProjectsModel projects;

    gtk_list_store_clear(projects_ending_soon_list_store);

    projects.get_projects_ending_soon();
    const tableVector &contents = projects.get_full_table();

    for (auto const &row_map : contents) {
        ProjectsModel *row       = new ProjectsModel(row_map);
        const std::string id_str = std::to_string(row->get_id());

        gtk_list_store_append(GTK_LIST_STORE(projects_ending_soon_list_store), &tree_iter);

        gtk_list_store_set(GTK_LIST_STORE(projects_ending_soon_list_store), &tree_iter, ID_COLUMN, id_str.c_str(),
                                                                                        NAME_COLUMN, row->get_name().c_str(),
                                                                                        END_DATE_COLUMN, row->get_end_date().c_str(),
                                                                                        -1);

        delete row;
    }
}

void DashboardView::refresh_all_sub_views() {
    fill_projects_ending_soon();
}
