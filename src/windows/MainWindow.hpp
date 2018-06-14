#ifndef MainWindow_hpp
#define MainWindow_hpp

class MainWindow {
private:
    GtkWidget *window;
    GtkWidget *grid;

    void setup_grid();
    void setup_stack();
    static void save_window(GtkWidget *window, gpointer user_data);

public:
    MainWindow();
    ~MainWindow();

    static void activate(GtkApplication *app, MainWindow *mw);
};

#endif /* MainWindow_hpp */
