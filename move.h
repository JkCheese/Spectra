/* Define move state */

#pragma once

#include <cstdint>
#include "board.h"

constexpr uint32_t MOVE_TO_SHIFT = 8;
constexpr uint32_t MOVE_PIECE_SHIFT = 16;
constexpr uint32_t MOVE_CAPTURE_SHIFT = 19;
constexpr uint32_t MOVE_PROMO_SHIFT = 22;
constexpr uint32_t MOVE_CASTLE_SHIFT = 25;
constexpr uint32_t MOVE_EP_SHIFT = 27;

constexpr uint32_t MOVE_SQ_MASK = 0xFF; // 8 bits
constexpr uint32_t MOVE_PIECE_MASK = 0x7; // 3 bits
constexpr uint32_t MOVE_CASTLE_MASK = 0x3; // 2 bits
constexpr uint32_t MOVE_EP_MASK = 0x1; // 1 bit

struct Move {
    // bits 28-31 — Unused
    // bit 27 — En passant 
    // bits 25-26 — Castling
    // bits 22-24 — Promoted piece type
    // bits 19-21 — Captured piece type
    // bits 16-18 — Moving piece type
    // bits 8-15 — Square that was moved to
    // bits 0-7 — Square that was moved from
    uint32_t data;
    
    Move() : data(0) {}

    Move(Square from, Square to, Piece moved, Piece captured, Piece promoted, Castling castling, bool en_passant) {
        data = uint32_t(from)
             | (uint32_t(to) << MOVE_TO_SHIFT)
             | (uint32_t(moved) << MOVE_PIECE_SHIFT)
             | (uint32_t(captured) << MOVE_CAPTURE_SHIFT)
             | (uint32_t(promoted) << MOVE_PROMO_SHIFT)
             | (uint32_t(castling) << MOVE_CASTLE_SHIFT)
             | (uint32_t(en_passant) << MOVE_EP_SHIFT);
    }

    Square from() const { return Square (data& MOVE_SQ_MASK); }
    Square to() const { return Square ((data >> 8) & MOVE_SQ_MASK); }
    Piece piece() const { return Piece ((data >> 16) & MOVE_PIECE_MASK); }
    Piece captured() const { return Piece ((data >> 19) & MOVE_PIECE_MASK); }
    Piece promoted() const { return Piece ((data >> 22) & MOVE_PIECE_MASK); }
    Castling castling() const { return Castling ((data >> 25) & MOVE_CASTLE_MASK); }
    
    bool is_ep() const { return (data >> 27) & MOVE_EP_MASK; }
    bool is_capture() const { return captured() != Piece::NO_PIECE; }
    bool is_promotion() const { return promoted() != Piece::NO_PIECE; }
    bool is_castling() const { return castling() != Castling::NONE; }
};

struct UndoState {
    Player captured_piece_owner;
    PlayerState prev_state[NUM_PLAYERS];
    
    Square prev_en_passant[NUM_PLAYERS];
    bool prev_castling_rights[NUM_PLAYERS][2];
    int prev_halfmove_clock;
};