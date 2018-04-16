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
}

#endif /* Constants_hpp */
