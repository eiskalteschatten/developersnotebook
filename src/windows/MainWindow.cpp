#include <gtk/gtk.h>

#include "MainWindow.hpp"

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

MainWindow::MainWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // setupMenuBar();
}

void MainWindow::setupMenuBar() {

}
