#ifndef WindowRegistry_hpp
#define WindowRegistry_hpp

#include "MainWindow.hpp"


class WindowRegistry {
private:
    WindowRegistry();
    ~WindowRegistry();

    WindowRegistry(WindowRegistry const&)  = delete;  // Delete the copy constructor
    WindowRegistry(WindowRegistry const&&) = delete; // Delete the move constructor

    std::vector<MainWindow*> windows;

public:
    static WindowRegistry& get_instance();

    void add_window(MainWindow* window);
    std::vector<MainWindow*> const& get_windows() const { return windows; }
    MainWindow *get_window(int i);
    int get_instance_index(MainWindow *instance);
};

#endif /* WindowRegistry_hpp */
