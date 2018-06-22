#include <string>
#include <vector>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "Modal.hpp"


Modal::Modal(std::string new_message, std::string new_sub_message, GtkWidget *window) {
    message       = new_message;
    sub_message   = new_sub_message;
    parent_window = window;
}

Modal::Modal(std::string new_message, std::string new_sub_message, std::vector<std::string> button_labels, GtkWidget *window) {
    message       = new_message;
    sub_message   = new_sub_message;
    parent_window = window;
}

Modal::~Modal() {

}

void Modal::show_error_modal() {
    #ifdef __APPLE__
        // DialogRef alert;
        // CreateStandardAlert(kAlertStopAlert, CFSTR("some message"), CFSTR("some sub message"), NULL, &alert);
    #else
        GtkWidget *image = gtk_image_new_from_icon_name("dialog-error", GTK_ICON_SIZE_DIALOG);
        GtkWidget *label = gtk_label_new(message.c_str());
        GtkWidget *hbox  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

        gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
        gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX(hbox), label, TRUE, FALSE, 0);

        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog    = gtk_dialog_new_with_buttons("",
                                                        GTK_WINDOW(parent_window),
                                                        flags,
                                                        "OK",
                                                        GTK_RESPONSE_OK,
                                                        NULL);

        gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        gtk_box_pack_start(GTK_BOX(content_area), hbox, TRUE, FALSE, 0);
        gtk_widget_show_all(dialog);

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    #endif
}
