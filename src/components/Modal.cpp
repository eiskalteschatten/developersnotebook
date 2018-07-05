#include <string>
#include <vector>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include "MacModalInterface.hpp"
#endif

#include "Modal.hpp"

enum {
   NSAlertFirstButtonReturn  = 1000,
   NSAlertSecondButtonReturn = 1001,
   NSAlertThirdButtonReturn  = 1002
};


Modal::Modal(std::string new_message, std::string new_sub_message, GtkWidget *window) {
    message       = new_message;
    sub_message   = new_sub_message;
    parent_window = window;

    #ifndef __APPLE__
        const int grid_spacing = 10;

        main_grid = gtk_grid_new();
        gtk_widget_set_halign(main_grid, GTK_ALIGN_FILL);
        gtk_widget_set_valign(main_grid, GTK_ALIGN_FILL);
        gtk_grid_set_column_spacing(GTK_GRID(main_grid), grid_spacing);
        gtk_grid_set_row_spacing(GTK_GRID(main_grid), grid_spacing);
        gtk_container_set_border_width(GTK_CONTAINER(main_grid), grid_spacing);

        gtk_grid_insert_row(GTK_GRID(main_grid), 0);
        gtk_grid_insert_row(GTK_GRID(main_grid), 1);
        gtk_grid_insert_column(GTK_GRID(main_grid), 0);
        gtk_grid_insert_column(GTK_GRID(main_grid), 1);

        // Message
        GtkWidget *message_label = gtk_label_new(NULL);
        const gchar *format_msg  = "<span font_weight=\"heavy\">\%s</span>";
        const gchar *msg_markup  = g_markup_printf_escaped(format_msg, message.c_str());
        gtk_label_set_markup(GTK_LABEL(message_label), msg_markup);
        gtk_widget_set_halign(message_label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(main_grid), message_label, 1, 0, 1, 1);

        // Sub message
        GtkWidget *sub_message_label = gtk_label_new(sub_message.c_str());
        gtk_widget_set_halign(sub_message_label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(main_grid), sub_message_label, 1, 1, 1, 1);
    #endif
}

Modal::~Modal() {

}

void Modal::show_error_modal() {
    #ifdef __APPLE__
        mac_show_error_modal(message, sub_message);
    #else
        GtkWidget *image = gtk_image_new_from_icon_name("dialog-error", GTK_ICON_SIZE_DIALOG);
        gtk_grid_attach(GTK_GRID(main_grid), image, 0, 0, 1, 2);

        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog    = gtk_dialog_new_with_buttons("",
                                                           GTK_WINDOW(parent_window),
                                                           flags,
                                                           "OK",
                                                           GTK_RESPONSE_OK,
                                                           NULL);

        gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        gtk_box_pack_start(GTK_BOX(content_area), main_grid, TRUE, FALSE, 0);
        gtk_widget_show_all(dialog);

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    #endif
}

int Modal::show_confirm_modal(std::string accept_button, std::string reject_button) {
    #ifdef __APPLE__
        int result = mac_show_confirm_modal(message, sub_message, accept_button, reject_button);
        return result == NSAlertFirstButtonReturn ? MODAL_RESPONSE_ACCEPT : MODAL_RESPONSE_REJECT;
    #else
        GtkWidget *image = gtk_image_new_from_icon_name("dialog-warning", GTK_ICON_SIZE_DIALOG);
        gtk_grid_attach(GTK_GRID(main_grid), image, 0, 0, 1, 2);

        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog    = gtk_dialog_new_with_buttons("",
                                                           GTK_WINDOW(parent_window),
                                                           flags,
                                                           reject_button.c_str(),
                                                           GTK_RESPONSE_REJECT,
                                                           accept_button.c_str(),
                                                           GTK_RESPONSE_ACCEPT,
                                                           NULL);

        gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        gtk_box_pack_start(GTK_BOX(content_area), main_grid, TRUE, FALSE, 0);
        gtk_widget_show_all(dialog);

        int result = gtk_dialog_run(GTK_DIALOG(dialog));

        gtk_widget_destroy(dialog);

        return result == GTK_RESPONSE_ACCEPT ? MODAL_RESPONSE_ACCEPT : MODAL_RESPONSE_REJECT;
    #endif
}
