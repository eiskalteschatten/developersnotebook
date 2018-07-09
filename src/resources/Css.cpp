#include <gtk/gtk.h>

#include "Css.hpp"


Css::Css(const std::string new_name, const std::string path) : Resource(new_name, "css", path, "css") {

}

Css::~Css() {

}
