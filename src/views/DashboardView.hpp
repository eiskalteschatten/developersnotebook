#ifndef DashboardView_hpp
#define DashboardView_hpp

#include <string>

#include "AbstractView.hpp"

class DashboardView : public AbstractView {
private:
    GtkWidget *release_notes_text_view;
    GtkWidget *projects_ending_soon_tree_view;

    std::string release_notes_file_name = "release-notes";
    std::string release_notes_extension = "html";

    std::string get_release_notes_path();
    std::string get_release_notes_path_mac();
    void fill_release_notes();
    void fill_projects_ending_soon();

public:
    DashboardView();
    ~DashboardView();
};

#endif /* DashboardView_hpp */
