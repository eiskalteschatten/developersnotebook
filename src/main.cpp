#include <boost/filesystem.hpp>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <gtkosxapplication.h>
#endif

#include "db/SqliteSchema.hpp"
#include "windows/MainWindow.hpp"

namespace fs = boost::filesystem;

extern char *PATH_TO_CONFIG;


void initialize();

int main(int argc, char **argv) {
    MainWindow *window = nullptr;

    GtkApplication *app = gtk_application_new("com.alexseifert.developersnotebook", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "startup", G_CALLBACK(initialize), NULL);
    g_signal_connect(app, "activate", G_CALLBACK(window->activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    #ifdef __APPLE__
        GtkosxApplication *osx_app = gtkosx_application_get();
        gtkosx_application_ready(osx_app);
        g_object_unref(osx_app);
    #endif

    delete window;

    return status;
}

void initialize() {
    fs::path path_to_config = fs::path(PATH_TO_CONFIG);

    if (!fs::is_directory(path_to_config)) {
        if(!fs::create_directory(path_to_config)) {
            throw std::runtime_error("Unable to create destination directory " + path_to_config.string());
        }
    }

    SqliteSchema *db_schema = nullptr;
    db_schema->setup_db();
    delete db_schema;
}
