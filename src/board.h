#ifndef BOARD_H
#define BOARD_H

#include <vector>
#define SYMBOL_STR " XO"

enum Symbols{SYM_NONE = 0, SYM_X, SYM_O};


class GameBoard{
    public:
        GameBoard();
        unsigned int get_cell(unsigned int row, unsigned int col) const;
        void update_cell(unsigned int row, unsigned int col, unsigned int symbol);
        unsigned int check_win() const;
        unsigned int get_free_spaces() const;
        void display() const;
    private:
        std::vector<unsigned int> board;


};

#endif