#include <boost/filesystem.hpp>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "Resource.hpp"
#include "../constants.hpp"

namespace fs = boost::filesystem;


Resource::Resource(const std::string new_name, const std::string new_extension, const std::string new_path_to_exec, std::string new_sub_folders) {
    name             = new_name;
    extension        = new_extension;
    path_to_exec_str = new_path_to_exec;
    sub_folders      = new_sub_folders;

    #ifdef __APPLE__
        path = get_resource_path_mac();
    #else
        path = get_resource_path();
    #endif
}

Resource::~Resource() {

}

std::string Resource::get_resource_path() {
    fs::path path_to_exec = path_to_exec_str;
    path_to_exec.remove_filename();
    path_to_exec /= Constants::path_to_resources;

    if (!fs::is_directory(path_to_exec)) {
        path_to_exec.remove_leaf();
        path_to_exec.remove_leaf();
        path_to_exec /= Constants::path_to_resources;
    }

    path_to_exec /= sub_folders;
    path_to_exec /= name + "." + extension;

    return path_to_exec.string();
}

std::string Resource::get_resource_path_mac() {
    #ifdef __APPLE__
        CFStringRef apple_name      = CFStringCreateWithCString(NULL, name.c_str(), kCFStringEncodingUTF8);
        CFStringRef apple_extension = CFStringCreateWithCString(NULL, extension.c_str(), kCFStringEncodingUTF8);
        CFURLRef file_url_ref       = CFBundleCopyResourceURL(CFBundleGetMainBundle(), apple_name, apple_extension, NULL);

        if (file_url_ref == NULL) {
            return get_resource_path();
        }

        CFStringRef path                 = CFURLCopyFileSystemPath(file_url_ref, kCFURLPOSIXPathStyle);
        CFStringEncoding encoding_method = CFStringGetSystemEncoding();
        CFRelease(file_url_ref);

        return std::string(CFStringGetCStringPtr(path, encoding_method));
    #else
        return get_resource_path();
    #endif
}
