/* Define move and move state needed for undo */

#pragma once

#include <cstdint>
#include "board.h"

constexpr uint32_t MOVE_FROM_SHIFT = 0;
constexpr uint32_t MOVE_TO_SHIFT = 8;
constexpr uint32_t MOVE_FLAG_SHIFT = 16;
constexpr uint32_t MOVE_CAPTURED_SHIFT = 20;
constexpr uint32_t MOVE_PROMO_SHIFT = 25;

constexpr uint32_t MOVE_SQ_MASK = 0xFF; // 8 bits
constexpr uint32_t MOVE_FLAG_MASK= 0xF; // 4 bits
constexpr uint32_t MOVE_CAPTURED_MASK = 0x1F; // 5 bits
constexpr uint32_t MOVE_PROMO_MASK = 0x1F; // 5 bits

enum class MoveFlag : uint8_t {
    QUIET,
    CAPTURE,
    DOUBLE_PUSH,
    EN_PASSANT,
    CASTLE_QUEENSIDE,
    CASTLE_KINGSIDE,
    PROMO,
    PROMO_CAPTURE
};

struct Move {
    // bits 30-31 — Unused
    // bits 25-29 — Promoted piece
    // bits 20-24 — Captured piece
    // bits 16-19 — Move flag
    // bits 8-15 — Square that was moved to
    // bits 0-7 — Square that was moved from
    uint32_t data;
    
    Move() : data(0) {}

    Move(
        Square from,
        Square to,
        MoveFlag flag,
        Piece captured = Piece::NO_PIECE,
        Piece promoted = Piece::NO_PIECE
    ) {
        data = (uint32_t(from) << MOVE_FROM_SHIFT)
             | (uint32_t(to) << MOVE_TO_SHIFT)
             | (uint32_t(flag) << MOVE_FLAG_SHIFT)
             | (uint32_t(captured) << MOVE_CAPTURED_SHIFT)
             | (uint32_t(promoted) << MOVE_PROMO_SHIFT);
    }

    Square from() const { return Square((data >> MOVE_FROM_SHIFT) & MOVE_SQ_MASK); }
    Square to() const { return Square((data >> MOVE_TO_SHIFT) & MOVE_SQ_MASK); }
    MoveFlag flag() const { return MoveFlag((data >> MOVE_FLAG_SHIFT) & MOVE_FLAG_MASK); }
    Piece captured() const { return Piece((data >> MOVE_CAPTURED_SHIFT) & MOVE_CAPTURED_MASK); }
    Piece promoted() const { return Piece((data >> MOVE_PROMO_SHIFT) & MOVE_PROMO_MASK); }
    
    bool is_quiet() const { return flag() == MoveFlag::QUIET; }
    bool is_ep() const { return flag() == MoveFlag::EN_PASSANT; }
    bool is_capture() const { return captured() != Piece::NO_PIECE || is_ep(); }
    bool is_promotion() const { return promoted() != Piece::NO_PIECE; }
    bool is_castling() const {
        return flag() == MoveFlag::CASTLE_QUEENSIDE
            || flag() == MoveFlag::CASTLE_KINGSIDE;
    }
};

struct UndoState {
    Player captured_piece_owner;
    PlayerState prev_state[NUM_PLAYERS];
    
    Square prev_en_passant[NUM_PLAYERS];
    bool prev_castling_rights[NUM_PLAYERS][2];
    int prev_halfmove_clock;
};