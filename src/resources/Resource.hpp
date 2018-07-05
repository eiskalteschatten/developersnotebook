#ifndef Resource_hpp
#define Resource_hpp

#include <string>
#include <gtk/gtk.h>


class Resource {
protected:
    std::string path_to_exec_str;
    std::string name;
    std::string extension;
    std::string path;
    std::string sub_folders;

public:
    Resource(const std::string new_name, const std::string new_extension, const std::string new_path_to_exec);
    Resource(const std::string new_name, const std::string new_extension, const std::string new_path_to_exec, const std::string new_sub_folders);
    ~Resource();

    std::string get_resource_path();
    std::string get_resource_path_mac();

    std::string get_name() { return name; }
    void set_name(std::string new_name) { name = new_name; }
    std::string get_extension() { return extension; }
    void set_extension(std::string new_extension) { extension = new_extension; }
    std::string get_path() { return path; }
    void set_path(std::string new_path) { path = new_path; }
};

#endif /* Resource_hpp */
