#include <iostream>
#include "board.h"

void player_move(GameBoard& board, int symbol){
    unsigned int row, col;
    std::cout << "Player " << symbol << "\n\tRow: ";
    std::cin >> row;
    std::cout << "\tColumn: ";
    std::cin >> col;
    if (board.get_cell(row, col) != SYM_NONE || row > 2 || col > 2){
        std::cout << "Invalid move" << std::endl;
        player_move(board, symbol);
        return;
    }
    board.update_cell(row, col, symbol);

}

int main(){
    GameBoard board;
    int turn = 0;
    int symbol = SYM_X;
    while (turn < 9){
        system("clear");
        board.display();
        player_move(board, symbol);
        int winner = board.check_win();
        if (winner){
            system("clear");
            board.display();
            std::cout << "Winner: Player " << symbol << std::endl;
            return 0;
        }
        turn++;
        symbol = 3 ^ symbol;
    }
}