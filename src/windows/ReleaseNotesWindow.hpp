#ifndef ReleaseNotesWindow_hpp
#define ReleaseNotesWindow_hpp

#include <gtk/gtk.h>

#include "MenuBar.hpp"


class ReleaseNotesWindow {
private:
    std::string release_notes_file_name = "release-notes";
    std::string release_notes_extension = "html";

    std::string get_release_notes_path();
    std::string get_release_notes_path_mac();
    void fill_release_notes(GtkTextBuffer *buffer);

public:
    ReleaseNotesWindow();
    ~ReleaseNotesWindow();

    static void activate(GtkWidget *menu_item, void *main_window_obj);
};

#endif /* ReleaseNotesWindow_hpp */
