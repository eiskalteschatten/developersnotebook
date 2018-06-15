#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <gtk/gtk.h>

#include "AboutDialog.hpp"
#include "../constants.hpp"


void AboutDialog::activate(GtkWidget *menu_item, GtkWidget *main_window) {
    const std::string copyright = "(c) Alex Seifert 2018";
    const std::string comments  = "A digital notebook for developers";
    const std::string website   = "https://www.alexseifert.com";

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    const char *icon_path = std::strcat(cwd, "/resources/images/icon128x128.svg");

    std::ifstream ifs(icon_path);
    std::string icon_svg_content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    GInputStream *stream = g_memory_input_stream_new_from_data(icon_svg_content.c_str(), -1, g_free);
    GdkPixbuf *logo      = gdk_pixbuf_new_from_stream(stream, NULL, NULL);

    GtkWidget *dialog = gtk_about_dialog_new();

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(main_window));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), icon_path, NULL);

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), Constants::application_name.c_str());
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), Constants::application_version.c_str());
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright.c_str());
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), comments.c_str());
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), website.c_str());

    gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog), NULL);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
    g_object_unref(logo);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
