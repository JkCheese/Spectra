/* Define board state */

#pragma once

#include "bitboard.h"

enum class Square : uint16_t {
    A1,  B1,  C1,  D1,  E1,  F1,  G1,  H1,  I1,  J1,  K1,  L1,  M1,  N1,  O1,  P1,
    A2,  B2,  C2,  D2,  E2,  F2,  G2,  H2,  I2,  J2,  K2,  L2,  M2,  N2,  O2,  P2,
    A3,  B3,  C3,  D3,  E3,  F3,  G3,  H3,  I3,  J3,  K3,  L3,  M3,  N3,  O3,  P3,
    A4,  B4,  C4,  D4,  E4,  F4,  G4,  H4,  I4,  J4,  K4,  L4,  M4,  N4,  O4,  P4,
    A5,  B5,  C5,  D5,  E5,  F5,  G5,  H5,  I5,  J5,  K5,  L5,  M5,  N5,  O5,  P5,
    A6,  B6,  C6,  D6,  E6,  F6,  G6,  H6,  I6,  J6,  K6,  L6,  M6,  N6,  O6,  P6,
    A7,  B7,  C7,  D7,  E7,  F7,  G7,  H7,  I7,  J7,  K7,  L7,  M7,  N7,  O7,  P7,
    A8,  B8,  C8,  D8,  E8,  F8,  G8,  H8,  I8,  J8,  K8,  L8,  M8,  N8,  O8,  P8,
    A9,  B9,  C9,  D9,  E9,  F9,  G9,  H9,  I9,  J9,  K9,  L9,  M9,  N9,  O9,  P9,
    A10, B10, C10, D10, E10, F10, G10, H10, I10, J10, K10, L10, M10, N10, O10, P10,
    A11, B11, C11, D11, E11, F11, G11, H11, I11, J11, K11, L11, M11, N11, O11, P11,
    A12, B12, C12, D12, E12, F12, G12, H12, I12, J12, K12, L12, M12, N12, O12, P12,
    A13, B13, C13, D13, E13, F13, G13, H13, I13, J13, K13, L13, M13, N13, O13, P13,
    A14, B14, C14, D14, E14, F14, G14, H14, I14, J14, K14, L14, M14, N14, O14, P14,
    A15, B15, C15, D15, E15, F15, G15, H15, I15, J15, K15, L15, M15, N15, O15, P15,
    A16, B16, C16, D16, E16, F16, G16, H16, I16, J16, K16, L16, M16, N16, O16, P16,
    NO_SQUARE
};

enum class Piece : uint8_t {
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NO_PIECE
};

enum class Player : uint8_t {
    RED, BLUE, YELLOW, GREEN, NO_PLAYER
};

enum class PlayerState : uint8_t {
    ALIVE, ZOMBIE, DEAD
};

enum class Castling : uint8_t {
    NONE, KINGSIDE, QUEENSIDE
};

constexpr uint16_t BOARD_SIZE = 256;

// File masks
constexpr Bitboard FILE_A = Bitboard(0x0001000100010001ULL, 0x0001000100010001ULL, 0x0001000100010001ULL, 0x0001000100010001ULL);
constexpr Bitboard FILE_B = Bitboard(0x0002000200020002ULL, 0x0002000200020002ULL, 0x0002000200020002ULL, 0x0002000200020002ULL);
constexpr Bitboard FILE_C = Bitboard(0x0004000400040004ULL, 0x0004000400040004ULL, 0x0004000400040004ULL, 0x0004000400040004ULL);
constexpr Bitboard FILE_D = Bitboard(0x0008000800080008ULL, 0x0008000800080008ULL, 0x0008000800080008ULL, 0x0008000800080008ULL);
constexpr Bitboard FILE_E = Bitboard(0x0010001000100010ULL, 0x0010001000100010ULL, 0x0010001000100010ULL, 0x0010001000100010ULL);
constexpr Bitboard FILE_F = Bitboard(0x0020002000200020ULL, 0x0020002000200020ULL, 0x0020002000200020ULL, 0x0020002000200020ULL);
constexpr Bitboard FILE_G = Bitboard(0x0040004000400040ULL, 0x0040004000400040ULL, 0x0040004000400040ULL, 0x0040004000400040ULL);
constexpr Bitboard FILE_H = Bitboard(0x0080008000800080ULL, 0x0080008000800080ULL, 0x0080008000800080ULL, 0x0080008000800080ULL);
constexpr Bitboard FILE_I = Bitboard(0x0100010001000100ULL, 0x0100010001000100ULL, 0x0100010001000100ULL, 0x0100010001000100ULL);
constexpr Bitboard FILE_J = Bitboard(0x0200020002000200ULL, 0x0200020002000200ULL, 0x0200020002000200ULL, 0x0200020002000200ULL);
constexpr Bitboard FILE_K = Bitboard(0x0400040004000400ULL, 0x0400040004000400ULL, 0x0400040004000400ULL, 0x0400040004000400ULL);
constexpr Bitboard FILE_L = Bitboard(0x0800080008000800ULL, 0x0800080008000800ULL, 0x0800080008000800ULL, 0x0800080008000800ULL);
constexpr Bitboard FILE_M = Bitboard(0x1000100010001000ULL, 0x1000100010001000ULL, 0x1000100010001000ULL, 0x1000100010001000ULL);
constexpr Bitboard FILE_N = Bitboard(0x2000200020002000ULL, 0x2000200020002000ULL, 0x2000200020002000ULL, 0x2000200020002000ULL);
constexpr Bitboard FILE_O = Bitboard(0x4000400040004000ULL, 0x4000400040004000ULL, 0x4000400040004000ULL, 0x4000400040004000ULL);
constexpr Bitboard FILE_P = Bitboard(0x8000800080008000ULL, 0x8000800080008000ULL, 0x8000800080008000ULL, 0x8000800080008000ULL);

