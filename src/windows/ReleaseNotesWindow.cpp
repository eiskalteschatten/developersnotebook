#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <cstring>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "ReleaseNotesWindow.hpp"
#include "MainWindow.hpp"
#include "../resources/Resource.hpp"
#include "../resources/Image.hpp"
#include "../constants.hpp"

namespace fs = boost::filesystem;


void ReleaseNotesWindow::activate(GtkWidget *menu_item, void *main_window_obj) {
    MainWindow *mw                  = (MainWindow*)main_window_obj;
    std::string path_to_exec_str    = mw->get_path_to_exec();
    GtkWidget *release_notes_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(release_notes_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(release_notes_window), 800, 500);
    gtk_window_set_title(GTK_WINDOW(release_notes_window), "Release Notes");

    #ifndef __APPLE__
        Image logo("icon", "svg", path_to_exec_str, 32, 32);
        std::string path = logo.get_image_path();
        gtk_window_set_icon_from_file(GTK_WINDOW(release_notes_window), path.c_str(), NULL);
    #endif

    GtkWidget *release_notes_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(release_notes_text_view), false);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(release_notes_text_view), GTK_WRAP_WORD);

    GtkWidget *release_notes_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(release_notes_scrolled_window), release_notes_text_view);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(release_notes_text_view));

    ReleaseNotesWindow rnw(path_to_exec_str);
    rnw.fill_release_notes(buffer);

    gtk_container_add(GTK_CONTAINER(release_notes_window), release_notes_scrolled_window);

    gtk_widget_show_all(release_notes_window);
}

ReleaseNotesWindow::ReleaseNotesWindow(std::string path) {
    path_to_exec_str = path;
}

ReleaseNotesWindow::~ReleaseNotesWindow() {}

void ReleaseNotesWindow::fill_release_notes(GtkTextBuffer *buffer) {
    Resource release_notes_resource("release-notes", "html", path_to_exec_str);
    std::string path_to_release_notes = release_notes_resource.get_path();

    std::ifstream ifs(path_to_release_notes.c_str());
    std::string release_notes_str((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    const gchar *release_notes = release_notes_str.c_str();

    GtkTextIter start;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_insert_markup(buffer, &start, release_notes, -1);
}
