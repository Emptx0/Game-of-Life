#include <windows.h>
#include <conio.h>
#include "Field.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13
#define SPACE 32
#define E 0x45
#define Q 0x51

using namespace std;

void set_color_field(int a, int b) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (a + (b * 16)));
}

void set_cursor_field(int a, int b) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdOut, { static_cast<SHORT>(a), static_cast<SHORT>(b) });
}

Field::Field(int x, int y, short active_menu) {
    m_action = active_menu;
    m_x = x + 2;
    m_y = y + 2;
    arr = new int*[m_y];
    for (int i = 0; i < m_y; i++)
        arr[i] = new int[m_x];

    for (int i = 0; i < m_y; i++)
        for (int j = 0; j < m_x; j++)
            arr[i][j] = 0;
}

Field::~Field() {
    for (int i = 0; i < m_y; i++)
        delete[] arr[i];
    delete[] arr;
}

void Field::regenerate_array(int x, int y) {
    for (int i = 0; i < m_y; i++)
        for (int j = 0; j < m_x; j++)
            arr[i][j] = 0;

    for (int i = 0; i < m_y; i++)
        delete[] arr[i];
    delete[] arr;

    m_x = x + 2;
    m_y = y + 2;

    int **newArr = new int*[m_y];
    for (int i = 0; i < m_y; i++)
        newArr[i] = new int[m_x];

    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
            newArr[i][j] = 0;

    arr = newArr;
}

void Field::random_generate() {
    srand(time(NULL));
    for (int i = 1; i < m_y - 1; i++)
        for (int j = 1; j < m_x - 1; j++)
            arr[i][j] = rand() % 2;
}

void Field::custom_generate() {
    cout << m_x - 2 << "x" << m_y - 2 << endl;
    short m_active_menu_x = 1;
    short m_active_menu_y = 1;
    while(true) {
        set_cursor_field(0, 0);
        print();
        cout << "Cursor position: " << m_active_menu_x << " , " << m_active_menu_y << " ";
        cout << "\n\nMoving by arrows.";
        cout << " \nPress ";
        set_color_field(14, 9);
        cout << "ENTER";
        set_color_field(7, 9);
        cout << " to put cell.";
        cout << "\nTo erase a cell, place the cursor at the cell position.";
        cout << "\n\nPress ";
        set_color_field(14, 9);
        cout << "SPACE";
        set_color_field(7, 9);
        cout << " to continue.";

       m_key = _getch();
        if (m_key == -32) m_key = _getch();

        if (m_key == LEFT && m_active_menu_x != 1) {
            set_cursor_field(0, 0);
            arr[m_active_menu_y][m_active_menu_x] = 0;
            m_active_menu_x--;
            arr[m_active_menu_y][m_active_menu_x] = 4;
        }
        else if (m_key == RIGHT && m_active_menu_x != m_x - 2) {
            set_cursor_field(0, 0);
            arr[m_active_menu_y][m_active_menu_x] = 0;
            m_active_menu_x++;
            arr[m_active_menu_y][m_active_menu_x] = 4;
        }
        else if (m_key == DOWN && m_active_menu_y != m_y - 2) {
            set_cursor_field(0, 0);
            arr[m_active_menu_y][m_active_menu_x] = 0;
            m_active_menu_y++;
            arr[m_active_menu_y][m_active_menu_x] = 4;
        }
        else if (m_key == UP && m_active_menu_y != 1) {
            set_cursor_field(0, 0);
            arr[m_active_menu_y][m_active_menu_x] = 0;
            m_active_menu_y--;
            arr[m_active_menu_y][m_active_menu_x] = 4;
        }
        else if (m_key == ENTER) {
            if (m_active_menu_x == m_x-2) {
                set_cursor_field(0, 0);
                arr[m_active_menu_y][m_active_menu_x] = 1;
                if (m_active_menu_y == m_y-2)
                    m_active_menu_y--;
                else
                    m_active_menu_y++;
                arr[m_active_menu_y][m_active_menu_x] = 4;
            }
            else {
                set_cursor_field(0, 0);
                arr[m_active_menu_y][m_active_menu_x] = 1;
                m_active_menu_x++;
                arr[m_active_menu_y][m_active_menu_x] = 4;
            }
        }
        else if (m_key == SPACE) {
            system("cls");
            break;
        }
    }
    for (int i = 0; i < m_y; i++)
        for (int j = 0; j < m_x; j++) {
            if (arr[i][j] == 4)
                arr[i][j] = 0;
        }
}

