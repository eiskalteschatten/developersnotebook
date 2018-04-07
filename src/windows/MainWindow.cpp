#include <gtk/gtk.h>

#include "MainWindow.hpp"

// MainWindow::MainWindow(int width, int height, const char* title) {
//     // Default window settings

//     // setupMenuBar();
// }

// void MainWindow::setupMenuBar() {
//     #ifdef __APPLE__
//         Fl_Mac_App_Menu::print = "";
//         Fl_Mac_App_Menu::about = "About Developer's Notebook";
//     #endif

//     Fl_Sys_Menu_Bar *menu_bar;
//     menu_bar = new Fl_Sys_Menu_Bar(0, 0, 640, 30);

//     // File menu
//     menu_bar->add("&File/&New", FL_COMMAND + 'n', (Fl_Callback *)quit_cb, 0, FL_MENU_DIVIDER);

//     #ifndef __APPLE__
//         menu_bar->add("&File/E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0);
//     #endif

//     // Help Menu
//     #ifndef __APPLE__
//         menu_bar->add("&Help/About Developer's Notebook", 0, (Fl_Callback *)quit_cb, 0);
//     #endif
// }
