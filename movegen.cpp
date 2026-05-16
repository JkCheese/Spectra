#include "movegen.h"

void generate_pawn_pushes(
    Bitboard pawns,
    Bitboard empty,
    Player player,
    MoveList& list
) {
    Bitboard single_push{}, double_push{}, promotions{};
    int push_delta = 0;
    Bitboard promo_rank{}, start_rank{};

    switch (player) {
        case Player::RED:
            push_delta = 16;
            promo_rank = RANK_9;
            start_rank = RANK_3;
            single_push = pawns.shift_north() & empty & ~promo_rank;
            double_push = (((pawns & start_rank).shift_north()) & empty).shift_north() & empty;
            promotions = pawns.shift_north() & empty & promo_rank;
            break;
        case Player::BLUE:
            push_delta = 1;
            promo_rank = FILE_I;
            start_rank = FILE_C;
            single_push = pawns.shift_east() & empty & ~promo_rank;
            double_push = (((pawns & start_rank).shift_east()) & empty).shift_east() & empty;
            promotions = pawns.shift_east() & empty & promo_rank;
            break;
        case Player::YELLOW:
            push_delta = -16;
            promo_rank = RANK_8;
            start_rank = RANK_14;
            single_push = pawns.shift_south() & empty & ~promo_rank;
            double_push = (((pawns & start_rank).shift_south()) & empty).shift_south() & empty;
            promotions = pawns.shift_south() & empty & promo_rank;
            break;
        case Player::GREEN:
            push_delta = -1;
            promo_rank = FILE_H;
            start_rank = FILE_N;
            single_push = pawns.shift_west() & empty & ~promo_rank;
            double_push = (((pawns & start_rank).shift_west()) & empty).shift_west() & empty;
            promotions = pawns.shift_west() & empty & promo_rank;
            break;
    }

    // single pushes
    while (single_push) {
        int to = single_push.pop_lsb();
        int from = to - push_delta;
        list.add(Move(Square(from), Square(to), MoveFlag::QUIET));
    }

    // double pushes
    while (double_push) {
        int to = double_push.pop_lsb();
        int from = to - push_delta * 2;
        list.add(Move(Square(from), Square(to), MoveFlag::DOUBLE_PUSH));
    }

    // push promotions — generate one move per promotion piece
    while (promotions) {
        int to = promotions.pop_lsb();
        int from = to - push_delta;
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO, Piece::NO_PIECE, Piece::QUEEN));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO, Piece::NO_PIECE, Piece::ROOK));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO, Piece::NO_PIECE, Piece::BISHOP));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO, Piece::NO_PIECE, Piece::KNIGHT));
    }
}

