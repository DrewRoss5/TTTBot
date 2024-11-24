#include <iostream>
#include "board.h"

int main(){
    GameBoard board;
    board.update_cell(2, 2, SYM_X);
    board.update_cell(1, 1, SYM_X);
    board.update_cell(0, 0, SYM_X);
    board.display();
    std::cout << "Winner: " << SYMBOL_STR[board.check_win()] << std::endl;
}