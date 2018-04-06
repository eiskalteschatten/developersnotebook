#include <FL/Fl.H>

#include "MainWindow.hpp"

void quit_cb(Fl_Widget*, void*) {
  exit(0);
}

Fl_Menu_Item menu_items[] = {
    { "&File",              0, 0, 0, FL_SUBMENU },
        { "E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0 },
        { 0 },
    { 0 }
};


MainWindow::MainWindow(int width, int height, const char* title): Fl_Double_Window(width, height, title) {
    menu_bar = new Fl_Menu_Bar(0, 0, 640, 30);
    menu_bar->copy(menu_items);
}
