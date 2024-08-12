#include <string>
#ifndef GAME_OF_LIFE_MENU_H
#define GAME_OF_LIFE_MENU_H

class Menu {
    std::string m_menu[4] = { "Random configuration",
                              "Create configuration",
                              "     Game rules",
                              "        Exit"         };
    short m_x = 30, m_y = 30;
    char m_key;
    short m_active_menu;
public:
    void run_menu();
    static void set_window_settings();
    bool main_menu();
    void cg_menu();
    void rules_menu();
    void print_rules();

    short getActiveMenu() { return m_active_menu; }
    int getX() { return m_x; }
    int getY() { return m_y; }
};


#endif //GAME_OF_LIFE_MENU_H
