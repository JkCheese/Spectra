#pragma once

#include "board.h"
#include "move.h"

constexpr int MAX_MOVES = 1024;

struct MoveList {
    Move moves[MAX_MOVES];
    int count = 0;

    void add(const Move& move) { if (count < MAX_MOVES) moves[count++] = move; }

    void clear() { count = 0; }
};

inline Bitboard compute_knight_attacks(Square sq) {
    Bitboard knight = Bitboard{};
    knight.set_bit(int(sq));

    Bitboard precomputed_knight_attacks = Bitboard{};
    
    precomputed_knight_attacks |= (knight & ~FILE_B).shift_north().shift_north().shift_west();
    precomputed_knight_attacks |= (knight & ~FILE_B).shift_south().shift_south().shift_west();
    precomputed_knight_attacks |= (knight & ~FILE_O).shift_north().shift_north().shift_east();
    precomputed_knight_attacks |= (knight & ~FILE_O).shift_south().shift_north().shift_east();
    precomputed_knight_attacks |= (knight & ~(FILE_B | FILE_C)).shift_north().shift_west().shift_west();
    precomputed_knight_attacks |= (knight & ~(FILE_B | FILE_C)).shift_south().shift_west().shift_west();
    precomputed_knight_attacks |= (knight & ~(FILE_O | FILE_N)).shift_north().shift_east().shift_east();
    precomputed_knight_attacks |= (knight & ~(FILE_O | FILE_N)).shift_south().shift_east().shift_east();

    return precomputed_knight_attacks & VALID_SQUARES;
}

