#include <FL/Fl.H>

#include "windows/MainWindow.hpp"

int main(int argc, char **argv) {
    MainWindow *window = new MainWindow(1000, 700, "Developer's Notebook");
    window->size_range(1, 1);
    window->show(argc, argv);
    return Fl::run();
}
