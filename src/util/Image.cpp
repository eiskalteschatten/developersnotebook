#include <unistd.h>
#include <fstream>
#include <gtk/gtk.h>

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include "Image.hpp"
#include "../constants.hpp"


Image::Image(const std::string new_name, const std::string new_extension) {
    name      = new_name;
    extension = new_extension;

    #ifdef __APPLE__
        image_path = get_icon_path_mac();
    #else
        image_path = get_icon_path();
    #endif
}

Image::~Image() {

}

std::string Image::get_icon_path() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    const std::string path = Constants::path_to_resources + "/images/" + name + "." + extension;

    return std::string(std::strcat(cwd, path.c_str()));
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
