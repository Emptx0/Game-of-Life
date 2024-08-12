#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include <iostream>
#include <string>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13

using namespace std;

void set_color_menu(int a, int b) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (a + (b * 16)));
}

void set_cursor_menu(int a, int b) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdOut, { static_cast<SHORT>(a), static_cast<SHORT>(b) });
}

void Menu::set_window_settings() {
    SetConsoleTitleW(L"Game of life");

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = false;
    structCursorInfo.dwSize = 100;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    HWND console = GetConsoleWindow();
    HWND consoleWindow = GetConsoleWindow();
    HANDLE stdHndl = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(70), static_cast<SHORT>(40) };
    DWORD style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

    SetWindowPos(consoleWindow, nullptr, 300, 20, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetConsoleWindowInfo(stdHndl, TRUE, &windowSize);
    SetWindowLong(console, GWL_STYLE, style);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 13;
    cfi.dwFontSize.Y = 17;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    system("color 97");
}

bool Menu::main_menu() {

    m_active_menu = 0;

    while(true) {
        set_cursor_menu(23, 16);
        set_color_menu(9,7);
        cout << "       GAME OF LIFE       ";
        set_color_menu(7,9);

        for (int i = 0; i < size(m_menu); i++) {
            if (i == m_active_menu) {
                set_cursor_menu(23, i + 18);
                cout << "-> " << m_menu[i];
            }
            else {
                set_cursor_menu(26, i + 18);
                cout << m_menu[i];
            }
        }

        m_key = _getch();
        if (m_key == -32) m_key = _getch();
        if (m_key == UP && m_active_menu != 0) {
            system("cls");
            --m_active_menu;
        }
        else if (m_key == DOWN && m_active_menu != size(m_menu) - 1) {
            system("cls");
            ++m_active_menu;
        }
        else if (m_key == ENTER) {
            system("cls");
            if (m_active_menu == 1 || m_active_menu == 0) {
                cg_menu();
            }
            else if (m_active_menu == 2) {
                rules_menu();
            }
            else if (m_active_menu == 3)
                return false;
            break;
        }
    }
    return true;
}

void Menu::cg_menu() {
    short active_menu_cg = 0;

    while (true) {
        cout << "<- esc";
        set_cursor_menu(24, 0);
        
        cout << "\n\n   Field size: " << m_x << "x" << m_y << endl;
        if (active_menu_cg == 0) {
            set_cursor_menu(22, 4);
            cout << "-> Change";
        }
        else {
            set_cursor_menu(25, 4);
            cout << "Change";
        }
        if (active_menu_cg == 1) {
            set_cursor_menu(33, 4);
            cout << "-> Continue";
        }
        else {
            set_cursor_menu(36, 4);
            cout << "Continue";
        }

        m_key = _getch();
        if (m_key == -32) m_key = _getch();
        if (m_key == LEFT && active_menu_cg != 0) {
            system("cls");
            --active_menu_cg;
        }
        else if (m_key == RIGHT && active_menu_cg != 1) {
            system("cls");
            ++active_menu_cg;
        }
        else if (m_key == ESC) {
            system("cls");
            main_menu();
            break;
        }
        else if (m_key == ENTER) {
            system("cls");
            if (active_menu_cg == 0) {
                system("cls");
                cout << "Min size: 1x1\n"
                        "Max size: 32x32\n";
                while (true) {
                    cout << "Enter field width: ";
                    cin >> m_x;
                    cout << "Enter field high: ";
                    cin >> m_y;

                    if (m_x > 32 || m_x < 1 || m_y > 32 || m_y < 1) {
                        set_color_menu(4, 9);
                        cout << "Values are out of range!\n";
                        set_color_menu(7, 9);
                    }
                    else
                        break;
                }
                break;
            }
            else
                break;
        }
        else
            system("cls");
    }
}

void Menu::print_rules() {
    cout << "<- esc";
    set_cursor_menu(3, 2);
    set_color_menu(9, 7);

    for (int i = 0; i <= 29; i++)
        cout << " ";
    cout << "Rules";
    for (int i = 0; i <= 29; i++)
        cout << " ";

    set_color_menu(7, 9);
    set_cursor_menu(8, 4);
    cout << "The universe of the Game of Life is an infinite, ";
    set_cursor_menu(4, 5);
    cout << "two-dimensional orthogonal grid of square cells each of which";
    set_cursor_menu(4, 6);
    cout << "is in one of two possible states ";
    set_color_menu(2, 9);
    cout << "live ";
    set_color_menu(7, 9);
    cout << "or ";
    set_color_menu(4, 9);
    cout << "dead.";
    set_color_menu(7, 9);
    cout << " Every cell";
    set_cursor_menu(4, 7);
    cout << "interacts with its eight neighbors, which are the cells that";
    set_cursor_menu(4, 8);
    cout << "are horizontally, vertically, or diagonally adjacent.";
    set_cursor_menu(4, 9);
    cout << "At each step in time, the following transitions occur:";

    set_cursor_menu(4, 11);
    cout << "1) Any live cell with fewer than ";
    set_color_menu(14, 9);
    cout << "2";
    set_color_menu(7, 9);
    cout << " live neighbors";
    set_color_menu(4, 9);
    cout << " dies";
    set_color_menu(7, 9);
    cout << ", as if";
    set_cursor_menu(4, 12);
    cout << "by underpopulation.";

    set_cursor_menu(4, 13);
    cout << "2) Any live cell with ";
    set_color_menu(14, 9);
    cout << "2";
    set_color_menu(7, 9);
    cout << " or ";
    set_color_menu(14, 9);
    cout << "3";
    set_color_menu(7, 9);
    cout << " live neighbors";
    set_color_menu(2, 9);
    cout << " lives ";
    set_color_menu(7, 9);
    cout << "on to the";
    set_cursor_menu(4, 14);
    cout << "next generation.";

    set_cursor_menu(4, 15);
    cout << "3) Any live cell with more than ";
    set_color_menu(14, 9);
    cout << "3";
    set_color_menu(7, 9);
    cout << " live neighbors";
    set_color_menu(4, 9);
    cout << " dies";
    set_color_menu(7, 9);
    cout << ",";
    set_cursor_menu(4, 16);
    cout << "as if by overpopulation.";

    set_cursor_menu(4, 17);
    cout << "4) Any dead cell with exactly ";
    set_color_menu(14, 9);
    cout << "3";
    set_color_menu(7, 9);
    cout << " live neighbors becomes a";
    set_cursor_menu(4, 18);
    set_color_menu(2, 9);
    cout << "live ";
    set_color_menu(7, 9);
    cout << "cell, as if by reproduction.";
}

void Menu::rules_menu() {
    while (true) {
        print_rules();

        m_key = _getch();
        if (m_key == ESC) {
            system("cls");
            main_menu();
            break;
        }
    }
}
