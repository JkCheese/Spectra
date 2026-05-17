#include "board.h"

Board init_board() {
    Board board;

    // ————————————————————————————————————————————————————————————————
    // Place piece on board, update its bitboard + mailbox
    // ————————————————————————————————————————————————————————————————
    auto place = [&](Player p, Piece pt, Square sq) {
        board.pieces[int(p)][int(pt)].set_bit(int(sq));
        board.mailbox[int(sq)] = pt;
        board.owner[int(sq)] = p;
    };

    // ————————————————————————————————————————————————————————————————
    // Red — moves north, back rank on rank 2, pawns on rank 3
    // RNBQKBNR left to right from Red's perspective (west to east, E–L)
    // ————————————————————————————————————————————————————————————————
    place(Player::RED, Piece::ROOK,   Square::E2);
    place(Player::RED, Piece::KNIGHT, Square::F2);
    place(Player::RED, Piece::BISHOP, Square::G2);
    place(Player::RED, Piece::QUEEN,  Square::H2);
    place(Player::RED, Piece::KING,   Square::I2);
    place(Player::RED, Piece::BISHOP, Square::J2);
    place(Player::RED, Piece::KNIGHT, Square::K2);
    place(Player::RED, Piece::ROOK,   Square::L2);

    for (int sq = int(Square::E3); sq <= int(Square::L3); sq++) {
        place(Player::RED, Piece::PAWN, static_cast<Square>(sq));
    }

    // ————————————————————————————————————————————————————————————————
    // Blue — moves east, back rank on file 2, pawns on file 3
    // RNBQKBNR left to right from Blue's perspective (north to south, ranks 12–5)
    // ————————————————————————————————————————————————————————————————
    place(Player::BLUE, Piece::ROOK,   Square::B12);
    place(Player::BLUE, Piece::KNIGHT, Square::B11);
    place(Player::BLUE, Piece::BISHOP, Square::B10);
    place(Player::BLUE, Piece::QUEEN,  Square::B9);
    place(Player::BLUE, Piece::KING,   Square::B8);
    place(Player::BLUE, Piece::BISHOP, Square::B7);
    place(Player::BLUE, Piece::KNIGHT, Square::B6);
    place(Player::BLUE, Piece::ROOK,   Square::B5);

    for (int sq = int(Square::C5); sq <= int(Square::C12); sq += 16) {
        place(Player::BLUE, Piece::PAWN, static_cast<Square>(sq));
    }

    // ————————————————————————————————————————————————————————————————
    // Yellow — moves south, back rank on rank 15, pawns on rank 14
    // RNBQKBNR left to right from Yellow's perspective (east to west, L–E)
    // ————————————————————————————————————————————————————————————————
    place(Player::YELLOW, Piece::ROOK,   Square::L15);
    place(Player::YELLOW, Piece::KNIGHT, Square::K15);
    place(Player::YELLOW, Piece::BISHOP, Square::J15);
    place(Player::YELLOW, Piece::QUEEN,  Square::I15);
    place(Player::YELLOW, Piece::KING,   Square::H15);
    place(Player::YELLOW, Piece::BISHOP, Square::G15);
    place(Player::YELLOW, Piece::KNIGHT, Square::F15);
    place(Player::YELLOW, Piece::ROOK,   Square::E15);

    for (int sq = int(Square::E14); sq <= int(Square::L14); sq++) {
        place(Player::YELLOW, Piece::PAWN, static_cast<Square>(sq));
    }

    // ————————————————————————————————————————————————————————————————
    // Green — moves west, back rank on file 15, pawns on file 14
    // RNBQKBNR left to right from Green's perspective (south to north, ranks 5–12)
    // ————————————————————————————————————————————————————————————————
    place(Player::GREEN, Piece::ROOK,   Square::O5);
    place(Player::GREEN, Piece::KNIGHT, Square::O6);
    place(Player::GREEN, Piece::BISHOP, Square::O7);
    place(Player::GREEN, Piece::QUEEN,  Square::O8);
    place(Player::GREEN, Piece::KING,   Square::O9);
    place(Player::GREEN, Piece::BISHOP, Square::O10);
    place(Player::GREEN, Piece::KNIGHT, Square::O11);
    place(Player::GREEN, Piece::ROOK,   Square::O12);

    for (int sq = int(Square::N5); sq <= int(Square::N12); sq += 16) {
        place(Player::GREEN, Piece::PAWN, static_cast<Square>(sq));
    }

    // ————————————————————————————————————————————————————————————————
    // Occupancy bitboards
    // ————————————————————————————————————————————————————————————————
    for (int p = 0; p < NUM_PLAYERS; p++) {
        board.occupied_by[p] = Bitboard{};
        for (int pt = 0; pt < NUM_PIECE_TYPES; pt++) {
            board.occupied_by[p] |= board.pieces[p][pt];
        }
        board.occupied |= board.occupied_by[p];
    }

    // ————————————————————————————————————————————————————————————————
    // King squares
    // ————————————————————————————————————————————————————————————————
    board.king_sq[int(Player::RED)]    = Square::I2;
    board.king_sq[int(Player::BLUE)]   = Square::B8;
    board.king_sq[int(Player::YELLOW)] = Square::I15;
    board.king_sq[int(Player::GREEN)]  = Square::O9;

    // ————————————————————————————————————————————————————————————————
    // Game state
    // ————————————————————————————————————————————————————————————————
    board.turn            = Player::RED;
    board.ply_count       = 0;
    board.full_move_count = 1;

    for (int p = 0; p < NUM_PLAYERS; p++) {
        board.points[p]           = 0;
        board.state[p]            = PlayerState::ALIVE;
        board.en_passant[p]       = Square::NO_SQUARE;
        board.castling_rights[p][0] = true;
        board.castling_rights[p][1] = true;
    }

    return board;
}