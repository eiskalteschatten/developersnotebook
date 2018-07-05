#ifndef Modal_hpp
#define Modal_hpp

#include <string>
#include <vector>
#include <gtk/gtk.h>

enum {
    MODAL_RESPONSE_ACCEPT,
    MODAL_RESPONSE_REJECT
};


class Modal {
private:
    GtkWidget *parent_window;

    #ifndef __APPLE__
        GtkWidget *main_grid;
    #endif

    std::string message;
    std::string sub_message;

public:
    Modal(std::string new_message, std::string new_sub_message, GtkWidget *window);
    ~Modal();

    void show_error_modal();
    int show_confirm_modal(std::string accept_button, std::string reject_button);
};

#endif /* Modal_hpp */
