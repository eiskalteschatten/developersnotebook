#include <FL/Fl.H>

#include "windows/MainWindow.hpp"

int main(int argc, char **argv) {
    MainWindow *window = new MainWindow(500, 300, "Develoepr's Notebook");

    window->show(argc, argv);

    //if (argc > 1) load_file(argv[1], -1);

    return Fl::run();
}
