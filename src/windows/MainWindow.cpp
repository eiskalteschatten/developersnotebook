#include <FL/Fl.H>
#include <FL/Fl_Sys_Menu_Bar.H>

#include "MainWindow.hpp"

void quit_cb(Fl_Widget*, void*) {
  exit(0);
}

MainWindow::MainWindow(int width, int height, const char* title): Fl_Double_Window(width, height, title) {
    // Default window settings
    this->size_range(1, 1);

    setupMenuBar();
}

void MainWindow::setupMenuBar() {
    #ifdef __APPLE__
        Fl_Mac_App_Menu::print = "";
    #endif

    Fl_Sys_Menu_Bar *menu_bar;
    menu_bar = new Fl_Sys_Menu_Bar(0, 0, 640, 30);

    // File menu
    menu_bar->add("&File/&New", FL_COMMAND + 'n', (Fl_Callback *)quit_cb, 0);

    #ifndef __APPLE__
        menu_bar->add("&File/E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0);
    #endif

    // Help Menu
    #ifndef __APPLE__
        menu_bar->add("&Help/About", 0, (Fl_Callback *)quit_cb, 0);
    #endif
}
