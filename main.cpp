#include <iostream>
#include "Field.h"
#include "Menu.h"

int main() {
    Menu menu;
    menu.set_window_settings();
    if (!menu.main_menu()) {
        return 0;
    }
    Field game(menu.getX(), menu.getY(), menu.getActiveMenu());
    game.run();

    while (menu.main_menu()) {
        menu.main_menu();
        game.regenerate_array(menu.getX(), menu.getY());
        game.setActiveMenu(menu.getActiveMenu());
        game.run();
    }

    return 0;
}
