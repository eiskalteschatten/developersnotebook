#ifndef Css_hpp
#define Css_hpp

#include <string>
#include <gtk/gtk.h>

#include "Resource.hpp"


class Css : public Resource {
private:

public:
    Css(const std::string new_name, const std::string path);
    ~Css();
};

#endif /* Css_hpp */
