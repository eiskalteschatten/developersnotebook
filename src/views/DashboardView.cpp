#include <fstream>
#include <cstring>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "DashboardView.hpp"
#include "../util/Image.hpp"
#include "../models/ProjectsModel.hpp"
#include "../constants.hpp"


DashboardView::DashboardView() {
    const int grid_spacing = 20;

    main_widget = gtk_grid_new();
    gtk_widget_set_halign(main_widget, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_widget, GTK_ALIGN_FILL);
    gtk_grid_set_column_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(main_widget), grid_spacing);
    gtk_container_set_border_width(GTK_CONTAINER(main_widget), grid_spacing);

    gtk_grid_insert_row(GTK_GRID(main_widget), 0);
    gtk_grid_insert_row(GTK_GRID(main_widget), 1);
    gtk_grid_insert_column(GTK_GRID(main_widget), 0);
    gtk_grid_insert_column(GTK_GRID(main_widget), 1);

    // Setup grid for application title, logo, etc
    {
        GtkWidget *title_grid = gtk_grid_new();

        gtk_grid_insert_row(GTK_GRID(title_grid), 0);
        gtk_grid_insert_row(GTK_GRID(title_grid), 1);
        gtk_grid_insert_column(GTK_GRID(title_grid), 0);
        gtk_grid_insert_column(GTK_GRID(title_grid), 1);

        // -- Logo
        Image logo_image("icon128x128", "svg");
        GdkPixbuf *logo_buf = logo_image.get_pixbuf();
        GtkWidget *logo     = gtk_image_new_from_pixbuf(logo_buf);
        g_object_unref(logo_buf);
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

    // Release Notes
    {
        GtkWidget *release_notes_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(release_notes_grid), 10);

        gtk_grid_insert_row(GTK_GRID(release_notes_grid), 0);
        gtk_grid_insert_row(GTK_GRID(release_notes_grid), 1);
        gtk_grid_insert_column(GTK_GRID(release_notes_grid), 0);

        // Title
        GtkWidget *title          = gtk_label_new(NULL);
        const gchar *format_title = "<span font_weight=\"heavy\" font_size=\"x-large\">\%s</span>";
        const gchar *markup       = g_markup_printf_escaped(format_title, "Release Notes");
        gtk_label_set_markup(GTK_LABEL(title), markup);

        g_object_set(title, "hexpand", TRUE, NULL);
        gtk_widget_set_halign(title, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(release_notes_grid), title, 0, 0, 1, 1);

        // Release Notes Text View
        release_notes_text_view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(release_notes_text_view), false);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(release_notes_text_view), GTK_WRAP_WORD);

        GtkWidget *release_notes_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        g_object_set(release_notes_scrolled_window, "hexpand", TRUE, NULL);
        g_object_set(release_notes_scrolled_window, "vexpand", TRUE, NULL);
        gtk_container_add(GTK_CONTAINER(release_notes_scrolled_window), release_notes_text_view);

        gtk_grid_attach(GTK_GRID(release_notes_grid), release_notes_scrolled_window, 0, 1, 1, 1);

        fill_release_notes();

        gtk_grid_attach(GTK_GRID(main_widget), release_notes_grid, 0, 1, 1, 1);
    }

    // Grid for the right side
    GtkWidget *right_side_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(right_side_grid), 10);

    gtk_grid_insert_row(GTK_GRID(right_side_grid), 0);
    gtk_grid_insert_row(GTK_GRID(right_side_grid), 1);
    gtk_grid_insert_column(GTK_GRID(right_side_grid), 0);

    // Projects Ending Soon
    {
        // Title
        GtkWidget *title          = gtk_label_new(NULL);
        const gchar *format_title = "<span font_weight=\"heavy\" font_size=\"x-large\">\%s</span>";
        const gchar *markup       = g_markup_printf_escaped(format_title, "Projects Ending Soon");
        gtk_label_set_markup(GTK_LABEL(title), markup);

        g_object_set(title, "hexpand", TRUE, NULL);
        gtk_widget_set_halign(title, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(right_side_grid), title, 0, 0, 1, 1);

        // Tree View
        //projects_ending_soon_tree_view = ;
    }

    gtk_grid_attach(GTK_GRID(main_widget), right_side_grid, 1, 1, 1, 1);
}

std::string DashboardView::get_release_notes_path() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    const std::string path = Constants::path_to_resources + "/" + release_notes_file_name + "." + release_notes_extension;
    return std::string(std::strcat(cwd, path.c_str()));
}

std::string DashboardView::get_release_notes_path_mac() {
    #ifdef __APPLE__
        CFStringRef apple_name      = CFStringCreateWithCString(NULL, release_notes_file_name.c_str(), kCFStringEncodingUTF8);
        CFStringRef apple_extension = CFStringCreateWithCString(NULL, release_notes_extension.c_str(), kCFStringEncodingUTF8);
        CFURLRef file_url_ref       = CFBundleCopyResourceURL(CFBundleGetMainBundle(), apple_name, apple_extension, NULL);

        if (file_url_ref == NULL) {
            return get_release_notes_path();
        }

        CFStringRef path                 = CFURLCopyFileSystemPath(file_url_ref, kCFURLPOSIXPathStyle);
        CFStringEncoding encoding_method = CFStringGetSystemEncoding();
        CFRelease(file_url_ref);

        return std::string(CFStringGetCStringPtr(path, encoding_method));
    #else
        return get_release_notes_path();
    #endif
}

void DashboardView::fill_release_notes() {
    std::string path_to_release_notes;

    #ifdef __APPLE__
        path_to_release_notes = get_release_notes_path_mac();
    #else
        path_to_release_notes = get_release_notes_path();
    #endif

    std::ifstream ifs(path_to_release_notes.c_str());
    std::string release_notes_str((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    const gchar *release_notes = release_notes_str.c_str();

    GtkTextIter start;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(release_notes_text_view));

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_insert_markup(buffer, &start, release_notes, -1);
}

void DashboardView::fill_projects_ending_soon() {

}
