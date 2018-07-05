#ifndef Image_hpp
#define Image_hpp

#include <string>
#include <gtk/gtk.h>

#include "Resource.hpp"


class Image : public Resource {
private:
    int height;
    int width;

public:
    Image(const std::string new_name, const std::string new_extension, const std::string path);
    Image(const std::string new_name, const std::string new_extension, const std::string path, const int dest_height, const int dest_width);
    ~Image();

    std::string get_svg_content();
    GdkPixbuf* get_pixbuf();
};

#endif /* Image_hpp */
