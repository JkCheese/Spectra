#pragma once

#include <array>
#include "board.h"
#include "move.h"

constexpr int MAX_MOVES = 1024;

struct MoveList {
    Move moves[MAX_MOVES];
    int count = 0;

    void add(const Move& move) { if (count < MAX_MOVES) moves[count++] = move; }

    void clear() { count = 0; }
};

constexpr std::array<Bitboard, 256> compute_knight_attacks() {
    std::array<Bitboard, 256> table{};
    for (int sq = 0; sq < 256; sq++) {
        Bitboard b{};
        b.set_bit(sq);
        
        Bitboard attacks{};
        attacks |= (b & ~FILE_A).shift_north().shift_north().shift_west();
        attacks |= (b & ~FILE_A).shift_south().shift_south().shift_west();
        attacks |= (b & ~FILE_P).shift_north().shift_north().shift_east();
        attacks |= (b & ~FILE_P).shift_south().shift_south().shift_east();
        attacks |= (b & ~(FILE_A | FILE_B)).shift_north().shift_west().shift_west();
        attacks |= (b & ~(FILE_A | FILE_B)).shift_south().shift_west().shift_west();
        attacks |= (b & ~(FILE_O | FILE_P)).shift_north().shift_east().shift_east();
        attacks |= (b & ~(FILE_O | FILE_P)).shift_south().shift_east().shift_east();
        table[sq] = attacks & VALID_SQUARES;
    }
    return table;
}

constexpr std::array<Bitboard, 256> compute_king_attacks() {
    std::array<Bitboard, 256> table{};
    for (int sq = 0; sq < 256; sq++) {
        Bitboard b{};
        b.set_bit(sq);

        Bitboard attacks{};
        attacks |= (b & ~FILE_A).shift_northwest();
        attacks |= (b & ~FILE_A).shift_west();
        attacks |= (b & ~FILE_A).shift_southwest();
        attacks |= (b & ~FILE_P).shift_northeast();
        attacks |= (b & ~FILE_P).shift_east();
        attacks |= (b & ~FILE_P).shift_southeast();
        attacks |= b.shift_north();
        attacks |= b.shift_south();
        table[sq] = attacks & VALID_SQUARES;
    }
    return table;
}

constexpr auto KNIGHT_ATTACKS = compute_knight_attacks();
constexpr auto KING_ATTACKS = compute_king_attacks();

void generate_knight_moves(const Board& board, MoveList& list, Player player);
void generate_king_moves(const Board& board, MoveList& list, Player player);