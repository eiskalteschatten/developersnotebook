#include <boost/filesystem.hpp>
#include <gtk/gtk.h>
#include <iostream>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "windows/MainWindow.hpp"

namespace fs = boost::filesystem;

extern char *PATH_TO_CONFIG;


void initialize();

int main(int argc, char **argv) {
    initialize();

    GtkApplication *app;
    MainWindow *window;
    int status;

    app = gtk_application_new("com.alexseifert.developersnotebook", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(window->activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    #ifdef __APPLE__
        GtkosxApplication *osx_app = gtkosx_application_get();
        gtkosx_application_ready(osx_app);
        g_object_unref(osx_app);
    #endif

    return status;
}

void initialize() {
    fs::path path_to_config = fs::path(PATH_TO_CONFIG);

    if (!fs::is_directory(path_to_config)) {
        if(!fs::create_directory(path_to_config)) {
            throw std::runtime_error("Unable to create destination directory " + path_to_config.string());
        }
    }
}
