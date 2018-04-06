#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
// FOR MAC: #include <FL/Fl_Sys_Menu_Bar.H>
// #include <FL/Fl_Window.H>
// #include <FL/Fl_Input.H>
// #include <FL/Fl_Button.H>
// #include <FL/Fl_Return_Button.H>
// #include <FL/Fl_Text_Editor.H>
// #include <FL/Fl_Text_Buffer.H>

class MainWindow: public Fl_Double_Window {
private:

    void setupMenuBar();

public:
    MainWindow(int width, int height, const char* title);
    virtual ~MainWindow() {};

    Fl_Menu_Bar *menu_bar;

    // Fl_Window        *replace_dlg;
    // Fl_Input         *replace_find;
    // Fl_Input         *replace_with;
    // Fl_Button        *replace_all;
    // Fl_Return_Button *replace_next;
    // Fl_Button        *replace_cancel;
    // Fl_Text_Editor   *editor;
    // Fl_Text_Buffer   *textbuf;

    // char search[256];
};

#endif /* MainWindow_hpp */
