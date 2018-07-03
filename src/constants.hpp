#ifndef Constants_hpp
#define Constants_hpp

#include <cstdlib>
#include <string>

namespace Constants {
    #if defined(__APPLE__) || defined(__linux__)
        const std::string path_to_config = std::string(getenv("HOME")) + "/.devnotebook/";
    #else
        const std::string path_to_config = std::string(getenv("APPDATA")) + "/.devnotebook/";
    #endif

    const std::string path_to_resources         = "/resources";
    const std::string application_icon_path     = path_to_resources + "/images/icon.png";
    const std::string application_icon_path_svg = path_to_resources + "/images/icon.svg";

    const std::string path_to_db = path_to_config + "developersnotebook.db";

    const std::string application_name     = "Developer's Notebook";
    const std::string application_exec     = "developersnotebook";
    const std::string application_version  = "0.1";
    const std::string application_slogan   = "A digital notebook for developers";
    const std::string application_website  = "https://www.alexseifert.com";

    const std::string default_date_format      = "%a, %d %B %Y";
    const std::string default_date_time_format = default_date_format + " %T";
}

#endif /* Constants_hpp */