void generate_pawn_captures(
    Bitboard pawns,
    Bitboard empty,
    Bitboard enemies,
    Player player,
    MoveList& list,
    const Board& board
) {
    Bitboard left_captures{}, right_captures{};
    Bitboard left_promo{}, right_promo{};
    int left_delta = 0, right_delta = 0;
    Bitboard promo_rank{};
    Bitboard edge_left{}, edge_right{};

    switch (player) {
        case Player::RED:
            promo_rank = RANK_9;
            edge_left = FILE_A;
            edge_right = FILE_P;
            left_delta = 15;   // northwest
            right_delta = 17;   // northeast
            left_captures = (pawns & ~edge_left).shift_northwest() & enemies & ~promo_rank;
            right_captures = (pawns & ~edge_right).shift_northeast() & enemies & ~promo_rank;
            left_promo = (pawns & ~edge_left).shift_northwest() & enemies &  promo_rank;
            right_promo = (pawns & ~edge_right).shift_northeast() & enemies &  promo_rank;
            break;
        case Player::BLUE:
            promo_rank = FILE_I;
            edge_left = RANK_16;
            edge_right = RANK_1;
            left_delta = 17;   // northeast
            right_delta = -15;  // southeast
            left_captures = (pawns & ~edge_left).shift_northeast() & enemies & ~promo_rank;
            right_captures = (pawns & ~edge_right).shift_southeast() & enemies & ~promo_rank;
            left_promo = (pawns & ~edge_left).shift_northeast() & enemies &  promo_rank;
            right_promo = (pawns & ~edge_right).shift_southeast() & enemies &  promo_rank;
            break;
        case Player::YELLOW:
            promo_rank = RANK_8;
            edge_left = FILE_P;
            edge_right = FILE_A;
            left_delta = -17;  // southeast → from Yellow's perspective
            right_delta = -15;  // southwest
            left_captures = (pawns & ~edge_left).shift_southeast() & enemies & ~promo_rank;
            right_captures = (pawns & ~edge_right).shift_southwest() & enemies & ~promo_rank;
            left_promo = (pawns & ~edge_left).shift_southeast() & enemies &  promo_rank;
            right_promo = (pawns & ~edge_right).shift_southwest() & enemies &  promo_rank;
            break;
        case Player::GREEN:
            promo_rank = FILE_H;
            edge_left = RANK_1;
            edge_right = RANK_16;
            left_delta = -17;  // southwest
            right_delta = 15;   // northwest
            left_captures = (pawns & ~edge_left).shift_southwest() & enemies & ~promo_rank;
            right_captures = (pawns & ~edge_right).shift_northwest() & enemies & ~promo_rank;
            left_promo = (pawns & ~edge_left).shift_southwest() & enemies &  promo_rank;
            right_promo = (pawns & ~edge_right).shift_northwest() & enemies &  promo_rank;
            break;
    }

    // non-promoting left captures
    while (left_captures) {
        int to = left_captures.pop_lsb();
        int from = to - left_delta;
        Piece captured = board.mailbox[to];
        list.add(Move(Square(from), Square(to), MoveFlag::CAPTURE, captured));
    }

    // non-promoting right captures
    while (right_captures) {
        int to = right_captures.pop_lsb();
        int from = to - right_delta;
        Piece captured = board.mailbox[to];
        list.add(Move(Square(from), Square(to), MoveFlag::CAPTURE, captured));
    }

    // left capture promotions
    while (left_promo) {
        int to = left_promo.pop_lsb();
        int from = to - left_delta;
        Piece captured = board.mailbox[to];
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::QUEEN));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::ROOK));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::BISHOP));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::KNIGHT));
    }

    // right capture promotions
    while (right_promo) {
        int to = right_promo.pop_lsb();
        int from = to - right_delta;
        Piece captured = board.mailbox[to];
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::QUEEN));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::ROOK));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::BISHOP));
        list.add(Move(Square(from), Square(to), MoveFlag::PROMO_CAPTURE, captured, Piece::KNIGHT));
    }
}

void generate_pawn_ep(Bitboard pawns, Player player, MoveList& list, const Board& board) {
    for (int p = 0; p < NUM_PLAYERS; p++) {
        if (Player(p) == player) continue;
        Square ep_sq = board.en_passant[p];
        if (ep_sq == Square::NO_SQUARE) continue;

        Bitboard ep_bb{};
        ep_bb.set_bit(int(ep_sq));

        // find pawns that attack ep_sq by reversing the capture direction
        // a RED pawn captures northwest/northeast — so it sits southeast/southwest of ep_sq
        Bitboard capturing_pawns{};

        switch (player) {
            case Player::RED:
                capturing_pawns |= pawns & ep_bb.shift_southeast();
                capturing_pawns |= pawns & ep_bb.shift_southwest();
                break;
            case Player::BLUE:
                capturing_pawns |= pawns & ep_bb.shift_southwest();
                capturing_pawns |= pawns & ep_bb.shift_northwest();
                break;
            case Player::YELLOW:
                capturing_pawns |= pawns & ep_bb.shift_northwest();
                capturing_pawns |= pawns & ep_bb.shift_northeast();
                break;
            case Player::GREEN:
                capturing_pawns |= pawns & ep_bb.shift_northeast();
                capturing_pawns |= pawns & ep_bb.shift_southeast();
                break;
        }

        while (capturing_pawns) {
            int from = capturing_pawns.pop_lsb();
            list.add(Move(
                Square(from),
                ep_sq,
                MoveFlag::EN_PASSANT,
                Piece::PAWN  // captured piece is always a pawn
            ));
        }
    }
}

void generate_pawn_moves(const Board& board, MoveList& list, Player player) {
    if (board.state[int(player)] == PlayerState::DEAD) return;

    Bitboard pawns = board.pieces[int(player)][int(Piece::PAWN)];
    Bitboard empty = ~board.occupied & VALID_SQUARES;
    Bitboard enemies = board.occupied & ~board.occupied_by[int(player)];

    generate_pawn_pushes(pawns, empty, player, list);
    generate_pawn_captures(pawns, empty, enemies, player, list, board);
    generate_pawn_ep(pawns, player, list, board);
}

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

void generate_pseudo_legal_moves(const Board& board, MoveList& list, Player player) {
    list.clear();
    generate_pawn_moves(board, list, player);
    generate_knight_moves(board, list, player);
    generate_king_moves(board, list, player);
    // sliding pieces come later
}