void Field::print() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    m_life_cells = 0;
    cout << m_x - 2 << "x" << m_y - 2 << endl;
    for (int i = 1; i < m_y - 1; i++) {
        for (int j = 1; j < m_x - 1; j++) {
            if (arr[i][j] == 1) {
                set_color_field(0, 0);
                cout << "  ";
                m_life_cells++;
            }
            else if (arr[i][j] == 4) {
                set_color_field(8, 8);
                cout << "  ";
            }
            else {
                set_color_field(7, 7);
                cout << "  ";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
    set_color_field(7, 9);
}

void Field::rule(int i, int j) {
    int lifeCount = 0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0)
                y++;
            if (arr[i + x][j + y] == 1 || arr[i + x][j + y] == 3)
                lifeCount++;
        }
    }

    if (lifeCount == 3 && arr[i][j] == 0)
        arr[i][j] = 2;
    if ((lifeCount < 2 || lifeCount > 3) && arr[i][j] == 1)
        arr[i][j] = 3;
}

void Field::game() {
    m_gen = 1;
    print();
    cout << "\n\nGeneration " << m_gen++ << endl;
    cout << "Amount of alive: " << m_life_cells << "  " << endl;

    cout << "\nPress ";
    set_color_field(14, 9);
    cout << "E";
    set_color_field(7, 9);
    cout << " to edit current configuration.";

    cout << "\nPress ";
    set_color_field(14, 9);
    cout << "Q";
    set_color_field(7, 9);
    cout << " to pause.";

    cout << "\nPress ";
    set_color_field(14, 9);
    cout << "ESC";
    set_color_field(7, 9);
    cout << " to return to main menu.\n";

    Sleep(500);
    set_cursor_field(0, 0);
    while (true) {
        for (int i = 1; i < m_y - 1; i++)
            for (int j = 1; j < m_x - 1; j++)
                rule(i, j);

        for (int i = 1; i < m_y - 1; i++)
            for (int j = 1; j < m_x - 1; j++) {
                if (arr[i][j] == 2)
                    arr[i][j] = 1;
                else if (arr[i][j] == 3)
                    arr[i][j] = 0;
            }
        print();
        cout << "\n\nGeneration " << m_gen++ << endl;
        cout << "Amount of alive: " << m_life_cells << "  " << endl;

        cout << "\nPress ";
        set_color_field(14, 9);
        cout << "E";
        set_color_field(7, 9);
        cout << " to edit current configuration.";

        cout << "\nPress ";
        set_color_field(14, 9);
        cout << "Q";
        set_color_field(7, 9);
        cout << " to pause.";

        cout << "\nPress ";
        set_color_field(14, 9);
        cout << "ESC";
        set_color_field(7, 9);
        cout << " to return to main menu.\n";

        Sleep(500);

        if (m_life_cells == 0) {
            cout << endl;
            system("pause");
            break;
        }

        if (GetAsyncKeyState(VK_ESCAPE) && m_gen > 3) {
            system("pause");
            break;
        }
        else if (GetAsyncKeyState(E)) {
            system("cls");
            custom_generate();
        }
        else if (GetAsyncKeyState(Q)) {
            system("pause");
            system("cls");
        }

        set_cursor_field(0, 0);
    }
    system("cls");
}

void Field::run() {
    if (m_action == 0) {
        system("cls");
        random_generate();
        game();
    }
    else if (m_action == 1) {
        system("cls");
        custom_generate();
        game();
    }
}
