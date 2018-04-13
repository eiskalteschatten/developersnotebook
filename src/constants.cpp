// Global constants

#include <cstdlib>
#include <string>

using namespace std;

#if defined(__APPLE__) || defined(__linux__)
    string path_to_config_str = string(getenv("HOME")) + "/.devnotebook/";
    const char *PATH_TO_CONFIG = path_to_config_str.c_str();
#else
    const char *PATH_TO_CONFIG = "C:\\";
#endif

string path_to_db_str = string(PATH_TO_CONFIG) + "developersnotebook.db";
const char *PATH_TO_DB = path_to_db_str.c_str();
