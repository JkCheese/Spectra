#pragma once

#include <iostream>
#include <string>
#include "bitboard.h"
#include "board.h"

void print_bitboard(const Bitboard& bb) {
    for (int r = 15; r >= 0; r--) {
        for (int f = 0; f < 16; f++) {
            if (bb.test_bit(f, r)) {
                std::cout << 1;
            } else {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void print_board(const Board& b) {
    std::string color_str[] = { "r", "b", "y", "g" };
    std::string piece_str[] = { "P", "N", "B", "R", "Q", "K" };

    for (int r = 15; r >= 0; r--) {
        for (int f = 0; f < 16; f++) {
            int sq = f + r * 16;

            // check if this is a brick square
            if (!VALID_SQUARES.test_bit(sq)) {
                std::cout << "XX ";
                continue;
            }

            // find what piece is on this square using the mailbox
            Piece pt = b.mailbox[sq];
            Player p = b.owner[sq];

            if (pt == Piece::NO_PIECE || p == Player::NO_PLAYER) {
                std::cout << ".. ";
            } else {
                std::cout << color_str[int(p)] << piece_str[int(pt)] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}