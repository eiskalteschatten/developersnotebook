#ifndef WindowRegistry_hpp
#define WindowRegistry_hpp

#include "MainWindow.hpp"


class WindowRegistry {
private:
    std::vector<MainWindow*> windows;

public:
    WindowRegistry();
    ~WindowRegistry();

    std::vector<MainWindow*> const& get_windows() const { return windows; };
};

#endif /* WindowRegistry_hpp */
