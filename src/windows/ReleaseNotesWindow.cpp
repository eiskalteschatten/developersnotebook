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
        Image logo("icon", "svg", path_to_exec_str);
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

std::string ReleaseNotesWindow::get_release_notes_path() {
    fs::path path_to_exec = path_to_exec_str;
    path_to_exec.remove_filename();
    path_to_exec /= Constants::path_to_resources;

    if (!fs::is_directory(path_to_exec)) {
        path_to_exec.remove_leaf();
        path_to_exec.remove_leaf();
        path_to_exec /= Constants::path_to_resources;
    }

    path_to_exec /= release_notes_file_name + "." + release_notes_extension;

    return path_to_exec.string();
}

std::string ReleaseNotesWindow::get_release_notes_path_mac() {
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

void ReleaseNotesWindow::fill_release_notes(GtkTextBuffer *buffer) {
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

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_insert_markup(buffer, &start, release_notes, -1);
}
