#ifndef DashboardView_hpp
#define DashboardView_hpp

#include <string>

#include "AbstractView.hpp"

class DashboardView : public AbstractView {
private:
    std::string release_notes_file_name = "release-notes";
    std::string release_notes_extension = "rtf";

    std::string get_release_notes_path();
    std::string get_release_notes_path_mac();

public:
    DashboardView();
    ~DashboardView();
};

#endif /* DashboardView_hpp */
