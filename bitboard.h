/* New minimal 256-bit integer type for a 16x16 bitboard */

#pragma once

#include <cstdint>

struct Bitboard {

    // Four "words" of 64-bit integers, each spanning 4 ranks of 16 squares
    uint64_t w[4];
    
    // ————————————————————————————————————————————————————————————————
    // Constructors
    // ————————————————————————————————————————————————————————————————
    
    // Default ————————————————————————————————————————————————————————
    Bitboard() : w{0, 0, 0, 0} {}

    // Parametrized ———————————————————————————————————————————————————
    Bitboard(uint64_t w0, uint64_t w1, uint64_t w2, uint64_t w3) : w{w0, w1, w2, w3} {}

    // Small val to 256-bit int ———————————————————————————————————————
    explicit Bitboard(uint64_t val) : w{val, 0, 0, 0} {}

    // ————————————————————————————————————————————————————————————————
    // Single-bit Operations
    // ————————————————————————————————————————————————————————————————

    // Individual Bits ————————————————————————————————————————————————
    void set_bit(int bit) { w[bit >> 6] |= (uint64_t(1) << (bit & 63)); }
    void clear_bit(int bit) { w[bit >> 6] &= ~(uint64_t(1) << (bit & 63)); }
    bool test_bit(int bit) const { return (w[bit >> 6] >> (bit & 63)) & 1; }

    // Files and Ranks ————————————————————————————————————————————————
    void set_bit(int file, int rank) { set_bit(file + rank * 16); }

    void clear_bit(int file, int rank) { clear_bit(file + rank * 16); }

    bool test_bit(int file, int rank) const { return test_bit(file + rank * 16); }

    // ————————————————————————————————————————————————————————————————
    // Bitwise Operators
    // ————————————————————————————————————————————————————————————————

    Bitboard& operator&=(const Bitboard& rhs) {
        w[0] &= rhs.w[0];
        w[1] &= rhs.w[1];
        w[2] &= rhs.w[2];
        w[3] &= rhs.w[3];
        return *this;
    }

    Bitboard& operator|=(const Bitboard& rhs) {
        w[0] |= rhs.w[0];
        w[1] |= rhs.w[1];
        w[2] |= rhs.w[2];
        w[3] |= rhs.w[3];
        return *this;
    }

    Bitboard& operator^=(const Bitboard& rhs) {
        w[0] ^= rhs.w[0];
        w[1] ^= rhs.w[1];
        w[2] ^= rhs.w[2];
        w[3] ^= rhs.w[3];
        return *this;
    }

    Bitboard operator~() const { return {~w[0], ~w[1], ~w[2], ~w[3]}; }

    friend Bitboard operator&(Bitboard lhs, const Bitboard& rhs) {
        lhs &= rhs;
        return lhs;
    }

    friend Bitboard operator|(Bitboard lhs, const Bitboard& rhs) {
        lhs |= rhs;
        return lhs;
    }

    friend Bitboard operator^(Bitboard lhs, const Bitboard& rhs) {
        lhs ^= rhs;
        return lhs;
    }

    // ————————————————————————————————————————————————————————————————
    // Bit Shifts
    // ————————————————————————————————————————————————————————————————

    friend Bitboard operator<<(Bitboard lhs, int n) {
        if (n == 0) return lhs;
        if (n >= 256) return Bitboard{};
 
        Bitboard result{};
        int word_shift = n >> 6;   // n / 64
        int bit_shift = n & 63;   // n % 64
 
        if (bit_shift == 0) {
            for (int i = 3; i >= word_shift; --i)
                result.w[i] = lhs.w[i - word_shift];
        } else {
            for (int i = 3; i >= 0; --i) {
                int src = i - word_shift;
                if (src >= 0) result.w[i] = lhs.w[src] << bit_shift;
                if (src - 1 >= 0) result.w[i] |= lhs.w[src - 1] >> (64 - bit_shift);
            }
        }
        return result;
    }

    friend Bitboard operator>>(Bitboard lhs, int n) {
        if (n == 0) return lhs;
        if (n >= 256) return Bitboard{};
 
        Bitboard result{};
        int word_shift = n >> 6;
        int bit_shift = n & 63;
 
        if (bit_shift == 0) {
            for (int i = 0; i + word_shift <= 3; ++i)
                result.w[i] = lhs.w[i + word_shift];
        } else {
            for (int i = 0; i <= 3; ++i) {
                int src = i + word_shift;
                if (src <= 3) result.w[i] = lhs.w[src] >> bit_shift;
                if (src + 1 <= 3) result.w[i] |= lhs.w[src + 1] << (64 - bit_shift);
            }
        }
        return result;
    }

