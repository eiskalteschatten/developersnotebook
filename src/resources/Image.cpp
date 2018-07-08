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


Image::Image(const std::string new_name, const std::string new_extension, const std::string path) : Image(new_name, new_extension, path, -1, -1) {

}

Image::Image(const std::string new_name, const std::string new_extension, const std::string path, const int dest_height, const int dest_width) : Resource(new_name, new_extension, path, "images") {
    height = dest_height;
    width  = dest_width;
}

Image::~Image() {

}

std::string Image::get_svg_content() {
    std::ifstream ifs(path.c_str());
    std::string svg_content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return svg_content;
}

GdkPixbuf* Image::get_pixbuf() {
    GdkPixbuf *pixbuf;

    if (extension == "svg") {
        std::string svg_content = get_svg_content();
        GInputStream *stream    = g_memory_input_stream_new_from_data(svg_content.c_str(), -1, g_free);
        pixbuf                  = gdk_pixbuf_new_from_stream(stream, NULL, NULL);
    }
    else {
        pixbuf = gdk_pixbuf_new_from_file(path.c_str(), NULL);
    }

    if (height == -1 || width == -1) {
        return pixbuf;
    }

    return gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
}

GtkWidget* Image::get_image() {
    return gtk_image_new_from_pixbuf(get_pixbuf());
}
