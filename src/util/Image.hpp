#ifndef Image_hpp
#define Image_hpp

#include <string>
#include <gtk/gtk.h>

class Image {
private:
    std::string path_to_exec_str;
    std::string name;
    std::string extension;
    std::string image_path;
    int height;
    int width;

public:
    Image(const std::string new_name, const std::string new_extension, const std::string path);
    Image(const std::string new_name, const std::string new_extension, const std::string path, const int dest_height, const int dest_width);
    ~Image();

    std::string get_icon_path();
    std::string get_icon_path_mac();
    std::string get_svg_content();
    GdkPixbuf* get_pixbuf();

    std::string get_name() { return name; }
    void set_name(std::string new_name) { name = new_name; }
    std::string get_extension() { return extension; }
    void set_extension(std::string new_extension) { extension = new_extension; }
    std::string get_image_path() { return image_path; }
    void set_image_path(std::string new_image_path) { image_path = new_image_path; }
};

#endif /* Image_hpp */
