#include <string>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "AboutDialog.hpp"
#include "../constants.hpp"


std::string get_icon_path() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    const std::string path = Constants::path_to_resources + "/images/icon128x128.svg";

    return std::string(std::strcat(cwd, path.c_str()));
}

std::string get_icon_path_mac() {
    #ifdef __APPLE__
        CFURLRef file_url_ref = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("icon128x128"), CFSTR("svg"), NULL);

        if (file_url_ref == NULL) {
            return get_icon_path();
        }

        CFStringRef path                 = CFURLCopyFileSystemPath(file_url_ref, kCFURLPOSIXPathStyle);
        CFStringEncoding encoding_method = CFStringGetSystemEncoding();
        CFRelease(file_url_ref);

        return std::string(CFStringGetCStringPtr(path, encoding_method));
    #else
        return get_icon_path();
    #endif
}

void AboutDialog::activate(GtkWidget *menu_item, GtkWidget *main_window) {
    const gchar *copyright = "(c) Alex Seifert 2018";
    const gchar *website   = "https://www.alexseifert.com";

    std::string icon_path_str;

    #ifdef __APPLE__
        icon_path_str = get_icon_path_mac();
    #else
        icon_path_str = get_icon_path();
    #endif

    std::ifstream ifs(icon_path_str.c_str());
    std::string icon_svg_content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    GInputStream *stream = g_memory_input_stream_new_from_data(icon_svg_content.c_str(), -1, g_free);
    GdkPixbuf *logo      = gdk_pixbuf_new_from_stream(stream, NULL, NULL);

    GtkWidget *dialog = gtk_about_dialog_new();

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(main_window));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), Constants::application_name.c_str());
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), Constants::application_version.c_str());
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), copyright);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), Constants::application_slogan.c_str());
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), website);

    gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog), NULL);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
    g_object_unref(logo);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
