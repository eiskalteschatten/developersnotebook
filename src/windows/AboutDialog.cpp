#include <string>
#include <gtk/gtk.h>

#include "AboutDialog.hpp"
#include "../util/Image.hpp"
#include "../constants.hpp"


void AboutDialog::activate(GtkWidget *menu_item, GtkWidget *main_window) {
    const gchar *copyright = "(c) Alex Seifert 2018";

    Image logo("icon128x128", "svg");
    GdkPixbuf *logo_buf = logo.get_pixbuf();

    GtkWidget *dialog = gtk_about_dialog_new();

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(main_window));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), Constants::application_name.c_str());
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), Constants::application_version.c_str());
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), Constants::application_slogan.c_str());
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), Constants::application_website.c_str());
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog), GTK_LICENSE_MIT_X11);

    gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog), NULL);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo_buf);
    g_object_unref(logo_buf);

    // If focused, set active window in menubar

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
