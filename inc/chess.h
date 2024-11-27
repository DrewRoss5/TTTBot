#pragma once

#include <string>

enum PIECES{
    B_ROOK = -6,
    B_KNIGHT,
    B_BISH,
    B_QUEEN,
    B_KING,
    B_PAWN,
    BLANK = 0,
    W_PAWN,
    W_KING,
    W_QUEEN,
    W_BISH,
    W_KNIGHT,
    W_ROOK
    
};

enum COLORS{
    BLACK = -1,
    WHITE = 1
};

class ChessBoard{
    public:
        ChessBoard();
        ChessBoard(std::string file_path);
        ~ChessBoard();
        int get_piece(int row, int col);
        int eval_checkmate();
        int eval_check(int color);
        void move_piece(unsigned src_row, unsigned src_col, unsigned dest_row, unsigned dest_col, bool validate);
        void display();
    private:
        int* board {nullptr};
        int* operator[](int row_num);
        bool valid_move(unsigned src_row, unsigned src_col, unsigned dest_row, unsigned dest_col);

};

