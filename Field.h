#ifndef GAME_OF_LIFE_FIELD_H
#define GAME_OF_LIFE_FIELD_H

class Field {
    int m_gen, m_life_cells;
    short m_x, m_y, m_action;
    int** arr;
    char m_key;

public:
    void print();
    void regenerate_array(int x, int y);
    void random_generate();
    void custom_generate();
    void rule(int i, int j);
    void run();
    void game();

    void setActiveMenu(int action) { m_action = action; }

    Field(int x, int y, short active_menu);
    ~Field();
};


#endif //GAME_OF_LIFE_FIELD_H
