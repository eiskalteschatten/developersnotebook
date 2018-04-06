#ifndef MainWindow_hpp
#define MainWindow_hpp

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

class MainWindow: public Fl_Double_Window {
private:

    void setupMenuBar();

public:
    MainWindow(int width, int height, const char* title);
    virtual ~MainWindow() {};
};

#endif /* MainWindow_hpp */
