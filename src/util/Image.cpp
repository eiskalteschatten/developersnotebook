#include <boost/filesystem.hpp>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "Image.hpp"
#include "../constants.hpp"

namespace fs = boost::filesystem;


Image::Image(const std::string new_name, const std::string new_extension, const std::string path) {
    name             = new_name;
    extension        = new_extension;
    path_to_exec_str = path;

    #ifdef __APPLE__
        image_path = get_icon_path_mac();
    #else
        image_path = get_icon_path();
    #endif
}

Image::~Image() {

}

std::string Image::get_icon_path() {
    fs::path path_to_exec = path_to_exec_str;
    path_to_exec.remove_filename();
    path_to_exec /= Constants::path_to_resources;

    if (!fs::is_directory(path_to_exec)) {
        path_to_exec.remove_leaf();
        path_to_exec.remove_leaf();
    }

    path_to_exec /= Constants::path_to_resources;
    path_to_exec /= "images";
    path_to_exec /= name + "." + extension;

    return path_to_exec.string();
}

std::string Image::get_icon_path_mac() {
    #ifdef __APPLE__
        CFStringRef apple_name      = CFStringCreateWithCString(NULL, name.c_str(), kCFStringEncodingUTF8);
        CFStringRef apple_extension = CFStringCreateWithCString(NULL, extension.c_str(), kCFStringEncodingUTF8);
        CFURLRef file_url_ref       = CFBundleCopyResourceURL(CFBundleGetMainBundle(), apple_name, apple_extension, NULL);

        if (file_url_ref == NULL) {
            return get_icon_path();
        }

        CFStringRef path                 = CFURLCopyFileSystemPath(file_url_ref, kCFURLPOSIXPathStyle);
        CFStringEncoding encoding_method = CFStringGetSystemEncoding();
        CFRelease(file_url_ref);

        return std::string(CFStringGetCStringPtr(path, encoding_method));
    #else
        return get_icon_path();
    #endif
}

std::string Image::get_svg_content() {
    std::ifstream ifs(image_path.c_str());
    std::string svg_content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return svg_content;
}

GdkPixbuf* Image::get_pixbuf() {
    std::string svg_content = get_svg_content();
    GInputStream *stream = g_memory_input_stream_new_from_data(svg_content.c_str(), -1, g_free);
    return gdk_pixbuf_new_from_stream(stream, NULL, NULL);
}
