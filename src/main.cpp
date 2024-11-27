#include <iostream>
#include "../inc/chess.h"

int main(){
    ChessBoard board;
    board.move_piece(1, 4, 3, 4, true);
    board.move_piece(6, 4, 4, 4, true);   
    
    board.display();
}