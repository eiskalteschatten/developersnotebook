#ifndef MainWindow_hpp
#define MainWindow_hpp

class MainWindow {
private:
    MainWindow();

    static void setup_grid();
    static void setup_stack();

public:
    static void activate(GtkApplication *app, gpointer user_data);
};

#endif /* MainWindow_hpp */
