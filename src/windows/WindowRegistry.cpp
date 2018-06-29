#include <string>
#include <vector>

#include "WindowRegistry.hpp"

WindowRegistry::WindowRegistry() {

}

WindowRegistry::~WindowRegistry() {

}

WindowRegistry& WindowRegistry::get_instance() {
    static WindowRegistry instance;
    return instance;
}

void WindowRegistry::add_window(MainWindow *window) {
    windows.push_back(window);
}

void WindowRegistry::remove_window(MainWindow *instance) {
    int i = get_instance_index(instance);
    remove_window(i);
}

void WindowRegistry::remove_window(int i) {
    windows.erase(windows.begin() + i);
}

MainWindow *WindowRegistry::get_window(int i) {
    return windows.at(i);
}

int WindowRegistry::get_instance_index(MainWindow *instance) {
    int i;
    for (i = 0; i < windows.size(); i++) {
        if (windows.at(i) == instance) {
            break;
        }
    }

    return i;
}
