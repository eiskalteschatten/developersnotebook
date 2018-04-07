#include <gtk/gtk.h>

#include "windows/MainWindow.hpp"

int main(int argc, char **argv) {
    GtkApplication *app;
    MainWindow *window;
    int status;

    app = gtk_application_new("com.alexseifert.developersnotebook", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(window->activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
