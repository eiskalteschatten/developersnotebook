#ifndef DashboardView_hpp
#define DashboardView_hpp

#include <string>

#include "AbstractView.hpp"

class DashboardView : public AbstractView {
private:
    GtkWidget *release_notes_text_view;
    GtkWidget *projects_ending_soon_tree_view;

    void fill_projects_ending_soon();

public:
    DashboardView();
    ~DashboardView();
};

#endif /* DashboardView_hpp */
