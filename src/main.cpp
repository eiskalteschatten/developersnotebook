#include <FL/Fl.H>

#include "windows/MainWindow.hpp"

int main(int argc, char **argv) {
    MainWindow *window = new MainWindow(500, 300, "Develoepr's Notebook");
    window->show(argc, argv);
    return Fl::run();
}
