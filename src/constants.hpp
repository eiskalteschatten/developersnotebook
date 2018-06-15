#ifndef Constants_hpp
#define Constants_hpp

#include <cstdlib>
#include <string>

namespace Constants {
    #if defined(__APPLE__) || defined(__linux__)
        const std::string path_to_config = std::string(getenv("HOME")) + "/.devnotebook/";
    #else
        const std::string path_to_config = "C:\\";
    #endif

    const std::string path_to_db = path_to_config + "developersnotebook.db";

    const std::string application_name    = "Developer's Notebook";
    const std::string application_version = "0.1";

    const std::string default_date_format      = "%a, %d %B %Y";
    const std::string default_date_time_format = default_date_format + " %T";

    const char *application_icon_path = "/resources/images/icon.png";
}

#endif /* Constants_hpp */
