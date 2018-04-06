#include <FL/Fl.H>
#include <FL/Fl_Menu_Item.H>

#include "MainWindow.hpp"

Fl_Menu_Item menuitems[] = {
    { "&File",              0, 0, 0, FL_SUBMENU },
        { "&New File",        0, (Fl_Callback *)new_cb },
        { "&Open File...",    FL_COMMAND + 'o', (Fl_Callback *)open_cb },
        { "&Insert File...",  FL_COMMAND + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
        { "&Save File",       FL_COMMAND + 's', (Fl_Callback *)save_cb },
        { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
        { "New &View", FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
        { "&Close View", FL_COMMAND + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER },
        { "E&xit", FL_COMMAND + 'q', (Fl_Callback *)quit_cb, 0 },
        { 0 },
    { "&Edit", 0, 0, 0, FL_SUBMENU },
        { "&Undo",       FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
        { "Cu&t",        FL_COMMAND + 'x', (Fl_Callback *)cut_cb },
        { "&Copy",       FL_COMMAND + 'c', (Fl_Callback *)copy_cb },
        { "&Paste",      FL_COMMAND + 'v', (Fl_Callback *)paste_cb },
        { "&Delete",     0, (Fl_Callback *)delete_cb },
        { 0 },
    { "&Search", 0, 0, 0, FL_SUBMENU },
        { "&Find...",       FL_COMMAND + 'f', (Fl_Callback *)find_cb },
        { "F&ind Again",    FL_COMMAND + 'g', find2_cb },
        { "&Replace...",    FL_COMMAND + 'r', replace_cb },
        { "Re&place Again", FL_COMMAND + 't', replace2_cb },
        { 0 },
    { 0 }
};

MainWindow::MainWindow(int width, int height, const char* title): Fl_Double_Window(width, height, title) {
    // textbuf = new Fl_Text_Buffer;
}
