#include <iostream>

#include "MainWindow.hpp"

MainWindow::MainWindow(int width, int height, const char* title): Fl_Double_Window(width, height, title) {
    std::cout << "mainwindow constructor";

    // textbuf = new Fl_Text_Buffer;
}

MainWindow::~MainWindow() {

}
