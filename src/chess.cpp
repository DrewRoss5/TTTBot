#include "../inc/chess.h"

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

#define PIECE_STR_WHITE ".pkqbnr"
#define PIECE_STR_BLACK " PKQBNR"

// returns a given row on the chess board
int* ChessBoard::operator[](int row){
    return &this->board[row * 8];
}

// intializes the chess board in a standard starting position
ChessBoard::ChessBoard(){
    this->board = new int[64];
    // place the tooks, knights and bishops
    for (int i = W_ROOK; i > W_QUEEN; i--){
        (*this)[0][i + 1] = i;
        (*this)[0][7 - i - 1]  = i;
        (*this)[7][i  + 1] = -i;
        (*this)[7][7- i -1] = -i;
        
    }
    // place the kings and queens
    (*this)[0][3] = W_QUEEN;
    (*this)[0][4] = W_KING;
    (*this)[7][3] = B_QUEEN;
    (*this)[7][4] = B_KING;
    // place pawns
    for (int i = 0; i < 8; i++){
        (*this)[1][i] = W_PAWN;
        (*this)[6][i] = B_PAWN;
    }
}

// loads a chess board from a file 
ChessBoard::ChessBoard(std::string filepath){
    this->board = new int[64];
    std::map<char, int> pieces{
        {'R', -6},
        {'N', -5},
        {'B', -4},
        {'Q', -3},
        {'K', -2},
        {'P', -1},
        {'.', 0},
        {'p', 1},
        {'k', 2},
        {'q', 3},
        {'b', 4},
        {'n', 5},
        {'r', 6}
    };
    // read the file
    std::ifstream in(filepath);
    if (!in.good())
        throw std::runtime_error("the input file could not be read");
    // parse the file character by character
    char tmp;
    int pos {63};
    while(in.get(tmp)){
        if (pieces.find(tmp) != pieces.end())
            this->board[--pos] = pieces[tmp];
        if (pos < -1)
            throw std::runtime_error("this board is too large");
    }
    if (pos != -1)
        throw std::runtime_error("this board is too small");
    in.close();
}

// frees the chessboard's memory
ChessBoard::~ChessBoard(){
    delete[] this->board;
}

// displays the chess board
void ChessBoard::display(){
    std::cout << "    A  B  C  D  E  F  G  H \n\n8  ";
    int row {7}, col {0};
    for (int i = 0; i < 64; i++){
        int piece = (*this)[row][col];
        if (piece >= 0)
            std::cout << " " << PIECE_STR_WHITE[piece] << " ";
        else
            std::cout << " " << PIECE_STR_BLACK[-piece] << " ";
        col++;
        if (col == 8 && row > 0){
            col = 0;
            row--;
            std::cout << "\n"<< row + 1 << "  ";
        }
    }
    std::cout << std::endl;
}

// returns true if a move can be legally played, otherwise false
bool ChessBoard::valid_move(unsigned src_row, unsigned src_col, unsigned dst_row, unsigned dst_col){
    if (src_row > 7 || dst_row > 7 || src_col > 7 || dst_col > 7)
        return false;
    // determine the piece to be moved
    int to_move = ((*this)[src_row][src_col]);
    if (to_move == BLANK)
        return false;
    // get the piece that will be captured (if any)
    int target = ((*this)[dst_row][dst_col]);
    if ((target > 0 && to_move > 0) || (target < 0 && to_move < 0))
        return false;
    // TODO: Make this validate movement based on the piece type
    return true;
}

// moves a piece on the board
void ChessBoard::move_piece(unsigned src_row, unsigned src_col, unsigned dst_row, unsigned dst_col, bool validate = true){   
    if (validate && !this->valid_move(src_row, src_col, dst_row, dst_col))
        throw std::runtime_error("invalid move");
    (*this)[dst_row][dst_col] = (*this)[src_row][src_col];
    (*this)[src_row][src_col] = BLANK;
}   