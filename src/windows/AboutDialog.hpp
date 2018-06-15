#ifndef AboutDialog_hpp
#define AboutDialog_hpp

#include <gtk/gtk.h>

class AboutDialog {
private:
    AboutDialog();

public:
    static void activate(GtkWidget *menu_item, GtkWidget *main_window);
};

#endif /* AboutDialog_hpp */
