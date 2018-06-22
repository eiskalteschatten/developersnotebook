#ifndef Modal_hpp
#define Modal_hpp

#include <string>
#include <vector>
#include <gtk/gtk.h>

class Modal {
private:
    GtkWidget *parent_window;
    std::string message;
    std::string sub_message;

public:
    Modal(std::string new_message, std::string new_sub_message, GtkWidget *window);
    Modal(std::string new_message, std::string new_sub_message, std::vector<std::string> button_labels, GtkWidget *window);
    ~Modal();

    void show_error_modal();
};

#endif /* Modal_hpp */