// Rank masks
constexpr Bitboard RANK_1 = Bitboard(0x000000000000FFFFULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_2 = Bitboard(0x00000000FFFF0000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_3 = Bitboard(0x0000FFFF00000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_4 = Bitboard(0xFFFF000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_5 = Bitboard(0x0000000000000000ULL, 0x000000000000FFFFULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_6 = Bitboard(0x0000000000000000ULL, 0x00000000FFFF0000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_7 = Bitboard(0x0000000000000000ULL, 0x0000FFFF00000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_8 = Bitboard(0x0000000000000000ULL, 0xFFFF000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_9 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x000000000000FFFFULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_10 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x00000000FFFF0000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_11 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000FFFF00000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_12 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0xFFFF000000000000ULL, 0x0000000000000000ULL);
constexpr Bitboard RANK_13 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x000000000000FFFFULL);
constexpr Bitboard RANK_14 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x00000000FFFF0000ULL);
constexpr Bitboard RANK_15 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000FFFF00000000ULL);
constexpr Bitboard RANK_16 = Bitboard(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0xFFFF000000000000ULL);

// ————————————————————————————————————————————————————————————————
// Valid squares — the 160 squares that exist on the 4PC board
// Full 14x14 inner area minus the four 3x3 corner cutouts
// Outer border (rank/file 1 and 16) is always brick
// Corners removed: B2-D4, M2-O4, B13-D15, M13-O15
// ————————————————————————————————————————————————————————————————

constexpr Bitboard VALID_SQUARES =
    // all inner squares (files B-O, ranks 2-15)
    // minus southwest corner (files B-D, ranks 2-4)
    // minus southeast corner (files M-O, ranks 2-4)
    // minus northwest corner (files B-D, ranks 13-15)
    // minus northeast corner (files M-O, ranks 13-15)
    Bitboard(
        0x0FF00FF00FF00000ULL, // ranks 1-4:  only ranks 2-4 valid, files E-L only after corner removal — word 0
        0x7FFE7FFE7FFE7FFEULL, // ranks 5-8:  fully valid files B-O
        0x7FFE7FFE7FFE7FFEULL, // ranks 9-12: fully valid files B-O
        0x00000FF00FF00FF0ULL  // ranks 13-16: only ranks 13-15 valid, files E-L only after corner removal — word 3
    );

constexpr int NUM_PLAYERS = 4, NUM_PIECE_TYPES = 6;

struct Board {
    // All 24 piece bitboards, 6 for each of the 4 players
    Bitboard pieces[NUM_PLAYERS][NUM_PIECE_TYPES];

    // Mailbox arrays — which pieces are whose and where
    Piece mailbox[256];
    Player owner[256];

    // Occupancy bitboards
    Bitboard occupied;
    Bitboard occupied_by[NUM_PLAYERS];
    
    // General game state
    Player turn;
    int ply_count, full_move_count;
    int points[NUM_PLAYERS];
    PlayerState state[NUM_PLAYERS];

    // Special move tracking
    Square en_passant[NUM_PLAYERS]; // Multiple players can en passant in one full turn
    Square king_sq[NUM_PLAYERS];
    bool castling_rights[NUM_PLAYERS][2];

    Board() {
        for (int p = 0; p < NUM_PLAYERS; p++)
            for (int pt = 0; pt < NUM_PIECE_TYPES; pt++)
                pieces[p][pt] = Bitboard{};
        
        for (int sq = 0; sq < 256; sq++) {
            mailbox[sq] = Piece::NO_PIECE;
            owner[sq] = Player::NO_PLAYER;
        }

        occupied = Bitboard{};
        for (int p = 0; p < NUM_PLAYERS; p++)
            occupied_by[p] = Bitboard{};

        for (int p = 0; p < NUM_PLAYERS; p++) {
            state[p]           = PlayerState::ALIVE;
            points[p]          = 0;
            en_passant[p]      = Square::NO_SQUARE;
            king_sq[p]         = Square::NO_SQUARE;
            castling_rights[p][0] = true;
            castling_rights[p][1] = true;
        }

        turn             = Player::RED;
        ply_count        = 0;
        full_move_count  = 1;
    }
};

Board init_board();