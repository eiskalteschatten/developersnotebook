#include <string>
#include <cstring>
#include <unistd.h>
#include <gtk/gtk.h>

#include "AboutDialog.hpp"
#include "../constants.hpp"


void AboutDialog::activate() {
    const std::string copyright = "(c) Alex Seifert 2018";
    const std::string comments  = "A digital notebook for developers";
    const std::string website   = "https://www.alexseifert.com";

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    const char *icon_path = std::strcat(cwd, "/resources/images/logo.png");

    GError *error;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon_path, &error);

    GtkWidget *dialog = gtk_about_dialog_new();

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), Constants::application_name.c_str());
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), Constants::application_version.c_str());
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright.c_str());
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), comments.c_str());
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), website.c_str());

    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