    Bitboard& operator<<=(int n) { *this = *this << n; return *this; }
    Bitboard& operator>>=(int n) { *this = *this >> n; return *this; }

    // ————————————————————————————————————————————————————————————————
    // Movement Shifts
    // ————————————————————————————————————————————————————————————————
    
    Bitboard shift_north() const {
        return {
            w[0] << 16,
            (w[1] << 16) | (w[0] >> 48),
            (w[2] << 16) | (w[1] >> 48),
            (w[3] << 16) | (w[2] >> 48)
        };
    }

    Bitboard shift_south() const {
        return {
            (w[0] >> 16) | (w[1] << 48),
            (w[1] >> 16) | (w[2] << 48),
            (w[2] >> 16) | (w[3] << 48),
            w[3] >> 16
        };
    }

    Bitboard shift_east() const {
        return {
             w[0] << 1,
            (w[1] << 1) | (w[0] >> 63),
            (w[2] << 1) | (w[1] >> 63),
            (w[3] << 1) | (w[2] >> 63)
        };
    }

    Bitboard shift_west() const {
        return {
            (w[0] >> 1) | (w[1] << 63),
            (w[1] >> 1) | (w[2] << 63),
            (w[2] >> 1) | (w[3] << 63),
            w[3] >> 1
        };
    }

    Bitboard shift_northeast() const { return shift_north().shift_east(); }
    Bitboard shift_northwest() const { return shift_north().shift_west(); }
    Bitboard shift_southeast() const { return shift_south().shift_east(); }
    Bitboard shift_southwest() const { return shift_south().shift_west(); }

    // ————————————————————————————————————————————————————————————————
    // Comparisons
    // ————————————————————————————————————————————————————————————————

    bool operator==(const Bitboard& rhs) const {
        return w[0] == rhs.w[0]
            && w[1] == rhs.w[1]
            && w[2] == rhs.w[2]
            && w[3] == rhs.w[3];
    }

    bool operator!=(const Bitboard& rhs) const { return !(*this == rhs); }
 
    bool operator!() const {
        return !(w[0] | w[1] | w[2] | w[3]);
    }
 
    explicit operator bool() const {
        return w[0] | w[1] | w[2] | w[3];
    }

    // ————————————————————————————————————————————————————————————————
    // Bit Utilities
    // ————————————————————————————————————————————————————————————————
    
    // Population count of set bits
    int get_popcount() const {
        return __builtin_popcountll(w[0])
             + __builtin_popcountll(w[1])
             + __builtin_popcountll(w[2])
             + __builtin_popcountll(w[3]);
    }
 
    // Index of least significant set bit, undefined if zero
    int get_lsb() const {
        if (w[0]) return __builtin_ctzll(w[0]);
        else if (w[1]) return 64 + __builtin_ctzll(w[1]);
        else if (w[2]) return 128 + __builtin_ctzll(w[2]);
        else return 192 + __builtin_ctzll(w[3]);
    }
 
    // Index of most significant set bit, undefined if zero
    int get_msb() const {
        if (w[3]) return 255 - __builtin_clzll(w[3]);
        else if (w[2]) return 191 - __builtin_clzll(w[2]);
        else if (w[1]) return 127 - __builtin_clzll(w[1]);
        else return 63 - __builtin_clzll(w[0]);
    }
 
    // Extract and clear LSB
    int pop_lsb() {
        int bit;
        if (w[0]) {
            bit = __builtin_ctzll(w[0]);
            w[0] &= w[0] - 1;
            return bit;
        }
        else if (w[1]) {
            bit = __builtin_ctzll(w[1]);
            w[1] &= w[1] - 1;
            return 64  + bit;
        }
        else if (w[2]) {
            bit = __builtin_ctzll(w[2]);
            w[2] &= w[2] - 1;
            return 128 + bit;
        }
        else {
            bit = __builtin_ctzll(w[3]);
            w[3] &= w[3] - 1;
            return 192 + bit;
        }
    }
};