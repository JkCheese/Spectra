#include "movegen.h"

void generate_knight_moves(const Board& board, MoveList& list, Player player) {
    Bitboard knights = board.pieces[int(player)][int(Piece::KNIGHT)];
    Bitboard own = board.occupied_by[int(player)];

    while (knights) {
        int from = knights.pop_lsb();
        Bitboard attacks = KNIGHT_ATTACKS[from] & ~own;

        while (attacks) {
            int to = attacks.pop_lsb();

            Piece captured = board.mailbox[to];
            MoveFlag flag = (captured != Piece::NO_PIECE) ? MoveFlag::CAPTURE : MoveFlag::QUIET;

            list.add(Move(
                Square(from),
                Square(to),
                flag,
                captured
            ));
        }
    }
}

void generate_king_moves(const Board& board, MoveList& list, Player player) {
    Bitboard kings = board.pieces[int(player)][int(Piece::KING)];
    Bitboard own = board.occupied_by[int(player)];

    while (kings) {
        int from = kings.pop_lsb();
        Bitboard attacks = KING_ATTACKS[from] & ~own;

        while (attacks) {
            int to = attacks.pop_lsb();

            Piece captured = board.mailbox[to];
            MoveFlag flag = (captured != Piece::NO_PIECE) ? MoveFlag::CAPTURE : MoveFlag::QUIET;

            list.add(Move(
                Square(from),
                Square(to),
                flag,
                captured
            ));
        }
    }
}