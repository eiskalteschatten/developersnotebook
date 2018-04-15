#include <gtk/gtk.h>

#include "AboutDialog.hpp"

GtkWidget *dialog;

const char name[21] = "Developer's Notebook";
const char version[4] = "0.1";
const char copyright[22] = "(c) Alex Seifert 2018";
const char comments[34] = "A digital notebook for developers";
const char website[28] = "https://www.alexseifert.com";


void AboutDialog::activate() {
    //GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("../resources/templogo2.jpg", NULL);

    dialog = gtk_about_dialog_new();

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), name);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), version);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), comments);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), website);

    // gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    // g_object_unref(pixbuf), pixbuf = NULL;

    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}
