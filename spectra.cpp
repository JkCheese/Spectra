#include <iostream>
#include "board.h"
#include "movegen.h"
#include "test.h"

int main() {
    Board board = init_board();
    MoveList list;
    print_board(board);
    // print_bitboard(board.pieces[int(Player::BLUE)][int(Piece::QUEEN)]);
    // generate_pseudo_legal_moves(board, list, Player::RED);
    // for (Move move : list.moves) {
    //     if (move.data != 0) std::cout << int(move.from()) << " " << int(move.to()) << " " << int(move.flag()) << std::endl;
    // }
    // std::cout << list.count << std::endl;
    return 0;
}