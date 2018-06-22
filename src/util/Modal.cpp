#include <string>
#include <vector>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include "MacModalInterface.hpp"
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
        mac_show_error_modal(message, sub_message);
    #else
        const int grid_spacing = 10;

        GtkWidget *grid = gtk_grid_new();
        gtk_widget_set_halign(grid, GTK_ALIGN_FILL);
        gtk_widget_set_valign(grid, GTK_ALIGN_FILL);
        gtk_grid_set_column_spacing(GTK_GRID(grid), grid_spacing);
        gtk_grid_set_row_spacing(GTK_GRID(grid), grid_spacing);
        gtk_container_set_border_width(GTK_CONTAINER(grid), grid_spacing);

        gtk_grid_insert_row(GTK_GRID(grid), 0);
        gtk_grid_insert_row(GTK_GRID(grid), 1);
        gtk_grid_insert_column(GTK_GRID(grid), 0);
        gtk_grid_insert_column(GTK_GRID(grid), 1);

        // Image
        GtkWidget *image = gtk_image_new_from_icon_name("dialog-error", GTK_ICON_SIZE_DIALOG);
        gtk_grid_attach(GTK_GRID(grid), image, 0, 0, 1, 2);

        // Message
        GtkWidget *message_label = gtk_label_new(NULL);
        const gchar *format_msg  = "<span font_weight=\"heavy\">\%s</span>";
        const gchar *msg_markup  = g_markup_printf_escaped(format_msg, message.c_str());
        gtk_label_set_markup(GTK_LABEL(message_label), msg_markup);
        gtk_widget_set_halign(message_label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), message_label, 1, 0, 1, 1);

        // Sub message
        GtkWidget *sub_message_label = gtk_label_new(sub_message.c_str());
        gtk_widget_set_halign(sub_message_label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), sub_message_label, 1, 1, 1, 1);

        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog    = gtk_dialog_new_with_buttons("",
                                                           GTK_WINDOW(parent_window),
                                                           flags,
                                                           "OK",
                                                           GTK_RESPONSE_OK,
                                                           NULL);

        gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);

        GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
        gtk_box_pack_start(GTK_BOX(content_area), grid, TRUE, FALSE, 0);
        gtk_widget_show_all(dialog);

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    #endif
}
