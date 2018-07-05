#ifndef ReleaseNotesWindow_hpp
#define ReleaseNotesWindow_hpp

#include <gtk/gtk.h>

#include "MenuBar.hpp"


class ReleaseNotesWindow {
private:
    std::string path_to_exec_str;

    void fill_release_notes(GtkTextBuffer *buffer);

public:
    ReleaseNotesWindow(std::string path);
    ~ReleaseNotesWindow();

    static void activate(GtkWidget *menu_item, void *main_window_obj);
};

#endif /* ReleaseNotesWindow_hpp */
