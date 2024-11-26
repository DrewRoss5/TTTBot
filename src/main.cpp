#include <iostream>
#include "board.h"
#include "bot.h"

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
    Bot bot(&board, SYM_X);
    std::cout << "Bot intialized" << std::endl;
    int turn = 0;
    while (turn < 9){
        std::cout << "Bot turn:" << std::endl;
        bot.take_turn();
        board.display();
        turn++;
        if (board.check_win() != SYM_NONE){
            std::cout << "Bot wins" << std::endl;
            return 0;
        }
        if (turn == 9)
            break;
        player_move(board, SYM_O);
        board.display();
        turn++;
        if (board.check_win() != SYM_NONE){
            std::cout << "Player wins" << std::endl;
            return 0;
        }
        system("clear");
    }
    std::cout << "Tie!" << std::endl;
}