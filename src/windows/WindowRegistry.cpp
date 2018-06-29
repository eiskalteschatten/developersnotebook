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

void WindowRegistry::add_window(MainWindow* window) {
    windows.push_back(window);
}
